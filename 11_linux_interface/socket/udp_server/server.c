#include "../wrap.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_LINE    80
#define SERVER_PORT 8002

int main(int argc, char *argv[])
{
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port        = htons(SERVER_PORT);

    Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Accept connections ...\n");

    char buf[MAX_LINE];

    while (1) {
        struct sockaddr_in cliaddr;
        socklen_t          cliaddr_len = sizeof(cliaddr);
        char               str[INET_ADDRSTRLEN];
        int n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
        if (n < 0) {
            perror("recvfrom error");
        }
        printf("received from %s at port %d error",
               inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
               ntohs(cliaddr.sin_port));
        for (int i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }
        n = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        if (n == -1) {
            perror("sendto error");
        }
    }

    return EXIT_SUCCESS;
}
