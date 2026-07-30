#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int shared = 0;

void *threadFunction(void *arg)
{
    int i;

    for(i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex);

        shared++;
        printf("Thread %ld : Shared Value = %d\n",
               (long)pthread_self(), shared);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, threadFunction, NULL);
    pthread_create(&t2, NULL, threadFunction, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("\nFinal Shared Value = %d\n", shared);

    return 0;
}
