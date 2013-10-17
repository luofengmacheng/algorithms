/*
 * author:	luo feng
 * date:	2013/10/16
 * source:	LeetCode OJ
 * title:	Single Number
 * solution:	利用异或运算符的特性，相同为0，相异为1
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int arr[] = {1, 4, 6, 4, 7, 1, 7};
    int len = sizeof(arr)/sizeof(int);

    int i = 0;
    int res = 0;
    for(i = 0; i < len; i++) {
        res ^= arr[i];
    }
    printf("single number: %d\n", res);

    return 0;
}
