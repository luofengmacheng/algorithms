/*
 * author:	luo feng
 * date:	2014/4/9
 * source:	LeetCode OJ
 * title:	Set Matrix Zeroes
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
	void setZeroes(vector<vector<int> > &matrix)
	{
		int row = matrix.size();
		if(row == 0) {
			return;
		}

		int col = matrix[0].size();
		if(col == 0) {
			return;
		}

		bool r0 = false, c0 = false;
		int i = 0;
		for(i = 0; i < col; ++i) {
			if(matrix[0][i] == 0) {
				r0 = true;
				break;
			}
		}

		for(i = 0; i < row; ++i) {
			if(matrix[i][0] == 0) {
				c0 = true;
				break;
			}
		}

		int j = 0;
		for(i = 1; i < row; ++i) {
			for(j = 1; j < col; ++j) {
				if(matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		for(i = 1; i < row; ++i) {
			for(j = 1; j < col; ++j) {
				if(matrix[i][0] == 0 || matrix[0][j] == 0) {
					matrix[i][j] = 0;
				}
			}
		}

		if(r0) {
			for(j = 0; j < col; ++j) {
				matrix[0][j] = 0;
			}
		}
		if(c0) {
			for(i = 0; i < row; ++i) {
				matrix[i][0] = 0;
			}
		}
	}
};

int main(int argc, char const *argv[])
{
	vector<vector<int> > vvec;
	vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vvec.push_back(vec);
	Solution sol;
	sol.setZeroes(vvec);
	for(int i = 0; i < vvec.size(); ++i) {
		vector<int> tmp = vvec[i];
		copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
	}

	return 0;
}