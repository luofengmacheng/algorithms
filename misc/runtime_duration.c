/*
 * author:	luo feng
 * date:	2013/10/17
 * info:	测试程序运行的时间
 */

#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    long start_sec, finish_sec, start_usec, finish_usec;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    start_sec = tv.tv_sec;
    start_usec = tv.tv_usec;


    gettimeofday(&tv, &tz);
    finish_sec = tv.tv_sec;
    finish_usec = tv.tv_usec;

    double duration = (double)(finish_usec-start_usec)/1000+(finish_sec-start_sec)*1000;
    printf("Runtime: %.3fms\n", duration);

    return 0;
}
