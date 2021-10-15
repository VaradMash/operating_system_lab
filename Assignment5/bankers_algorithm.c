#include <stdio.h>
#include <stdbool.h>

// Defining presets 
#define PROCESSES 15
#define RESOURCES 15
int max[PROCESSES][RESOURCES], 
    allocation[PROCESSES][RESOURCES], 
    need[PROCESSES][RESOURCES],
    available[RESOURCES], 
    work[RESOURCES], 
    schedule[PROCESSES];
int finished[PROCESSES];

void separator()
{
    /*
     *  Input   :   None
     *  Utility :   Display separator for UI.
     *  Output  :   Console output
     */
    int i;
    printf("\n");
    for(i = 0; i < 100; i++)
    {
        printf("*");
    }
    printf("\n");
}

void display_matrices(int n, int m)
{
    /*
     *  Input   :   Number of Processes and Resources
     *  Utility :   Display Matrices
     *  Output  :   Console Output
     */
    int i, j;
    printf("\nMax Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nAllocation Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailability Matrix : \n");
    for(i = 0; i < m; i++)
    {
        printf("%d ", available[i]);
    }
}

void schedule_processes(int p, int r)
{
    /*
     *  Input   :   Allocation matrix, Number of processes, 
     *  Utility :   Schedule processes according to safety algorithm.
     *  Output  :   Console output
     */
    int work[r];
    int i, j, index = 0, u = 0, completed_processes = 0, k = 0;
    int found_exceeding = 0;

    // Copy availibility matrix into work matrix
    for(i = 0; i < r; i++)
    {
        work[i] = available[i];
    }

    for(k = 0; k < p; k++)
    {
        for(i = 0; i < p; i++)
        {
            if (finished[i] == 0)
            {               
                found_exceeding = 0;
                for(j = 0; j < r; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        found_exceeding = 1;
                        break;
                    }
                }
                // If the current process is suitable to be scheduled with no deadlock, 
                // allocate and empty the resources after completion.
                if (found_exceeding == 0)
                {
                    schedule[index++] = (i + 1);
                    finished[i] = 1;
                    completed_processes += 1;
                    for(u = 0; u < r; u++)
                    {
                        work[u] += allocation[i][u];
                    }
                }
            }
        }
    }
}

void calculate_need_matrix(int p, int r)
{
    /*
     *  Input   :   Number of process, number of resources, max matrix, allocation matrix.
     *  Utility :   Calulate need matrix.
     *  Output  :   Console output.
     */
    int i, j;
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }   

    printf("\nNeed Matrix : \n");
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < r; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

}

bool is_safe(int p, int r)
{
    /*
     *  Input   :   Finished matrix
     *  Utility :   Determine whether the processes can be scheduled in a safe way to avoid deadlock using Banker's algorithm.
     *  Output  :   Boolean value.
     */ 
    int i;
    for (i = 0; i < p; i++)
    {
        if (!finished[i])
        {
            return false;
        }
    }
    return true;
}

void get_input(int n, int m)
{
    /*
     *  Input   :   Number of Processes, Number of Resources
     *  Utility :   Get Matrix Inputs
     *  Output  :   None
     */
    int i, j;
    separator();
    printf("\nEnter Max Matrix : \n\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("\nProcess %d Resource %d : ", i, j);
            scanf("%d", &max[i][j]);
        }
    }
    separator();
    printf("\nEnter Allocation Matrix : \n\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("\nProcess %d Resource %d : ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }
    separator();
    printf("\nEnter Availability matrix : ");
    for(i = 0; i < m; i++)
    {
        printf("\nResource %d : ", i);
        scanf("%d", &available[i]);
    }

    for(i = 0; i < n; i++)
    {
        finished[i] = 0;
    }
}

int resource_request_algorithm(int p, int r)
{
    /*
     *  Input   :   Number of processes and resources
     *  Utility :   Check if system can grant requested resources to desired process.
     *  Output  :   Binary {1:Can grant resources, 0:Cannot grant resources}
     */
    separator(); 
    printf("\n\nResource Request Algorithm\n\n");
    separator();
    int i = 0,process, resource_request[r];
    // Get Process number and requested resources 
    printf("\n\n Enter Process Number : ");
    scanf("%d", &process);
    printf("\n\nEnter requests : ");
    for(i = 0; i < r; i++)
    {
        printf("\nRequest for process %d : ", i);
        scanf("%d", &resource_request[i]);
    }

    // Check if request is greater than need.
    // Else update the need matrix by subtracting the request.
    for(i = 0; i < r; i++)
    {
        if (resource_request[i] > need[process][i])
        {
            printf("Resource %d request exceeded than need for process %d", i, process);
            printf("\n Resource Request %d\nNeed : %d", resource_request[i], need[i]);
            return 0;
        }
        else
        {
            need[process][i] -= resource_request[i];
        }
    }

    // Check if request is greater than availibility.
    // Else update the availibility matrix by by subtracting the request.
    for(i = 0; i < r; i++)
    {
        if (resource_request[i] > available[i])
        {
            printf("Resource %d request exceeded than availibility for process %d", i, process);
            return 0;
        }
        else
        {
            available[i] -= resource_request[i];
        }
    }

    // Update the allocation matrix.
    for(i = 0; i < r; i++)
    {
        allocation[process][i] += resource_request[i];
    }

    // Schedule process for given request.
    schedule_processes(p, r);
    display_matrices(p, r);
    return (is_safe(p, r));
}

void display_schedule(int p)
{
    /*
     *  Input   :   Number of processes and schedule matrix.
     *  Utility :   Display schedule of the provided input.
     *  Output  :   Console Output
     */
    separator();
    int i;
    for(i = 0; i < p - 1; i++)
    {
        printf("%d -> ", schedule[i]);
    }
    printf("%d\n", schedule[p - 1]);
    separator();
}


int main()
{
    int n, m;
    bool safe;
    printf("Banker's Algorithms");
    printf("\nEnter number of processes : ");
    scanf("%d", &n);
    printf("\nEnter number of resources : ");
    scanf("%d", &m);

    // Get the matrix inputs.
    get_input(n, m);
    display_matrices(n, m);

    // Calculate need matrix.
    calculate_need_matrix(n, m);

    // Schedule Processes.
    schedule_processes(n, m);

    // Check whether the given situation is safe i.e. Deadlock can be avoided.
    if (is_safe(n, m))
    {
        printf("\nSafe Schedule : \n");
        display_schedule(n);
        // Resource request algorithm
        if (resource_request_algorithm(n, m))
        {
            printf("Given resource request can be granted at the current state of the system to avoid deadlock.");
            printf("Safe sequence is as follows : ");
            display_schedule(n);
        }
        else
        {
            printf("\nGiven resource request cannot be granted !");
        }
    }
    else
    {
        printf("Deadlock cannot be avoided in the given situation.\n");
    }
    return 0;
}

/*
 Output

A) Text Case 1 (Safe sequence with Unsafe resource request)

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment5$ ./a.out 
Banker's Algorithms
Enter number of processes : 5 

Enter number of resources : 3

****************************************************************************************************

Enter Max Matrix : 


Process 0 Resource 0 : 4

Process 0 Resource 1 : 3

Process 0 Resource 2 : 3

Process 1 Resource 0 : 3

Process 1 Resource 1 : 2

Process 1 Resource 2 : 2

Process 2 Resource 0 : 9

Process 2 Resource 1 : 0

Process 2 Resource 2 : 2

Process 3 Resource 0 : 7

Process 3 Resource 1 : 5

Process 3 Resource 2 : 3

Process 4 Resource 0 : 1

Process 4 Resource 1 : 1

Process 4 Resource 2 : 2

****************************************************************************************************

Enter Allocation Matrix : 


Process 0 Resource 0 : 1

Process 0 Resource 1 : 1

Process 0 Resource 2 : 2

Process 1 Resource 0 : 2

Process 1 Resource 1 : 1

Process 1 Resource 2 : 2

Process 2 Resource 0 : 4

Process 2 Resource 1 : 0

Process 2 Resource 2 : 1

Process 3 Resource 0 : 0

Process 3 Resource 1 : 2

Process 3 Resource 2 : 0

Process 4 Resource 0 : 1

Process 4 Resource 1 : 1

Process 4 Resource 2 : 2

****************************************************************************************************

Enter Availability matrix : 
Resource 0 : 2

Resource 1 : 1

Resource 2 : 0

Max Matrix : 
4 3 3 
3 2 2 
9 0 2 
7 5 3 
1 1 2 

Allocation Matrix : 
1 1 2 
2 1 2 
4 0 1 
0 2 0 
1 1 2 

Availability Matrix : 
2 1 0 
Need Matrix : 
3 2 1 
1 1 0 
5 0 1 
7 3 3 
0 0 0 

Safe Schedule : 

****************************************************************************************************
2 -> 5 -> 1 -> 3 -> 4

****************************************************************************************************

****************************************************************************************************


Resource Request Algorithm


****************************************************************************************************


 Enter Process Number : 1


Enter requests : 
Request for process 0 : 1

Request for process 1 : 1

Request for process 2 : 1
Resource 2 request exceeded than need for process 1
Given resource request cannot be granted !

B) Test Case 2 (Unsafe sequence)
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment5$ ./a.out 
Banker's Algorithms
Enter number of processes : 3

Enter number of resources : 3

****************************************************************************************************

Enter Max Matrix : 


Process 0 Resource 0 : 1

Process 0 Resource 1 : 2

Process 0 Resource 2 : 3

Process 1 Resource 0 : 4

Process 1 Resource 1 : 5

Process 1 Resource 2 : 6

Process 2 Resource 0 : 7

Process 2 Resource 1 : 8

Process 2 Resource 2 : 9

****************************************************************************************************

Enter Allocation Matrix : 


Process 0 Resource 0 : 1

Process 0 Resource 1 : 2

Process 0 Resource 2 : 3

Process 1 Resource 0 : 1

Process 1 Resource 1 : 1

Process 1 Resource 2 : 1

Process 2 Resource 0 : 2

Process 2 Resource 1 : 2

Process 2 Resource 2 : 2

****************************************************************************************************

Enter Availability matrix : 
Resource 0 : 2

Resource 1 : 1

Resource 2 : 0

Max Matrix : 
1 2 3 
4 5 6 
7 8 9 

Allocation Matrix : 
1 2 3 
1 1 1 
2 2 2 

Availability Matrix : 
2 1 0 
Need Matrix : 
0 0 0 
3 4 5 
5 6 7 
Deadlock cannot be avoided in the given situation.

 */