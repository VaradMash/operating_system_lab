#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


#define PRODUCERS 3
#define CONSUMERS 3
#define ITEMS 2         // Maximum items a producer can produce or a consumer can consume
#define BUFFERSIZE 5    // Size of the buffer

sem_t empty;
sem_t full;
int item_in = 0;
int item_out = 0;
int buffer[BUFFERSIZE];
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    for(int i = 0; i < ITEMS; i++) {
        // Produce ith item.
        item = i; 
        // Decrement semaphore for empty counter.  
        sem_wait(&empty);
        // Lock critical section for accessing buffer.
        pthread_mutex_lock(&mutex);
        buffer[item_in] = item;
        printf("Producer %d: \nProduced Item %d\nPlaced at position %d on Buffer\n\n", *((int *)pno),buffer[item_in],item_in);
        item_in = (item_in+1)%BUFFERSIZE;
        // Unlock Critical section.
        pthread_mutex_unlock(&mutex);
        // Increment semaphore for full items.
        sem_post(&full);
    }
}
void *consumer(void *cno)
{
    for(int i = 0; i < ITEMS; i++) {
        // Decrement semaphore for number of full items.
        // Symbolizes the consumption of an item from the buffer.
        sem_wait(&full);
        // Lock Critical section to access Buffer.
        pthread_mutex_lock(&mutex);
        int item = buffer[item_out];
        printf("Consumer %d: \nConsumed Item %d\nPlaced at position %d on Buffer\n\n",*((int *)cno),item, item_out);
        item_out = (item_out+1)%BUFFERSIZE;
        pthread_mutex_unlock(&mutex);
        // Increment semaphore for empty items.
        sem_post(&empty);
    }
}

int main()
{

    pthread_t producers[PRODUCERS],consumers[CONSUMERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BUFFERSIZE);
    sem_init(&full,0,0);

    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer

    for(int i = 0; i < PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for(int i = 0; i < CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}