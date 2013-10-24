/*
 * author:	luo feng
 * date:	2013/10/23
 * source:	LeetCode OJ
 * title:	Unique Binary Search Trees
 */

#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    int numtree(int left, int right)
    {
        int i = 0, num = 0;
        if(left >= right)
            return 1;

        for(i = left; i <= right; i++) {
            num += numtree(left, i-1) * numtree(i+1, right);
        }
        return num;
    }

    int numTrees(int n)
    {
        return numtree(0, n-1);
    }
};

int main(int argc, char *argv[])
{
    int n = 0;
    cin>>n;
    Solution sol;
    cout<<sol.numTrees(n)<<endl;
    return 0;
}
