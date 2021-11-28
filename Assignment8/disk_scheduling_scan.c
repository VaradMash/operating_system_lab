#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_REQUESTS 100

struct Request{
    int request_track, arrival_time;
    bool is_served;
};

void sort_by_request_track(struct Request p[], int size)
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
            if(p[i].request_track > p[i+ 1].request_track)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
                swapped = true;
            }
        }
    }while(swapped);
}

void serve_requests_scan(struct Request request_array[], int number_of_requests, int head)
{
    /*
     *  Input   :   Request array, number of requests, Initial head position.
     *  Utility :   Generate Sequence for serving requests using SCAN algorithm.
     *  Output  :   Serving sequence.
     */
    int completed_requests = 0, serving_sequence[number_of_requests + 1], min_seek = INT_MAX, index = 0;
    struct Request trailing_tracks[number_of_requests], succeeding_tracks[number_of_requests];
    int total_head_movement = 0, trailing_count = 0,succeding_count = 0;
    serving_sequence[0] = head;

    for(int i = 0; i < number_of_requests; i++)
    {
        if(request_array[i].request_track < head)
        {
            trailing_tracks[trailing_count] = request_array[i];
            trailing_count += 1;
        }
        else
        {
            succeeding_tracks[succeding_count] = request_array[i];
            succeding_count += 1;
        }
    }

    // sort the succeeding and trailing tracks
    sort_by_request_track(trailing_tracks, trailing_count);
    sort_by_request_track(succeeding_tracks, succeding_count);

    printf("\n\nServing Sequence : ");
    // Display trailing tracks in descending order
    printf("%d -> ", head);
    for(int i = trailing_count - 1; i >= 0; i--)
    {
        total_head_movement += abs(head - trailing_tracks[i].request_track);
        printf("%d -> ", trailing_tracks[i].request_track);
        head = trailing_tracks[i].request_track;
    }

    // Display succeesind tracks in ascending order
    for(int i = 0; i < succeding_count; i++)
    {
        total_head_movement += abs(head - succeeding_tracks[i].request_track);
        printf("%d", succeeding_tracks[i].request_track);
        head = succeeding_tracks[i].request_track;
        if(i < succeding_count - 1)
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


varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ gcc disk_scheduling_scan.c 
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment8$ ./a.out 


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

Serving Sequence : 50 -> 34 -> 11 -> 62 -> 64 -> 95 -> 119 -> 123 -> 180
Total Head Movements : 208

 */