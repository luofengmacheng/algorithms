/*
 * author:	luo feng
 * date:	2013/10/14
 * source:	Problem 1 of Project Euler.net
 * title:	Multiples of 3 and 5
 * info:	

If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.

 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    int up = 1000-1;

    while(up > 0) {
        if(!(up%3) | !(up%5))
            sum += up;
        up--;
    }

    printf("multiples of 3 and 5: %d\n", sum);

    return 0;
}
