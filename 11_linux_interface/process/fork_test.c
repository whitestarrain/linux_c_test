#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    char *message;
    int   n;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
    }
    if (pid == 0) {
        n       = 6;
        message = "This is the child\n";
    }
    else {
        n       = 3;
        message = "This is the parent\n";
    }
    for (; n > 0; n--) {
        printf("%s", message);
        sleep(2);
    }

    return EXIT_SUCCESS;
}
