#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 15
#define INPUT_SIZE 15

int frame_buffer[FRAME_SIZE] = {-1},
     input_string[INPUT_SIZE];

bool hit(int page_id, int frame_size)
{
    /*
     *  Input   :   Page ID, Size of frame buffer.
     *  Utility :   Check whether Page is available in the Frame buffer.
     *              (Linear Search on frame)
     *  Output  :   Boolean value
     */
    int i;
    for(i = 0; i < frame_size; i++)
    {
        if (frame_buffer[i] == page_id)
        {
            return true;
        }
    }
    return false;
}

void display_buffer(int iteration, int frame_size)
{
    /*
     *  Input   :   Frame size
     *  Utility :   Print contents of frame buffer.
     *  Output  :   Console Output
     */
    int i = iteration;
    if (i > frame_size - 1)
    {
        i = frame_size - 1;
    }
    printf("\n");
    while (i >= 0)
    {
        printf("%d\n", frame_buffer[i]);;
        i -= 1;
    }
}

void page_replacement_algorithm(int frame_size, int input_size)
{
    /*
     *  Input   :   Frame Buffer Size, Input size
     *  Utility :   Employ page replacement algorithm on given page sequence
     *          :   (First In First Out)
     *  Output  :   Hit ratio and miss ratio on console.
     */
    int hits = 0, i, tail = 0;
    float hit_ratio, miss_ratio;
    for(i = 0; i < input_size; i++)
    {
        if (hit(input_string[i], frame_size))
        {
            printf("\n\nThe page %d is found in the buffer (hit)", input_string[i]);
            hits += 1;
        }
        else
        {
            printf("\n\nPage not found in buffer (miss)");
        }
        printf("\nReplacing frame at the oldest location (%d) with page %d",tail, input_string[i]);
        frame_buffer[tail] = input_string[i];
        printf("\nContents of Frame Buffer : ");
        display_buffer(i, frame_size);
        tail = (tail + 1)%frame_size;
    }
    hit_ratio = (float)hits/input_size;
    miss_ratio = 1 - hit_ratio;
    printf("\n\nHit Ratio : %f", hit_ratio);
    printf("\nMiss Ratio: %f\n", miss_ratio);
}

void get_input(int input_size)
{
    /*
     *  Input   :   Input Size for page sequence
     *  Utility :   Get input for page sequence.
     *  Output  :   Confirmation output on console.
     */
    int i;
    printf("\n\nEnter Input Stream of Page sequences : ");
    for(i = 0; i < input_size; i++)
    {
        printf("\nPage %d\t:\t", i);
        scanf("%d", &input_string[i]);
    }

    // Display confirmation output on console.
    printf("\n\nThe given Page Sequence is as follows : \n");
    for(i = 0; i < input_size; i++)
    {
        printf("%d ", input_string[i]);
    }
}

int main()
{
    int frame_size, input_size;
    printf("Page replacement algorithm : FIRST IN FIRST OUT");
    printf("\n\nEnter Size of Frame Buffer : ");
    scanf("%d", &frame_size);
    printf("\nEnter Size of Input String : ");
    scanf("%d", &input_size);

    // Get input for input string
    get_input(input_size);

    // Employ FIFO algorithm
    page_replacement_algorithm(frame_size, input_size);

    return 0;
}

/*

Output

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment6$ ./pr_fifo.out 
Page replacement algorithm : FIRST IN FIRST OUT

Enter Size of Frame Buffer : 3

Enter Size of Input String : 10


Enter Input Stream of Page sequences : 
Page 0	:	4

Page 1	:	7

Page 2	:	6

Page 3	:	1

Page 4	:	7

Page 5	:	6

Page 6	:	1

Page 7	:	2

Page 8	:	7

Page 9	:	2


The given Page Sequence is as follows : 
4 7 6 1 7 6 1 2 7 2 

Page not found in buffer (miss)
Replacing frame at the oldest location (0) with page 4
Contents of Frame Buffer : 
4


Page not found in buffer (miss)
Replacing frame at the oldest location (1) with page 7
Contents of Frame Buffer : 
7
4


Page not found in buffer (miss)
Replacing frame at the oldest location (2) with page 6
Contents of Frame Buffer : 
6
7
4


Page not found in buffer (miss)
Replacing frame at the oldest location (0) with page 1
Contents of Frame Buffer : 
6
7
1


The page 7 is found in the buffer (hit)
Replacing frame at the oldest location (1) with page 7
Contents of Frame Buffer : 
6
7
1


The page 6 is found in the buffer (hit)
Replacing frame at the oldest location (2) with page 6
Contents of Frame Buffer : 
6
7
1


The page 1 is found in the buffer (hit)
Replacing frame at the oldest location (0) with page 1
Contents of Frame Buffer : 
6
7
1


Page not found in buffer (miss)
Replacing frame at the oldest location (1) with page 2
Contents of Frame Buffer : 
6
2
1


Page not found in buffer (miss)
Replacing frame at the oldest location (2) with page 7
Contents of Frame Buffer : 
7
2
1


The page 2 is found in the buffer (hit)
Replacing frame at the oldest location (0) with page 2
Contents of Frame Buffer : 
7
2
2


Hit Ratio : 0.400000
Miss Ratio: 0.600000
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment6$ ./pr_fifo.out 
Page replacement algorithm : FIRST IN FIRST OUT

Enter Size of Frame Buffer : 3

Enter Size of Input String : 6


Enter Input Stream of Page sequences : 
Page 0	:	1

Page 1	:	3

Page 2	:	0

Page 3	:	3

Page 4	:	5

Page 5	:	6


The given Page Sequence is as follows : 
1 3 0 3 5 6 

Page not found in buffer (miss)
Replacing frame at the oldest location (0) with page 1
Contents of Frame Buffer : 
1


Page not found in buffer (miss)
Replacing frame at the oldest location (1) with page 3
Contents of Frame Buffer : 
3
1


The page 0 is found in the buffer (hit)
Replacing frame at the oldest location (2) with page 0
Contents of Frame Buffer : 
0
3
1


The page 3 is found in the buffer (hit)
Replacing frame at the oldest location (0) with page 3
Contents of Frame Buffer : 
0
3
3


Page not found in buffer (miss)
Replacing frame at the oldest location (1) with page 5
Contents of Frame Buffer : 
0
5
3


Page not found in buffer (miss)
Replacing frame at the oldest location (2) with page 6
Contents of Frame Buffer : 
6
5
3


Hit Ratio : 0.333333
Miss Ratio: 0.666667
varadmash@varadmash-G3-
 */