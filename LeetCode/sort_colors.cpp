/*
 * author:	luo feng
 * date:	2013/11/1
 * source:	LeetCode OJ
 * title:	Sort Colors
 * title:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void sortColors(int A[], int n)
    {
        int i = 0;
        int j = 0, k = n-1;

        while(i <= k) {
            if(A[i] == 0) {
                if(i != j) {
                    swap(A[i], A[j]);
                    ++j;
                    continue;
                }
                else {
                    ++j;
                }
            }
            else if(A[i] == 2) {
                if(i != k) {
                    swap(A[i], A[k]);
                    --k;
                    continue;
                }
                else {
                    --k;
                }
            }
            ++i;
        }
    }
};

int main(int argc, char *argv[])
{
    int a[] = {2, 1, 0, 1, 0, 2};
    int len = sizeof(a) / sizeof(a[0]);

    Solution sol;
    sol.sortColors(a, len);
    for(int i = 0; i < len; ++i)
        cout<<a[i]<<"\t";
    cout<<endl;

    return 0;
}
