/*
 * author:	luo feng
 * date:	2013/10/17
 * source:	Project Euler.net
 * title:	Largest palindrome product
 * info:

A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.

 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int integer_len(unsigned long num)
{
    int len = 0;

    while(num) {
        num /= 10;
        len++;
    }

    return len;
}

void integer_to_array(unsigned long num, char *str)
{
    int len = 0, i = 0;
    unsigned long data = num;

    len = integer_len(num);
    for(i = 0; i < len; i++) {
        str[i] = data%10;
        data /= 10;
    }
}

int is_palindrome(unsigned long num)
{
    int len = 0;
    unsigned long data = num;

    len = integer_len(num);
    char *int_str = (char*)malloc(len);
    integer_to_array(num, int_str);

    int i = 0, j = len-1;
    while(i < j) {
        if(int_str[i] != int_str[j]) {
            free(int_str);
            return 0;
        }
        i++;
        j--;
    }
    free(int_str);
    return 1;
}

int main(int argc, char *argv[])
{
    long start_sec, finish_sec, start_usec, finish_usec;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    start_sec = tv.tv_sec;
    start_usec = tv.tv_usec;

    int integer_a = 0, integer_b = 0;
    unsigned long res = 0;

    for(integer_a = 999; integer_a > 99; integer_a--) {
        for(integer_b = integer_a; integer_b > 99; integer_b--)
            if(integer_a*integer_b > res && is_palindrome(integer_a*integer_b)) {
                res = integer_a*integer_b;
            }
    }

    printf("largest palindrome product: %ld\n", res);

    gettimeofday(&tv, &tz);
    finish_sec = tv.tv_sec;
    finish_usec = tv.tv_usec;

    double duration = (double)(finish_usec-start_usec)/1000+(finish_sec-start_sec)*1000;
    printf("Runtime: %.2fms\n", duration);

    return 0;
}
