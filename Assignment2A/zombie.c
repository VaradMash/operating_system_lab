/*
 *  Author		:	Varad Girish Mashalkar
 *  Roll Number	:	33337
 *  Batch		:	M11
 *  Version	    :	1
 *  Assignment	:	2A
 *  Details     :   Demonstration of Orphan and Zombie states.
 *  Course		:	Operating Systems Laboratory
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>

void zombie_demo()
{
    int cpid = fork();
    if (cpid < 0)
        printf("Fork unsuccessful.\n");
    else if (cpid == 0)
    {
        sleep(15);
        int array[5], i, temp;
        bool swapped = false;
        printf("\nIn child process.\n");
        printf("child process id is %d\n",getpid());
        printf("1.parent process id is %d\n",getppid());
        printf("Enter Elements of the array : \n");
        for(i = 0; i < 5; i++)
        {
            printf("Enter element %d : ", i);
            scanf("%d", &array[i]);
        }
        printf("1.child process iD is %d\n",getpid());
        printf("1.Parent process iD is %d\n",getppid());
        // Employing Bubble Sort.
        do
        {
            swapped = false;
            for(i = 0; i < 4; i++)
            {
                if(array[i] < array[i + 1])
                {
                    temp = array[i];
                    array[i] = array[i + 1];
                    array[i + 1] = temp;
                    swapped = true;
                }
            }

        }while(swapped);
        // Print array in Parent process.		
        printf("\nArray contents after sorting in child are : \n");
        for(i = 0; i < 5; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
        printf("********* Child Exit *********");
    }
    else
    {
        int array[5], i, temp;
        bool swapped = false;
        printf("\n\nIn parent process.\n");
        printf("Process id is %d\n",getpid());
        printf("\n\nEnter Elements of the array : \n");
        for(i = 0; i < 5; i++)
        {
            printf("Enter element %d : ", i);
            scanf("%d", &array[i]);
        }
        do
        {
            swapped = false;
            for(i = 0; i < 4; i++)
            {
                if(array[i] > array[i + 1])
                {
                    temp = array[i];
                    array[i] = array[i + 1];
                    array[i + 1] = temp;
                    swapped = true;
                }
            }

        }while(swapped);
        // Print array in Parent process.		
        printf("\nArray contents after sorting in parent are : \n");
        for(i = 0; i < 5; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
        sleep(20);
        wait(NULL);
    }
}

int main()
{
    zombie_demo();
    return 0;
}


/*
    Output : 
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2A$ ./zombie.out 


In parent process.
Process id is 22825


Enter Elements of the array : 
Enter element 0 : 5
Enter element 1 : 8
Enter element 2 : 0
Enter element 3 : 1
Enter element 4 : 6

Array contents after sorting in parent are : 
0 1 5 6 8 

In child process.
child process id is 22826
1.parent process id is 22825
Enter Elements of the array : 
Enter element 0 : 5
Enter element 1 : 0
Enter element 2 : 3
Enter element 3 : 6
Enter element 4 : 7
1.child process iD is 22826
1.Parent process iD is 22825

Array contents after sorting in child are : 
7 6 5 3 0 
********* Child Exit *********

varadmash@varadmash-G3-3590:~$ ps -elf
1 Z varadma+   22826   22825  0  80   0 -     0 -      14:20 pts/0    00:00:00 [zombie.out] <defunct>

*/