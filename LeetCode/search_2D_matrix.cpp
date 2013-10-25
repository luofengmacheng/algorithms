/*
 * author:	luo feng
 * date:	2013/10/25
 * source:	LeetCode OJ
 * title:	Search a 2D Matrix
 * language:	C++
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        unsigned long left = 0, right = matrix.size()-1;
        vector<int> ivec;
        while(left != right) {
            unsigned long mid = (left+right)/2;
            ivec = matrix[mid];
            if(target < ivec[0])
                right = mid-1;
            else
                left = mid;
        }
        cout<<"fuck"<<endl;
        ivec = matrix[left];
        left = 0;
        right = ivec.size()-1;
        while(left < right) {
            int mid = (left+right)/2;
            if(target <ivec[mid])
                right = mid-1;
            else if(target > ivec[mid])
                left = mid+1;
            else
                return true;
        }

        return false;
    }

    bool searchMatrix1(vector<vector<int> > &matrix, int target)
    {
        vector<int> ivec;
        for(vector<vector<int> >::iterator iter = matrix.begin();
                                           iter != matrix.end(); ++iter) {
            ivec = *iter;
            if(target <= ivec[ivec.size()-1])
                break;
        }

        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            if(target == *iter)
                return true;
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    vector<vector<int> > matrix;
    vector<int> ivec;
    ivec.push_back(1);
    matrix.push_back(ivec);
    ivec.clear();
    ivec.push_back(3);
    matrix.push_back(ivec);
    ivec.clear();
/*    ivec.push_back(23);
    ivec.push_back(30);
    ivec.push_back(34);
    ivec.push_back(50);
    matrix.push_back(ivec);
    ivec.clear();*/

    Solution sol;
    if(sol.searchMatrix1(matrix, 1))
        cout<<"find"<<endl;
    else
        cout<<"cannot find"<<endl;

    return 0;
}
