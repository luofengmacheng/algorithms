/*
 * author:	luo feng
 * date:	2013/10/18
 * source:	Project Euler.net
 * title:	Smallest multiple
 * solution URL:http://m.blog.csdn.net/blog/acmjk/9767779
 * remark:	最简单的方法是采用迭代的方式逐个两两求最小公倍数，
 * info:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

 */

#include <stdio.h>

#define max(a, b) (a)>(b) ? (a) : (b)
#define min(a, b) (a)>(b) ? (b) : (a)

/* a和b的最小公倍数 */
int lcm(int a, int b)
{
    int big = max(a, b);
    int small = min(a, b);
    int max = a*b;

    int i = big;
    for(i = big; i < max; i += big) {
        if(i%small == 0)
            return i;
    }
    return max;
}

int main(int argc, char *argv[])
{
    int a = 1, b = 2;
    int lcm_val = 0;

    while(b <= 20) {
        lcm_val = lcm(a, b);
        printf("a and b lcm is: %d\n", lcm_val);
        a = lcm_val;
        b++;
    }
    printf("%d\n", lcm_val);
    

    return 0;
}
