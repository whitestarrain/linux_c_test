#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NLOOP 50
#define NUM   5

int   queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg)
{
    int p = 0;
    for (int i = 0; i < NLOOP; i++) {
        sem_wait(&blank_number);
        queue[p] = rand() % 1000 + 1;
        printf("produce %d \n", queue[p]);
        sem_post(&product_number);
        p = (p + 1) % NUM;
        sleep(rand() % 2);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int c = 0;

    for (int i = 0; i < NLOOP; i++) {
        sem_wait(&product_number);
        printf("consum %d\n", queue[c]);
        queue[c] = 0;
        sem_post(&blank_number);
        c = (c + 1) % NUM;
        sleep(rand() % 2);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t pt, ct;
    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);
    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);
    pthread_join(pt, NULL);
    pthread_join(ct, NULL);
    sem_destroy(&blank_number);
    sem_destroy(&product_number);
    return EXIT_SUCCESS;
}
