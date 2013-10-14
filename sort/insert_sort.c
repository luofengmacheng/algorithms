/*
 * author:	luo feng
 * date:	2013/10/11
 * info:	直接插入排序
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

void insert_sort(int array[], int size)
{
    int i = 0, j = 0;

    for(i = 1; i < size; i++) {
        int temp = array[i];
        for(j = i-1; j >= 0 && array[j] >= temp; j--)
            array[j+1] = array[j];
        array[j+1] = temp;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert_sort2(int array[], int size)
{
    int i = 0, j = 0;

    for(i = 1; i < size; i++)
        for(j = i-1; j >= 0 && array[j] >= array[j+1]; j--)
            swap(&array[j], &array[j+1]);
}

int main(int argc, char argv[])
{
    int arr[] = {3, 5, 2, 7, 0};
    int len = sizeof(arr)/sizeof(int);

    insert_sort2(arr, len);
    print_res(arr, len);

    return 0;
}
