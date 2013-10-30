/*
 * author:	luo feng
 * date:	2013/10/30
 * source:	LeetCode OJ
 * title:	Single Number II
 * language:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int singleNumber(int A[], int n) 
    {
        int one = 0, two = 0, three = 0;

        int i = 0;
        for(i = 0; i < n; ++i) {
            two |= one & A[i];
            one ^= A[i];
            three = one & two;
            one &= ~three;
            two &= ~three;
        }

        return one;
    }
};

int main(int argc, char *argv[])
{
    int a[] = {1, 5, 1, 1};
    int len = sizeof(a) / sizeof(a[0]);

    Solution sol;
    int single = sol.singleNumber(a, len);
    cout<<"single number: "<<single<<endl;

    return 0;
}
