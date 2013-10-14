/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	堆排序
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

void heap_adjust(int array[], int i_parent, int size)
{
    int parent = array[i_parent];
    int i_child = 2*i_parent+1;

    while(i_child < size) {
        if(i_child+1 < size && array[i_child] < array[i_child+1])
            i_child++;

        if(parent >array[i_child])
            break;

        array[i_parent] = array[i_child];
        i_parent = i_child;
        i_child = 2*i_parent+1;
    }
    array[i_parent] = parent;
}

void heap_sort(int array[], int size, int top)
{
    int i = 0;

    for(i = size/2-1; i >= 0; i--)
        heap_adjust(array, i, size);

    for(i = size-1; i > size-top; i--) {
        swap(&array[0], &array[i]);

        heap_adjust(array, 0, i);
    }
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    heap_sort(arr, len, 5);
    print_res(arr, len);

    return 0;
}
