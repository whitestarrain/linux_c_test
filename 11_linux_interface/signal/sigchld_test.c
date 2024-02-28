#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void clear_child(int signo)
{
    printf("sigaction start \n");
    pid_t clear_pid = wait(NULL);
    if (clear_pid < 0) {
        perror("wait");
    }
    printf("clear child %d\n", clear_pid);
    printf("sigaction end\n");
}

int main(int argc, char *argv[])
{
    struct sigaction sig_action, old_action;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_handler = clear_child;
    sig_action.sa_flags   = 0;
    sigaction(SIGCHLD, &sig_action, &old_action);

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {   // parent
        int i = 10;
        while (i--) {
            printf("parent: %d \n", i);
            sleep(3);
        }
    }

    if (pid == 0) {   // child
        int j = 10;
        while (j--) {
            printf("child: %d \n", j);
            sleep(1);
        }
    }
    return EXIT_SUCCESS;
}
