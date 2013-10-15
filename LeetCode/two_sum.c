/*
 * author:	luo feng
 * date:	2013/10/15
 * source:	LeetCode OJ
 * title:	Two Sum
 */

#include <stdio.h>

void two_sum(int nums[], int size, int target, int *index1, int *index2)
{
    int i = 0, j = 0;

    *index1 = i;
    *index2 = j;
    for(i = 0; i < size; i++)
        for(j = i+1; j < size; j++)
            if(nums[i]+nums[j] == target) {
                *index1 = i;
                *index2 = j;
            }
}

int main(int argc, char *argv[])
{
    int arr[] = {2, 7, 11, 15};
    int len = sizeof(arr)/sizeof(int);

    int index1 = 0, index2 = 0;
    int target = 16;
    two_sum(arr, len, target, &index1, &index2);
    if(index1 == 0 && index2 == 0)
        printf("cannot find two numbers in the array that they add up to %d\n", target);
    else
        printf("index1 = %d, index2 = %d\n", index1+1, index2+1);

    return 0;
}
