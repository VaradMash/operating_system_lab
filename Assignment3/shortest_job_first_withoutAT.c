#include <stdio.h>
#include <stdbool.h>

struct Process{
    int pid, arrival_time, burst_time, turn_around_time, waiting_time, completion_time;
};

void sort_by_burst(struct Process p[], int size)
{
    /*
     *  Input       :   Process array, size of process array.
     *  Utility     :   Sort processes by bubble sort algorithm.
     *  Output      :   None
     */
    struct Process temp;
    bool swapped = false;
    int i;
    do
    {
        swapped = false;
        for(i = 0; i < size - 1; i++)
        {
            if(p[i].burst_time > p[i+ 1].burst_time)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
                swapped = true;
            }
        }
    }while(swapped);
}

void shortest_job_first_NP(struct Process p[], int size)
{
    /*
     *  Input   :   Process array.
     *  Utility :   a) Employ shortest Job first (Non Pre-emptive) algorithm on Process array for CPU Scheduling simulation.
     *              b) Arrival time considered same for all processes.
     *  Output  :   Console output (Description table and Gantt Chart).
     */
    
    // Sort the processes by their burst time.
    sort_by_burst(p, size);
}


int main()
{
    // Get 5 processes.
    int i, time_quant = 0;
    float average_waiting_time, average_turnaround_time = 0;
    struct Process process_array[5];
    for(i = 0; i < 5; i++)
    {
        printf("\nProcess : %d ", (i+1));
        printf("\nProcess ID : ");
        scanf("%d", &process_array[i].pid);
        process_array[i].arrival_time = 0;
        printf("\nBurst Time : ");
        scanf("%d", &process_array[i].burst_time);
        printf("\n");
    }


    // Call SJF algorithm
    shortest_job_first_NP(process_array, 5);

    time_quant = process_array[0].arrival_time;

    printf("\nSr.No.\tPID\tAT\tBT\tCT\tTAT\tWT");
    // Display table for Process serving sequence
    for(i = 0; i < 5; i++)
    {
        time_quant += process_array[i].burst_time;

        process_array[i].completion_time = time_quant;
        process_array[i].turn_around_time = process_array[i].completion_time - process_array[i].arrival_time;
        process_array[i].waiting_time = process_array[i].turn_around_time - process_array[i].burst_time;
        average_waiting_time += process_array[i].waiting_time;
        average_turnaround_time += process_array[i].turn_around_time;
        if(i < 4 && process_array[i+1].arrival_time > time_quant)
        {
            time_quant = process_array[i + 1].arrival_time;
        }

        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t", (i+1), process_array[i].pid, process_array[i].arrival_time, process_array[i].burst_time, process_array[i].completion_time, process_array[i].turn_around_time, process_array[i].waiting_time);
    }
    average_waiting_time /= 5;
    average_turnaround_time /= 5;
    printf("\n\nAverage Waiting Time : %f", average_waiting_time);
    printf("\n\nAverage Turn Around Time : %f\n", average_turnaround_time);

    printf("\n\nGantt Chart : ");
    for(i = 0; i < 5; i++)
    {
        printf("%d", process_array[i].pid);
        if(i < 4)
        {
            printf("->");
        }
    }
    printf("\n");
    return (0);
}