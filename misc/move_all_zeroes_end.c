/*
 * author:	luo feng
 * date:	2013/10/18
 * source:	GeeksforGeeks
 * title:	Move all zeros to end of array
 * solution URL:http://www.geeksforgeeks.org/move-zeroes-end-array/
 * info:

Given an array of random numbers, Push all the zero’s of a given array to the end of the array. For example, if the given arrays is {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0}, it should be changed to {1, 9, 8, 4, 2, 7, 6, 0, 0, 0, 0}. The order of all other elements should be same. Expected time complexity is O(n) and extra space is O(1).

 */

#include <stdio.h>

void move_all_zeroes_end(int arr[], int size)
{
    int i = 0, j = 0;

    for(i = 0; i < size; i++) {
        if(arr[i])
            arr[j++] = arr[i];
    }

    while(j < size)
        arr[j++] = 0;
}

int main(int argc, char *argv[])
{
    int arr[] = {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0};
    int len = sizeof(arr)/sizeof(int);
 
    move_all_zeroes_end(arr, len);
    int i = 0;
    for(i = 0; i < len; i++)
        printf("%d\t", arr[i]);
    

    return 0;
}
