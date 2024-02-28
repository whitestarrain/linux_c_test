#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return (void *)1;
}

void *thr_fn2(void *arg)
{
    printf("thread 2 returning\n");
    return (void *)2;
}

void *thr_fn3(void *arg)
{
    int i = 10;
    while (i--) {
        printf("thread 3 writing\n");
        sleep(1);
    }
    return (void *)1;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    void     *tret;

    pthread_create(&tid, NULL, thr_fn1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code %ld\n", (long)tret);

    pthread_create(&tid, NULL, thr_fn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code %ld\n", (long)tret);

    pthread_create(&tid, NULL, thr_fn3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code %ld\n", (long)tret);
}
