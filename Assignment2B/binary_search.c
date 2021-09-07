#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int binary_search(int key, int arr[],int size)
{
    /*
     *  Input   :   Key, Integer Array, size of array.
     *  Utility :   Search for key in array using binary search iterative algorithm.
     *  Output  :   Console message.
     */
    int low = 0, mid, high = size - 1;
    while(low <= high)
    {
        mid = (low + high)/2;
        if(arr[mid] > key)
        {
            high = mid - 1;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            return (mid);
        }
    }
    return -1;
}

int main(int argc,char *argv[])
{
    /*
     *  Input   :   Argument count, argument vector.
     *  Utility :   Process elements of argument vector.
     *  Output  :   Console output of binary search.
     */
    if (argc <=2 )
    {
        printf("Not enough arguments !");
        return 0;
    }
    int i, key, result;
    int main_array[argc - 2];
    printf("\n\nIn binary search routine : ");
    printf("\nNumber of elements : %d \n\n", argc - 2);

    // Capture key at argv[1];
    key = atoi(argv[1]);

    // Store elements in array.
    for(i = 2; i < argc; i++)
    {
        main_array[i - 2] = atoi(argv[i]);
    }

    // Print key
    printf("\nKey : %d", key);
    // Print contents of array
    for(i = 0; i < argc - 2; i++)
    {
        printf("\nElement %d : %d", (i+1), main_array[i]);
    }
    printf("\n");

    // Call binary search routine and display result.
    result = binary_search(key, main_array, argc - 2);
    if(result == -1)
    {
        printf("\n%d could not be found in array!", key);
    }
    else
    {
        printf("\n%d found at index %d in sorted array.", key, result);
    }
    return (0);
}