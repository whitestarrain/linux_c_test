#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MSG_TRY     "try again\n"
#define MSG_TIMEOUT "timeout\n"

int main(int argc, char *argv[])
{
    char buf[10];
    int  fd    = STDIN_FILENO, n, i;
    int  flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    if((fcntl(STDIN_FILENO, F_SETFL,flags)) == -1){
        perror("fcntl set flag");
        exit(1);
    }
    for (i = 0; i < 10; i++) {
        n = read(fd, buf, 10);
        if (n > 0) {
            break;
        }
        if (errno != EAGAIN) {
            perror("read /dev/tty");
            exit(1);
        }
        sleep(1);
        write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
    }
    if (i == 5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    }
    else {
        write(STDOUT_FILENO, buf, n);
    }
    close(fd);

    return EXIT_SUCCESS;
}
