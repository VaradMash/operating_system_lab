#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define PRODUCERS 5
#define CONSUMERS 10



sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int item=1;


pthread_mutex_t mutex;

void *producer(void *pno)
{   
    

    // Produce an random item
    sem_wait(&empty); //reduce value of semaphore
    pthread_mutex_lock(&mutex); //CS locked
    
    printf("Producer produced item %d\n",item);
    
    pthread_mutex_unlock(&mutex); //CS unlocked
    sem_post(&full); //increase value of semaphore
    
}
void *consumer(void *cno)
{   
    
    sem_wait(&full); // reduce value of semaphore
    pthread_mutex_lock(&mutex); //CS locked
    
    printf("Consumer consumed item %d\n\n",item);

    // Incrementing the value of item for next item to be produced.
    item += 1;
    
    pthread_mutex_unlock(&mutex); //CS unlocked
    sem_post(&empty); //increase value of semaphore
    
}

int main()
{   
    int i;
    pthread_t pro[PRODUCERS],con[CONSUMERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0, 5);
    sem_init(&full,0,0);

    //int a[5] = {1,2,3,4,5}; //Multiple  producers and consumers. We refer to only one P and one C
    for(i = 0; i < PRODUCERS; i++)
    {
        
    }

    

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}

