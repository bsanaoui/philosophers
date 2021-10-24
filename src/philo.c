#include "../include/philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <string.h>

char            *hello_msg;
pthread_mutex_t mutex;

void    *worker_thread1(void * tid)
{
    hello_msg = "HELLO WORLD"; 
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

void    *worker_thread2(void * tid)
{
    int i;

    i = 0;
    pthread_mutex_lock(&mutex);
    while (hello_msg[i])
        printf("%c\t",hello_msg[i++]);
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

int main()
{
    pthread_t   tid0; 
    pthread_t   tid1;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid0, NULL, worker_thread1, (void *)&tid0);
    pthread_create(&tid1, NULL, worker_thread2, (void *)&tid1);
    wait(1);

    pthread_mutex_destroy(&mutex);
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    return (0);
}