/*
 *  Author		:	Varad Girish Mashalkar
 *  Roll Number	:	33337
 *  Batch		:	M11
 *  Version	    :	1
 *  Assignment	:	2A
 *  Details     :   Demonstration of Orphan and Zombie states.
 *  Course		:	Operating Systems Laboratory
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

void orphan_demo()
{
    /*
     *  Input   :   None
     *  Utility :   Demonstrate the Orphan state adoption by init process using fork() system call.
     *  Output  :   Console output (Process ID)
     */
    int cpid = fork();
    if (cpid < 0)
        printf("Fork unsuccessful.\n");
    else if(cpid == 0)
    {
        int array[5], i, temp;
        bool swapped = false;
        printf("In child process.\n");
        printf("Enter Elements of the array : \n");
        for(i = 0; i < 5; i++)
        {
            printf("Enter element %d : ", i);
            scanf("%d", &array[i]);
        }
        printf("Child process iD is %d\n",getpid());
        printf("Parent process iD is %d\n",getppid());
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
        // Print array in Child process.		
        printf("\nArray contents after sorting in child are : \n");
        for(i = 0; i < 5; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
        sleep(15);
        printf("3.child process iD is %d\n",getpid());
        printf("3.Parent process iD is %d\n",getppid());

        printf("\n\n******Child Exit******\n");
    }
    else
    {
        sleep(10);
        int array[5], i, temp;
        bool swapped = false;
        printf("\n\nIn parent process.\n");

        printf("Process iD is %d\n",getpid());
        printf("Parent process iD is %d\n",getppid());
        printf("\nSorting the array in ascending order\n");
        printf("Enter Elements of the array : \n");
        for(i = 0; i < 5; i++)
        {
            printf("Enter element %d : ", i);
            scanf("%d", &array[i]);
        }
        // Employing Bubble Sort.
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
        
        printf("\n\n******Parent Exit******\n");
    }
       
}   
int main()
{
    orphan_demo();
    return 0;
}

/*
    Output

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2A$ ./orphan.out 
In child process.
Enter Elements of the array : 
Enter element 0 : 4
Enter element 1 : 65
Enter element 2 : 2
Enter element 3 : 3
Enter element 4 : 7
Child process iD is 18269
Parent process iD is 18268

Array contents after sorting in child are : 
65 7 4 3 2 


In parent process.
Process iD is 18268
Parent process iD is 18173

Sorting the array in ascending order
Enter Elements of the array : 
Enter element 0 : 9
Enter element 1 : 2
Enter element 2 : 6
Enter element 3 : 4
Enter element 4 : 7

Array contents after sorting in parent are : 
2 4 6 7 9 


******Parent Exit******
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2A$ Child process iD is 18269
Parent process iD is 1629


******Child Exit******

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment2A$ ps -elf | grep 1629
4 S varadma+    1629       1  0  80   0 -  4812 ep_pol 08:14 ?        00:00:00 /lib/systemd/systemd --user

 */