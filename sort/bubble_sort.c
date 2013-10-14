/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	冒泡排序
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

void bubble_sort(int array[], int size)
{
    int i = 0, j = 0;

    for(i = 0; i < size; i++)
        for(j = i+1; j < size; j++)
            if(array[i] > array[j])
                swap(&array[i], &array[j]);
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    bubble_sort(arr, len);
    print_res(arr, len);

    return 0;
}
