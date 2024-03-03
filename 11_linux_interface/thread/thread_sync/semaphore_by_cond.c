#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO: implement semaphore by condition variable

struct my_sem_t
{
    int             value;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
};

void my_sem_init(struct my_sem_t *sem, int num)
{
    sem->value = num;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void my_sem_wait(struct my_sem_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    while (sem->value == 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--;
    pthread_mutex_unlock(&sem->mutex);
}

void my_sem_post(struct my_sem_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    pthread_mutex_unlock(&sem->mutex);
    pthread_cond_signal(&sem->cond);
}


void my_sem_destroy(struct my_sem_t *sem)
{
    sem->value = 0;
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);
}

// --------------------------------------------------------------

#define NLOOP 50
#define NUM   5

int             queue[NUM];
struct my_sem_t blank_number, product_number;

void *producer(void *arg)
{
    int p = 0;
    for (int i = 0; i < NLOOP; i++) {
        my_sem_wait(&blank_number);
        queue[p] = rand() % 1000 + 1;
        printf("produce %d \n", queue[p]);
        my_sem_post(&product_number);
        p = (p + 1) % NUM;
        sleep(rand() % 2);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int c = 0;

    for (int i = 0; i < NLOOP; i++) {
        my_sem_wait(&product_number);
        printf("consum %d\n", queue[c]);
        queue[c] = 0;
        my_sem_post(&blank_number);
        c = (c + 1) % NUM;
        sleep(rand() % 2);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t pt, ct;
    my_sem_init(&blank_number, NUM);
    my_sem_init(&product_number, 0);

    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);
    pthread_join(pt, NULL);
    pthread_join(ct, NULL);

    my_sem_destroy(&blank_number);
    my_sem_destroy(&product_number);

    return EXIT_SUCCESS;
}
