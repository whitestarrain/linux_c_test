#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NLOOP 5000

int             counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *arg)
{
    int i, val;
    for (i = 0; i < NLOOP; i++) {
        pthread_mutex_lock(&counter_mutex);

        val     = counter;
        counter = val + 1;

        pthread_mutex_unlock(&counter_mutex);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tidA, tidB;

    pthread_create(&tidA, NULL, &doit, NULL);
    pthread_create(&tidB, NULL, &doit, NULL);

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    printf("counter: %d \n", counter);

    return EXIT_SUCCESS;
}
