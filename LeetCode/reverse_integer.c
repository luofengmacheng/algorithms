/*
 * author:	luo feng
 * date:	2013/10/21
 * source:	LeetCode OJ
 * title:	Reverse Integer
 * remark:	本题题目给的提示是前面的0和溢出的问题，不过在提交题目的时候并不需要考虑这些问题，that's so funny
 */

#include <stdio.h>
#include <memory.h>

void int_to_arr(int num, char *arr, int *size)
{
    int data = num;
    int i = 0;

    if(num < 0) {
        arr[0] = '-';
        data = -num;
    }
    else
        arr[0] = '+';
    i = 1;
    while(data) {
        arr[i++] = data%10;
        data /= 10;
    }
    *size = i;
}

int reverse(int x)
{
    char arr[15];
    int n = 0, i = 0;
    int result = 0, temp = 1;
    memset(arr, 0, 15);

    int_to_arr(x, arr, &n);
    /*for(i = 0; i < n; i++)
        printf("%d\n", arr[i]);*/

    for(i = n-1; i >= 1; i--) {
        result += arr[i]*temp;
        temp *= 10;
    }
    if(arr[0] == '-')
        result = -result;
    return result;
}

int reverse1(int x)
{
    int flag = x>0 ? -1 : 1;

    int X = abs(x);
    int result = 0;

    while(X) {
        result = result*10+X%10;
        X /= 10;
    }

    return flag*result;
}

int main(int argc, char *argv[])
{
    printf("%d\n", reverse1(1000000003));

    return 0;
}
