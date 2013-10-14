/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	希尔排序
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

void shell_sort(int array[], int size)
{
    int step = 0, i = 0, j = 0;

    for(step = size/2; step > 0; step /= 2) {
        for(i = step; i < size; i++)
            for(j = i-step; j >= 0 && array[j] >= array[j+step]; j -= step)
                swap(&array[j], &array[j+step]);
    }
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    shell_sort(arr, len);
    print_res(arr, len);

    return 0;
}
