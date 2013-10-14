/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	快速排序
 */

#include <stdio.h>

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

void quick_sort(int array[], int i_left, int i_right)
{
    if(i_left < i_right) {
        int mid = array[i_left];
        int i = i_left, j = i_right;

        while(i < j) {
            while(i < j && array[j] > mid)
                j--;
            if(i < j)
                array[i++] = array[j];

            while(i < j && array[i] < mid)
                i++;
            if(i < j)
                array[j--] = array[i];
        }
        array[i] = mid;

        quick_sort(array, i_left, i-1);
        quick_sort(array, i+1, i_right);
    }
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    quick_sort(arr, 0, len-1);
    print_res(arr, len);

    return 0;
}
