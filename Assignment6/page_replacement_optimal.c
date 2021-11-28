#include <stdio.h>

#define FRAME_SIZE 15
#define INPUT_SIZE 15

int frame_buffer[FRAME_SIZE] = {-1},
     input_string[INPUT_SIZE];

int hit(int page_id, int frame_size)
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
            return i;
        }
    }
    return -1;
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

int get_first_occurence(int page, int start_index, int input_size)
{
    /*
     *  Input   :   Page ID
     *  Utility :   Get first Occurence of frame
     *  Output  :   Index
     */
    int i;
    for(i = start_index; i < input_size; i++)
    {
        if (input_string[i] == page)
        {
            break;
        }
    }
    return i;
}

int get_victim_location(int frame_size,int start_index,int input_size)
{

    /*
     *  Input   :   frame size
     *  Utility :   Find page which is not being used in the near future.
     *  Output  :   Location for swapping buffer.
     */
    if (start_index == frame_size)
    {
        return 0;
    }
    int location = -1, i, prev_occurence = -1, current_occurence;
    for(i = 0; i < frame_size; i++)
    {
        current_occurence = get_first_occurence(frame_buffer[i], start_index, input_size);
        if (prev_occurence < current_occurence)
        {
            prev_occurence = current_occurence;
            location = i;
        }
    }
    return location;
}

void page_replacement_algorithm(int frame_size, int input_size)
{
    /*
     *  Input   :   Frame Buffer Size, Input size
     *  Utility :   Employ page replacement algorithm on given page sequence
     *          :   (Optimal Page Replacement)
     *  Output  :   Hit ratio and miss ratio on console.
     */
    int hits = 0, i, index = 0, hit_index, page_faults = 0;
    float hit_ratio, miss_ratio;
    for(i = 0; i < input_size; i++)
    {
        hit_index = hit(input_string[i], frame_size);
        if (hit_index != -1)
        {
            printf("\n\nThe page %d is found in the buffer (hit)", input_string[i]);
            printf("\n\nReplacing page at index %d in buffer ", i);
            hits += 1;
        }
        else
        {
            printf("\n\nPage not found in buffer (miss)");
            printf("\nPage %d placed at location %d", input_string[i], index);
            
            if (i < frame_size)
            {
                index = i;
            }
            else
            {
                index = get_victim_location(frame_size, i + 1, input_size);
            }
            printf("\nReplacing oldest frame in buffer at location (%d) with page %d",index, input_string[i]);
            frame_buffer[index] = input_string[i];
        }
        printf("\nContents of Frame Buffer : ");
        display_buffer(i, frame_size);
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
    printf("Page replacement algorithm : OPTIMAL PAGE REPLACEMENT ALGORITHM");
    printf("\n\nEnter Size of Frame Buffer : ");
    scanf("%d", &frame_size);
    printf("\nEnter Size of Input String : ");
    scanf("%d", &input_size);

    // Get input for input string
    get_input(input_size);

    // Employ OPR algorithm
    page_replacement_algorithm(frame_size, input_size);

    return 0;
}

/*
Output  :   

Page replacement algorithm : LEAST RECENT USED

Enter Size of Frame Buffer : 3

Enter Size of Input String : 19


Enter Input Stream of Page sequences : 
Page 0	:	3

Page 1	:	2

Page 2	:	1

Page 3	:	3

Page 4	:	4

Page 5	:	1

Page 6	:	6

Page 7	:	2

Page 8	:	4

Page 9	:	3

Page 10	:	4

Page 11	:	2

Page 12	:	1

Page 13	:	4

Page 14	:	5

Page 15	:	2

Page 16	:	1

Page 17	:	3

Page 18	:	4


The given Page Sequence is as follows : 
3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4 

Page not found in buffer (miss)
Page 3 placed at location 0
Replacing oldest frame in buffer at location (0) with page 3
Contents of Frame Buffer : 
3


Page not found in buffer (miss)
Page 2 placed at location 0
Replacing oldest frame in buffer at location (1) with page 2
Contents of Frame Buffer : 
2
3


Page not found in buffer (miss)
Page 1 placed at location 1
Replacing oldest frame in buffer at location (2) with page 1
Contents of Frame Buffer : 
1
2
3


The page 3 is found in the buffer (hit)

Replacing page at index 3 in buffer 
Contents of Frame Buffer : 
1
2
3


Page not found in buffer (miss)
Page 4 placed at location 2
Replacing oldest frame in buffer at location (0) with page 4
Contents of Frame Buffer : 
1
2
4


The page 1 is found in the buffer (hit)

Replacing page at index 5 in buffer 
Contents of Frame Buffer : 
1
2
4


Page not found in buffer (miss)
Page 6 placed at location 0
Replacing oldest frame in buffer at location (2) with page 6
Contents of Frame Buffer : 
6
2
4


The page 2 is found in the buffer (hit)

Replacing page at index 7 in buffer 
Contents of Frame Buffer : 
6
2
4


The page 4 is found in the buffer (hit)

Replacing page at index 8 in buffer 
Contents of Frame Buffer : 
6
2
4


Page not found in buffer (miss)
Page 3 placed at location 2
Replacing oldest frame in buffer at location (2) with page 3
Contents of Frame Buffer : 
3
2
4


The page 4 is found in the buffer (hit)

Replacing page at index 10 in buffer 
Contents of Frame Buffer : 
3
2
4


The page 2 is found in the buffer (hit)

Replacing page at index 11 in buffer 
Contents of Frame Buffer : 
3
2
4


Page not found in buffer (miss)
Page 1 placed at location 2
Replacing oldest frame in buffer at location (2) with page 1
Contents of Frame Buffer : 
1
2
4


The page 4 is found in the buffer (hit)

Replacing page at index 13 in buffer 
Contents of Frame Buffer : 
1
2
4


Page not found in buffer (miss)
Page 5 placed at location 2
Replacing oldest frame in buffer at location (0) with page 5
Contents of Frame Buffer : 
1
2
5


The page 2 is found in the buffer (hit)

Replacing page at index 15 in buffer 
Contents of Frame Buffer : 
1
2
5


The page 1 is found in the buffer (hit)

Replacing page at index 16 in buffer 
Contents of Frame Buffer : 
1
2
5


Page not found in buffer (miss)
Page 3 placed at location 0
Replacing oldest frame in buffer at location (0) with page 3
Contents of Frame Buffer : 
1
2
3


Page not found in buffer (miss)
Page 4 placed at location 0
Replacing oldest frame in buffer at location (0) with page 4
Contents of Frame Buffer : 
1
2
4


Hit Ratio : 0.473684
Miss Ratio: 0.526316


 */