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
    char              *str;
    if (argc != 2) {
        fputs("usage: ./client message\n", stderr);
        exit(1);
    }
    str    = argv[1];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    write(sockfd, str, strlen(str));

    n = read(sockfd, buf, MAXLINE);
    printf("Response from server:\n");
    write(STDOUT_FILENO, buf, n);

    close(sockfd);

    return EXIT_SUCCESS;
}
