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
    struct sockaddr_in servaddr, cliaddr;
    socklen_t          cliaddr_len;
    int                listenfd, connfd;
    char               buf[MAXLINE];
    char               str[INET_ADDRSTRLEN];
    int                i, n;
    int                opt = 1;
    listenfd               = Socket(AF_INET, SOCK_STREAM, 0);

    // 初始化server地址, ipv4, 0.0.0.0:SERV_PORT
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    // 文件描述符和网络地址绑定
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // 允许创建端口号相同但 IP 地址不同的多个 socket 描述符
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 监听文件描述符
    Listen(listenfd, 20);

    printf("Acception connections ...\n");

    while (1) {
        cliaddr_len = sizeof(cliaddr);
        // 接收请求
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        while (1) {
            n = Read(connfd, buf, MAXLINE);
            if (n == 0) {
                printf("the other side has been closed\n");
                break;
            }
            printf("received from %s at PORT %d\n",
                   // inet_ntop: network binary to char pointer
                   inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                   ntohs(cliaddr.sin_port));
            for (i = 0; i < n; i++) {
                buf[i] = toupper(buf[i]);
            }
            // 写入返回
            Write(connfd, buf, n);
        }
        // 关闭链接
        Close(connfd);
    }

    return EXIT_SUCCESS;
}
