#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    // parent
    if (pid > 0) {
        while (1) {
            sleep(1);
        }
    }

    // child
        // child process exit, but parent doesn't call wait
    return EXIT_SUCCESS;
}
