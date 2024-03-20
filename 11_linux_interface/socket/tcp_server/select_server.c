#include "../wrap.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>

#define MAXLINE   80
#define SERV_PORT 8001

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 初始化server地址, ipv4, 0.0.0.0:SERV_PORT
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    // 文件描述符和网络地址绑定
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // 允许创建端口号相同但 IP 地址不同的多个 socket 描述符
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 监听文件描述符
    Listen(listenfd, 20);

    fd_set allset;               // all fd set
    FD_ZERO(&allset);            // clear all fd set
    FD_SET(listenfd, &allset);   // add listenfd to all fd set

    // allset占用情况。select监控的每个set都有FD_SETSIZE个大小限制(和一个进程fd最大的数量一致)，client数组用来记录FD_SETSIZE个位置都给了哪些fd
    // 是不是得减一下，因为 0,1,2 以及 listenfd 都占用了4个 fd，进程最大fd数量也有限制
    int client[FD_SETSIZE];
    int maxfd = listenfd;   // initialize
    int maxi  = -1;         // index into client[] array
    for (int i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;     // -1 表示 fd 未被占用
    }

    for (;;) {
        // select，从当前的fd set中查找到可以读的fd。select block住，直到有fd可读
        fd_set rset = allset;
        int nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            perr_exit("select error");
        }

        // 获取请求fd
        if (FD_ISSET(listenfd, &rset)) {   // listenfd 就绪
            socklen_t cliaddr_len = sizeof(cliaddr);
            int       connfd      = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);

            printf("received from %s at PORT %d\n",
                   inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                   ntohs(cliaddr.sin_port));
            // allset占用情况
            int i;
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                fputs("too many clients\n", stderr);
                exit(1);
            }

            FD_SET(connfd, &allset);   // 监控请求fd
            if (connfd > maxfd) {
                // 记录最大fd，select第一个参数必须为 maxfd + 1
                maxfd = connfd;
            }

            if (i > maxi) {
                maxi = i;   // 记录array[] 最大长度，后面遍历需要
            }

            if (--nready == 0) {
                continue;   // no more readable descriptors
            }
        }

        // 为所有请求fd返回数据
        for (int i = 0; i <= maxi; i++) {
            int sockfd, n;
            if ((sockfd = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET(sockfd, &rset)) {
                int n = Read(sockfd, buf, MAXLINE);
                // 断开连接，释放fd
                if (n == 0) {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else {
                    int j;
                    for (j = 0; j < n; j++) {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(sockfd, buf, n);
                }
                if (--nready == 0) break; /* no more readable descriptors */
            }
        }
    }

    return EXIT_SUCCESS;
}
