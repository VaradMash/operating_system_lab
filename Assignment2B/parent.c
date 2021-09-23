#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
    int arr[5], i, cpid, key;
    char* char_array[8];
    printf("\n\nEnter 5 elements of the array : \n");
    for(i = 0; i < 5; i++)
    {
        printf("\nEnter Element %d : ", i);
        scanf("%d", &arr[i]);
    }
    printf("\nEnter Key : ");
    scanf("%d", &key);
    
    // Sort array and display
    qsort(arr, 5, sizeof(int), compare);
    printf("\nSorted Array : ");
    for(i = 0; i < 5; i++)
    {
        printf("\nElement %d : %d", (i+1), arr[i]);
    }
    printf("\n");
    
    // Setting first argument to name of program output.
    char_array[0] = "./bin.out";
    char_array[1] = malloc(sizeof(int));
    snprintf(char_array[1], sizeof(int), "%d", key);
    for(i = 2; i < 7; i++)
    {
        char_array[i] = malloc(sizeof(int));
        snprintf(char_array[i], sizeof(int), "%d", arr[i - 2]);
    }
    char_array[i] = NULL;

    cpid = fork();
    if(cpid == 0)
    {
        sleep(15);
        printf("\n\n***********Child Process***********\n\n");
        printf("Child Process ID : %d", getpid());
        printf("\nParent Process ID : %d", getppid());
        execv("./bin.out", char_array);
        printf("\n\n***********Child Exit***********\n\n");
    }
    else if (cpid < 0)
    {
        // Unsuccessful fork call.
        printf("\nFork unsuccessful !");
    }
}

/*
    Output

    varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2B$ ./parent.out 

Test Case 1)

Enter 5 elements of the array : 

Enter Element 0 : 5

Enter Element 1 : 0

Enter Element 2 : 2

Enter Element 3 : 4

Enter Element 4 : 3

Enter Key : 5

Sorted Array : 
Element 1 : 0
Element 2 : 2
Element 3 : 3
Element 4 : 4
Element 5 : 5
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2B$ 

***********Child Process***********

Child Process ID : 7223


In binary search routine : 
Number of elements : 5 


Key : 5
Element 1 : 0
Element 2 : 2
Element 3 : 3
Element 4 : 4
Element 5 : 5

5 found at index 4 in sorted array.
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2B$ 

Test Case 2)

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2B$ ./parent.out 


Enter 5 elements of the array : 

Enter Element 0 : 1

Enter Element 1 : 2

Enter Element 2 : 3

Enter Element 3 : 4

Enter Element 4 : 5

Enter Key : 5

Sorted Array : 
Element 1 : 1
Element 2 : 2
Element 3 : 3
Element 4 : 4
Element 5 : 5
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2B$ 

***********Child Process***********

Child Process ID : 7525


In binary search routine : 
Number of elements : 5 


Key : 5
Element 1 : 1
Element 2 : 2
Element 3 : 3
Element 4 : 4
Element 5 : 5

5 found at index 4 in sorted array.


*/