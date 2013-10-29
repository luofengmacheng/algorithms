/*
 * author:	luo feng
 * date:	2013/10/28
 * source:	LeetCode OJ
 * title:	Pascal's Triangle II
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void print_vec(vector<int> vec)
{
    for(vector<int>::iterator iter = vec.begin();
                              iter != vec.end(); iter++)
        cout<<*iter<<" ";
    cout<<endl;
}

class Solution {
public:
    vector<int> getRow(int rowIndex)
    {
        vector<int> ivec;
        vector<int> ivec2;

        if(rowIndex == 0)
            return vector<int>(1, 1);
        int i = 0, j = 0;
        ivec.push_back(1);
        for(i = 1; i <= rowIndex; i++) {
            for(j = 0; j <= ivec.size(); j++) {
                if(j == 0 || j == ivec.size()) {
                    ivec2.push_back(1);
                }
                else {
                    ivec2.push_back(ivec[j-1]+ivec[j]);
                }
            }
            ivec = ivec2;
            ivec2.clear();
            print_vec(ivec);
        }
        return ivec;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    vector<int> vec = sol.getRow(3);
    for(vector<int>::iterator iter = vec.begin();
                              iter != vec.end(); iter++) {
        cout<<*iter<<" ";
    }
    cout<<endl;

    return 0;
}
