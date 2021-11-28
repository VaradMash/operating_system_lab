#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

struct Request{
    int request_track, arrival_time;
};

void sort_by_arrival(struct Request p[], int size)
{
    /*
     *  Input       :   Request array, size of Request array.
     *  Utility     :   Sort requests by bubble sort algorithm.
     *  Output      :   None
     */
    struct Request temp;
    bool swapped = false;
    int i;
    do
    {
        swapped = false;
        for(i = 0; i < size - 1; i++)
        {
            if(p[i].arrival_time > p[i+ 1].arrival_time)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
                swapped = true;
            }
        }
    }while(swapped);
}

int main()
{
    // Get 5 Requests.
    int i, time_quant = 0, head, initial_head, number_of_requests, total_head_movement = 0;
    struct Request request_array[MAX_REQUESTS];
    printf("\n\nEnter Number of requests  : ");
    scanf("%d", &number_of_requests);
    printf("\nEnter Initial Head Position : ");
    scanf("%d", &head);
    initial_head = head;
    for(i = 0; i < number_of_requests; i++)
    {
        printf("\nRequest %d : ", (i+1));
        printf("\nArrival Time : ");
        scanf("%d", &request_array[i].arrival_time);
        printf("\nRequest Track : ");
        scanf("%d", &request_array[i].request_track);
        printf("\n");
    }

    // Sort Array according to the arrival time.
    sort_by_arrival(request_array, number_of_requests);

    printf("\nSr.No.\tAT\tTrack");
    // Display table for Request serving sequence and calculate head movements and direction reversals
    for(i = 0; i < number_of_requests; i++)
    {
        printf("\n%d\t%d\t%d", (i+1), request_array[i].arrival_time, request_array[i].request_track);
        total_head_movement += abs(request_array[i].request_track - head);
        head = request_array[i].request_track;
    }
    
    printf("\n\nServing Sequence : ");
    printf("%d -> ", initial_head);
    for(i = 0; i < number_of_requests; i++)
    {
        printf("%d", request_array[i].request_track);
        if(i < number_of_requests - 1)
        {
            printf(" -> ");
        }
    }
    printf("\nTotal Head Movements : %d", total_head_movement);
    printf("\n");
    return (0);
}

/*
 Output

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ gcc disk_scheduling_fcfs.c -o fcfs.out
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ ./fcfs.out 


Enter Number of requests  : 8

Enter Initial Head Position : 50

Request 1 : 
Arrival Time : 8

Request Track : 64


Request 2 : 
Arrival Time : 7

Request Track : 62


Request 3 : 
Arrival Time : 6

Request Track : 123


Request 4 : 
Arrival Time : 5

Request Track : 11


Request 5 : 
Arrival Time : 1

Request Track : 95


Request 6 : 
Arrival Time : 2

Request Track : 180


Request 7 : 
Arrival Time : 3

Request Track : 34


Request 8 : 
Arrival Time : 4

Request Track : 119


Sr.No.	AT	Track
1	    1	95
2	    2	180
3	    3	34
4	    4	119
5   	5	11
6	    6	123
7	    7	62
8	8	64

Serving Sequence : 50 -> 95 -> 180 -> 34 -> 119 -> 11 -> 123 -> 62 -> 64
Total Head Movements : 644

 */