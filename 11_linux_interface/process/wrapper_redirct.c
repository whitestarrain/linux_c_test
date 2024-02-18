#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    if (argc != 2) {
        fputs("usage: wrapper_redirct file \n", stderr);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execl("./upper.c", "upper", NULL);
    perror("exec ./upper");
    exit(1);
}
