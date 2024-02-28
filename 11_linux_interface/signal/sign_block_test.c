#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printsignset(const sigset_t *set)
{
    int i;
    for (i = 1; i < 32; i++) {
        if (sigismember(set, i) == 1)
            putchar('1');
        else
            putchar('0');
    }
    puts("");
}

/**
 * sigemptyset
 * sigfillset
 * sigdelset
 * sigaddset
 * sigismember
 *
 * sigprocmask
 * sigpending
 */
int main(int argc, char *argv[])
{
    sigset_t s, p;
    int      i = 100;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, NULL);
    while (i--) {
        sigpending(&p);
        printsignset(&p);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
