#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {   // child
        int i;
        for (i = 3; i > 0; i--) {
            printf("This is the child\n");
            sleep(1);
        }
        exit(3);
    }
    else {   // parent
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val)) {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        }
        else if (WIFSIGNALED(stat_val)) {
            printf("Child  terminated abnormally, signal %d\n",
                   WTERMSIG(stat_val));
        }
    }
    return EXIT_SUCCESS;
}
