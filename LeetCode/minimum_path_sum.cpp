/*
 * author:	luo feng
 * date:	2013/11/19
 * source:	LeetCode OJ
 * title:	Minimum Path Sum
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int> > &grid)
    {
        vector<vector<int> >::size_type grid_size = grid.size();

        if(grid_size == 0)
            return 0;

        vector<vector<int> >::size_type arr_size = grid[0].size();
        int *e = new int[arr_size];
        int *tmp = new int[arr_size];

        for(int i = 0; i < grid_size; ++i) {
            for(int j = 0; j < arr_size; ++j) {
                if(i == 0 && j == 0) {
                    tmp[j] = grid[i][j];
                }
                else if(i == 0) {
                    tmp[j] = tmp[j-1] + grid[i][j];
                }
                else if(j == 0) {
                    tmp[j] = e[j] + grid[i][j];
                }
                else {
                    tmp[j] = min(tmp[j-1], e[j]) + grid[i][j];
                }
            }
            copy(tmp, tmp+arr_size, e);
        }

        int minsum = e[arr_size-1];

        delete[] e;
        delete[] tmp;

        return minsum;
    }
};

int main(int argc, char *argv[])
{
    

    return 0;
}
