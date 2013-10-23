/*
 * author:	luo feng
 * date:	2013/10/23
 * source:	LeetCode OJ
 * title:	Maximum Subarray
 */

#include <stdio.h>
#include <limits.h>

/* 方法一：简单的计算任意区间的和，并与保存的最大的和比较 */
int LSS_enumerate(int A[], int n)
{
    int max = 0, sum = 0;
    int i = 0, j = 0;

    for(i = 0; i < n; i++) {
        for(j = i; j < n; j++) {
           sum = 0;
           int k = i;
           while(k <= j) {
               sum += A[k];
               k++;
           }
           if(sum > max)
               max = sum;
        }
    }
    return max;
}

/* 方法二：分治法，二分法 */
#define max(a, b) ((a)>(b) ? (a) : (b))

int LSS_recursion(int A[], int l, int r)
{
    int m = (l+r)/2;
    int t = 0, L = 0, R = 0;

    if(l == r)
        return A[m];

    if(r-l == 1)
        return max(max(A[l], A[r]), A[l]+A[r]);

    int lmax = LSS_recursion(A, l, m);
    int rmax = LSS_recursion(A, m+1, r);

    int i = 0;
    for(i = m, t = 0; i >= l; i--) {
        t += A[i];
        if(t > L)
            L = t;
    }
    for(i = m+1, t = 0; i <= r; i++) {
        t += A[i];
        if(t > R)
            R = t;
    }

    return max(max(lmax, rmax), L+R);
}

/* 方法三：动态规划 */
int LSS_dp(int A[], int n)
{
    int f[101];
    int max = INT_MIN;
    f[0] = A[0];

    int i = 0;
    for(i = 1; i < n; i++) {
        if(f[i-1] > 0)
            f[i] = f[i-1]+A[i];
        else
            f[i] = A[i];
        if(f[i] > max)
            max = f[i];
    }
    return max;
}

int main(int argc, char *argv[])
{
    int arr[] = {-2, 1, -3, 4, -1, 2, 1 , -5, 4};
    int len = sizeof(arr)/sizeof(int);

    printf("max subarray: %d\n", LSS_dp(arr, len));

    return 0;
}
