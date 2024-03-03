#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NLOOP 50

struct msg
{
    struct msg *next;
    int         num;
};

struct msg *head;

pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *arg)
{
    struct msg *mp;
    int         i;

    for (int i = 0; i < NLOOP; i++) {
        pthread_mutex_lock(&lock);

        while (head == NULL) {
            pthread_cond_wait(&cond, &lock);
        }

        mp   = head;
        head = mp->next;

        pthread_mutex_unlock(&lock);

        printf("\tConsum %d\n", mp->num);
        free(mp);
        sleep(rand() % 2);
    }

    return NULL;
}

void *producer(void *arg)
{
    struct msg *mp;
    int         i;

    for (int i = 0; i < NLOOP; i++) {
        mp      = malloc(sizeof(struct msg));
        mp->num = i;
        printf("Produce %d\n", mp->num);
        pthread_mutex_lock(&lock);
        mp->next = head;
        head     = mp;
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond);
        sleep(rand() % 2);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t p1, c1;
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, NULL);

    pthread_join(p1, NULL);
    pthread_join(c1, NULL);

    return EXIT_SUCCESS;
}
