#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_alarm(int signo)
{
    // nothing to do
}

int mysleep(unsigned int nsecs)
{
    struct sigaction oldact, newact;
    unsigned int     unslept;
    newact.sa_handler = sig_alarm;
    newact.sa_flags   = 0;
    sigemptyset(&newact.sa_mask);

    sigaction(SIGALRM, &newact, &oldact);

    alarm(nsecs);
    pause();

    unslept = alarm(0);
    sigaction(SIGALRM, &oldact, NULL);

    return unslept;
}

int mysleep_v2(unsigned int nsecs)
{

    struct sigaction oldact, newact;

    // set handler
    newact.sa_handler = sig_alarm;
    newact.sa_flags   = 0;
    sigemptyset(&newact.sa_mask);
    sigaction(SIGALRM, &newact, &oldact);

    // block SIGALRM
    sigset_t mask_set, old_set, susp_set;
    sigemptyset(&mask_set);
    sigaddset(&mask_set, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask_set, &old_set);

    alarm(nsecs);

    susp_set = old_set;
    sigdelset(&susp_set, SIGALRM);   // make sure SIGALRM isn't blocked
    sigsuspend(&susp_set);           // wait for any sign can be caught

    // catch singal
    unsigned int unslept = alarm(0);
    // reset previous action
    sigaction(SIGALRM, &oldact, NULL);

    // reset mask
    sigprocmask(SIG_SETMASK, &old_set, NULL);

    return unslept;
}

int main(int argc, char *argv[])
{
    // unsigned int unslept = mysleep(3);
    unsigned int unslept = mysleep_v2(3);
    printf("unslept: %d", unslept);
    return EXIT_SUCCESS;
}
