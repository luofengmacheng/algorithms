/*
 * author:	luo feng
 * date:	2014/5/27
 * source:	LeetCode OJ
 * title:	Spiral Matrix
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int> > &matrix)
	{
		vector<int> result;
		if(matrix.size() == 0) {
			return result;
		}

		int startx = 0, endx = matrix[0].size() - 1;
		int starty = 0, endy = matrix.size() - 1;

		cout << "endx :" << endx << endl;
		cout << "endy :" << endy << endl;

		int i = 0;
		while(true) {

			for(i = startx; i <= endx; ++i) {
				result.push_back(matrix[starty][i]);
			}
			if(++starty > endy) {
				break;
			}

			for(i = starty; i <= endy; ++i) {
				result.push_back(matrix[i][endx]);
			}
			if(--endx < startx) {
				break;
			}

			for(i = endx; i >= startx; --i) {
				result.push_back(matrix[endy][i]);
			}
			if(--endy < starty) {
				break;
			}

			for(i = endy; i >= starty; --i) {
				result.push_back(matrix[i][startx]);
			}
			if(++startx > endx) {
				break;
			}
		}

		return result;
	}
};

int main(int argc, const char *argv[])
{
	int arr0[] = {1, 2, 3};
	int arr1[] = {4, 5, 6};
	int arr2[] = {7, 8, 9};
	int arr3[] = {10, 11, 12};
	vector<int> vec0(arr0, arr0 + 3);
	vector<int> vec1(arr1, arr1 + 3);
	vector<int> vec2(arr2, arr2 + 3);
	vector<int> vec3(arr3, arr3 + 3);

	vector<vector<int> > matrix;
	matrix.push_back(vec0);
	matrix.push_back(vec1);
	matrix.push_back(vec2);
	matrix.push_back(vec3);
	
	Solution sol;
	vector<int> res = sol.spiralOrder(matrix);
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));

	return 0;
}
