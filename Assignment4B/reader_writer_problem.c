#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int book_number = 0;
int numreader = 0;

void *writer(void *writer_number)
{ 
    /*
     *  Input   :   Writer Number
     *  Utility :   Update the value of shared variable.
     *  Output  :   Console Output
     */ 
    // Decrement the writer semaphore
    sem_wait(&wrt);
    // Update the value of book being read.
    book_number += 1;
    printf("Writer %d\nWrote Book %d\n\n",(*((int *)writer_number)),book_number);
    sem_post(&wrt);

}
void *reader(void *rno)
{   
    /*
     *  Input   :   Reader Number
     *  Utility :   Reader reads the book. Makes space for the writer.
     *  Output  :   Console Output
     */
    pthread_mutex_lock(&mutex);
    // Increment the number of readers
    numreader += 1;
    if(numreader == 1) 
    {
        sem_wait(&wrt); 
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d:\nRead Book %d\n",*((int *)rno),book_number);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
}
int main()
{   

    pthread_t readers[10],writers[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int person_id[10] = {1,2,3,4,5,6,7,8,9,10}; 

    // Create threads for readers.
    for(int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, (void *)reader, (void *)&person_id[i]);
    }

    // Create threads for writers
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, (void *)writer, (void *)&person_id[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(writers[0], NULL);
    }


    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
    
}