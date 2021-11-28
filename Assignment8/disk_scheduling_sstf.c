#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_REQUESTS 100

struct Request{
    int request_track, arrival_time;
    bool is_served;
};

void serve_requests_scan(struct Request request_array[], int number_of_requests, int head)
{
    /*
     *  Input   :   Request array, number of requests, Initial head position.
     *  Utility :   Generate Sequence for serving requests using SCAN algorithm.
     *  Output  :   Serving sequence.
     */
    int completed_requests = 0, serving_sequence[number_of_requests + 1], min_seek = INT_MAX, index = 0;
    int total_head_movement = 0;
    serving_sequence[0] = head;
    while(completed_requests != number_of_requests)
    {
        min_seek = INT_MAX;
        printf("\nCompleted requests %d\nHead at %d ", completed_requests, head);
        for(int i = 0; i < number_of_requests; i++)
        {
            if(request_array[i].is_served == false && abs(head - request_array[i].request_track) < min_seek)
            {
                index = i;
                min_seek = abs(head - request_array[i].request_track);
            }
        }
        request_array[index].is_served = true;
        total_head_movement += abs(request_array[index].request_track - head);
        head = request_array[index].request_track;
        serving_sequence[completed_requests + 1] = request_array[index].request_track;
        completed_requests += 1;
    }

    printf("\n\nServing Sequence : ");
    for(int i = 0; i < number_of_requests + 1; i++)
    {
        printf("%d", serving_sequence[i]);
        if(i < number_of_requests)
        {
            printf(" -> ");
        }
    }
    printf("\nTotal Head Movements : %d", total_head_movement);
    
}

int main()
{
    // Get 5 Requests.
    int i, time_quant = 0, head, number_of_requests, total_head_movement = 0;
    struct Request request_array[MAX_REQUESTS];
    printf("\n\nEnter Number of requests  : ");
    scanf("%d", &number_of_requests);
    printf("\nEnter Initial Head Position : ");
    scanf("%d", &head);
    for(i = 0; i < number_of_requests; i++)
    {
        printf("\nRequest %d : ", (i+1));
        printf("\nArrival Time : ");
        scanf("%d", &request_array[i].arrival_time);
        printf("\nRequest Track : ");
        scanf("%d", &request_array[i].request_track);
        printf("\n");
        request_array[i].is_served = false;
    }

    printf("\nSr.No.\tAT\tTrack");
    // Display table for Request serving sequence and calculate head movements and direction reversals
    for(i = 0; i < number_of_requests; i++)
    {
        printf("\n%d\t%d\t%d", (i+1), request_array[i].arrival_time, request_array[i].request_track);
        total_head_movement += abs(request_array[i].request_track - head);
    }

    // Call SCAN algorithm
    serve_requests_scan(request_array, number_of_requests, head);
    
    printf("\n");
    return (0);
}


/*
 Output

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ gcc disk_scheduling_sstf.c -o sstf.out
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ ./sstf.out 


Enter Number of requests  : 8

Enter Initial Head Position : 50

Request 1 : 
Arrival Time : 1

Request Track : 95


Request 2 : 
Arrival Time : 2

Request Track : 180


Request 3 : 
Arrival Time : 3

Request Track : 34


Request 4 : 
Arrival Time : 4

Request Track : 119


Request 5 : 
Arrival Time : 5

Request Track : 11


Request 6 : 
Arrival Time : 6

Request Track : 123


Request 7 : 
Arrival Time : 7

Request Track : 62


Request 8 : 
Arrival Time : 8

Request Track : 64


Sr.No.	AT	Track
1	1	95
2	2	180
3	3	34
4	4	119
5	5	11
6	6	123
7	7	62
8	8	64
Completed requests 0
Head at 50 
Completed requests 1
Head at 62 
Completed requests 2
Head at 64 
Completed requests 3
Head at 34 
Completed requests 4
Head at 11 
Completed requests 5
Head at 95 
Completed requests 6
Head at 119 
Completed requests 7
Head at 123 

Serving Sequence : 50 -> 62 -> 64 -> 34 -> 11 -> 95 -> 119 -> 123 -> 180
Total Head Movements : 236


 */