/*
 * author:	luo feng
 * date:	2013/10/25
 * source:	LeetCode OJ
 * title:	Spiral Matrix II
 * language:	C++
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > generateMatrix(int n)
    {
        vector<vector<int> > vec(n, vector<int>(n));

        int i = 0, j = 0;
        int count = 1;
        int index = 0;
        int start = 0, end = n-1;
        while(count <= n*n) {
            for(i = index, j = start; j <= end && count <= n*n; j++)
                vec[i][j] = count++;

            for(j = n-1-index, i = start+1; i < end && count <= n*n; i++)
                vec[i][j] = count++;
 
            for(i = n-1-index, j = end; j >= start && count <= n*n; j--)
                vec[i][j] = count++;
 
            for(j = index, i = end-1; i >= start+1 && count <= n*n; i--)
                vec[i][j] = count++;

            index++;
            start++;
            end--;
        }

        return vec;                                  
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    vector<vector<int> > vec;
    vec = sol.generateMatrix(4);

    int i = 0, j = 0;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++)
            cout<<vec[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl; 

    return 0;
}
