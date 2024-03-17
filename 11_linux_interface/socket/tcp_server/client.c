#include "../wrap.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE   80
#define SERV_PORT 8001

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int                sockfd, n;
    char               buf[MAXLINE];
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        Write(sockfd, buf, strlen(buf));
        n = Read(sockfd, buf, MAXLINE);
        if (n == 0) {
            printf("the other side has been closed.\n");
        }
        else {
            Write(STDOUT_FILENO, buf, n);
        }
    }

    Close(sockfd);

    return EXIT_SUCCESS;
}
