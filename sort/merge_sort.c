/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	
 */

#include <stdio.h>
#include <stdlib.h>

void print_res(int arr[], int size)
{
    int i = 0;

    while(i < size) {
        printf("%d\t", arr[i]);
        i++;
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void merge(int array[], int temparr[], int left, int middle, int right)
{
    int left_end = middle;

    int right_start = middle+1;

    int i_temp = left;

    int temp_len = right-left+1;

    while(left <= left_end && right_start <= right) {
        if(array[left] < array[right_start])
            temparr[i_temp++] = array[left++];
        else
            temparr[i_temp++] = array[right_start++];
    }

    while(left <= left_end)
        temparr[i_temp++] = array[left++];

    while(right_start <= right)
        temparr[i_temp++] = array[right_start++];

    int i = 0;
    for(i = 0; i < temp_len; i++) {
        array[right] = temparr[right];
        right--;
    }
}

static void _merge_sort(int array[], int temparr[], int left, int right)
{
    if(left < right) {
        int middle = (left+right)/2;

        _merge_sort(array, temparr, left, middle);

        _merge_sort(array, temparr, middle+1, right);

       merge(array, temparr, left, middle, right);
    }
}

void merge_sort(int array[], int size)
{
    int *temparr = (int*)malloc(size*sizeof(int));

    _merge_sort(array, temparr, 0, size-1);

    free(temparr);
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    merge_sort(arr, len);
    print_res(arr, len);

    return 0;
}
