#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// create a daemon
void daemonize()
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(0);
    }

    if (pid > 0) {   // parent
        exit(0);
    }

    // child
    pid_t session_id = setsid();
    printf("session_id: %d\n", session_id);

    // change the current working directory to the root
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }

    // attach file descriptors 0, 1 and 2 to the /dev/null
    close(0);
    open("/dev/null", 0, O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main(int argc, char *argv[])
{
    daemonize();
    int i = 10;
    while (i--) {
        printf("%d: i\n", getpid());
        sleep(1);
    }
}
