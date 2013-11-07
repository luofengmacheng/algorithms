/*
 * author:	luo feng
 * date:	2013/11/7
 * source:	LeetCode OJ
 * title:	Trapping Rain Water
 * language:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
        int sum = 0, m = 0;
        int i = 0, j = 0, k = 0;
        
        for(i = 0; i < n; ++i) {
            j = i + 1;
            while(j < n && A[j] < A[i])
                ++j;

            if(j == n) {
                for(j = n - 1; j > i; --j) {
                    k = j - 1;
                    while(k >= i && A[k] < A[j])
                        --k;
                    m = j - 1;
                    while(m > k) {
                        if(A[j] > A[m])
                            sum += A[j] - A[m];
                        --m;
                    }
                    j = k + 1;
                }
                return sum;
            }
            
            k = i + 1;
            while(k < j) {
                if(A[i] > A[k])
                    sum += A[i] - A[k];
                ++k;
            }
            
            i = j - 1;
        }
        
        return sum;
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {4, 9, 4, 5, 3, 2};
    int len = sizeof(arr) / sizeof(arr[0]);

    Solution sol;
    cout << sol.trap(arr, len) <<endl;

    return 0;
}
