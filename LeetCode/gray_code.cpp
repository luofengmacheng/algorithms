/*
 * author:	luo feng
 * date:	2013/10/24
 * source:	LeetCode OJ
 * title:	Gray Code
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> grayCode1(int n)
    {
        vector<int> vec;

        if(n == 0) {
            vec.push_back(0);
            return vec;
        }

        vec = grayCode(n-1);
        int size = vec.size();
        int i = 0;
        for(i = size-1; i >= 0; i--) {
            vec.push_back(vec.at(i) | (1<<(n-1)));
        }

        return vec;
    }

    vector<int> grayCode(int n)
    {
        vector<int> vec;

        if(n == 0)
            return vector<int>(0);

        if(n == 1) {
            vec.push_back(0);
            vec.push_back(1);
            return vec;
        }

        vec = grayCode(n-1);
        vector<int>::iterator iter;
        for(iter = vec.begin(); iter != vec.end(); ++iter) {
            (*iter) <<= 1;
        }

        int i = 0;
        int size = vec.size();
        for(i = size-1; i >= 0; i--) {
            vec.push_back(vec.at(i)+1);
        }
        return vec;
    }
};

int main(int argc, char *argv[])
{
    vector<int> ivec;
    Solution sol;
    ivec = sol.grayCode1(3);
    int i = 0;
    for(i = 0; i < ivec.size(); i++)
        cout<<ivec.at(i)<<"\t";
    cout<<endl;  

    return 0;
}
