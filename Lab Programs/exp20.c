#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;

int readCount = 0;
int data = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    while(1)
    {
        pthread_mutex_lock(&mutex);
        readCount++;

        if(readCount == 1)
            sem_wait(&wrt);

        pthread_mutex_unlock(&mutex);

        printf("Reader %d reads data = %d\n", id, data);

        sleep(1);

        pthread_mutex_lock(&mutex);
        readCount--;

        if(readCount == 0)
            sem_post(&wrt);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    while(1)
    {
        sem_wait(&wrt);

        data++;
        printf("Writer %d writes data = %d\n", id, data);

        sem_post(&wrt);

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t r1, r2, w1;
    int reader1 = 1;
    int reader2 = 2;
    int writer1 = 1;

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r1, NULL, reader, &reader1);
    pthread_create(&r2, NULL, reader, &reader2);
    pthread_create(&w1, NULL, writer, &writer1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
