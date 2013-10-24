/*
 * author:	luo feng
 * date:	2013/10/24
 * source:	LeetCode OJ
 * title:	Pascal's Triangle
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > generate(int numRows)
    {
        if(numRows == 0)
            return vector<vector<int> >(0);

        vector<vector<int> > ivec;
        int i = 0, j = 0;
        for(i = 0; i < numRows; i++) {
            vector<int> vec;
            for(j = 0; j < i+1; j++) {
                if(j == 0 || j == i)
                    vec.push_back(1);
                else
                    vec.push_back(ivec[i-1][j-1] + ivec[i-1][j]);
            }
            ivec.push_back(vec);
        }
        for(i = 0; i < numRows; i++) {
            for(j = 0; j < i+1; j++) {
               cout<<ivec[i][j];
            }
            cout<<endl;
        }
        return ivec;
    }
};

int main(int argc, char *argv[])
{
    //vector<vector<int> > vec;
    Solution sol;
    vector<vector<int> > vec(sol.generate(5));
    cout<<"ab"<<endl;
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < i+1; j++)
            cout<<vec[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}
