/*
 * author:	luo feng
 * date:	2013/10/16
 * source:	Problem 3 of Project Euler.net
 * title:	Largest prime factor
 * remark:	本题没有得出结果，对于较小的数可以得出正确结果，不知道是因为该方法对大数有问题，还是因为处理器太慢了，不过这样解这道题确实太笨了
 * info:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?

 */

#include <stdio.h>
#include <sys/time.h>

unsigned int is_prime(unsigned long long num)
{
    unsigned long long i = 2;

    if(num == 1)
        return 0;

    while(i < num) {
        if(num%i == 0)
            return 0;
        i++;
    }

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

    unsigned long long num = 600851475143;
    unsigned long long factor = num;

    while(factor > 1) {
        if(num%factor == 0 && is_prime(factor)) {
            printf("%lld\n", factor);
            break;
        }
        else
            factor--;
    }

    gettimeofday(&tv, &tz);
    finish_sec = tv.tv_sec;
    finish_usec = tv.tv_usec;

    double duration = (double)(finish_usec-start_usec)/1000+(finish_sec-start_sec)*1000;
    printf("Runtime: %.2fms\n", duration);

    return 0;
}
