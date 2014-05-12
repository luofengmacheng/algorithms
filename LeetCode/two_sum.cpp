/*
 * author:	luo feng
 * date:	2014/5/12
 * source:	APUE
 * title:	Two Sum
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

bool compare(pair<int, int> lh, pair<int, int> rh)
{
	return lh.first < rh.first;
}

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target)
	{
		vector<pair<int, int> > num;
		int index = 1;
		for(vector<int>::iterator iter = numbers.begin();
			                      iter != numbers.end(); ++iter, ++index) {
			num.push_back(make_pair(*iter, index));
		}
		sort(num.begin(), num.end(), compare);
		int i = 0, j = num.size() - 1;
		vector<int> res;
		for(; i < j;) {
			if(num[i].first + num[j].first == target) {
				res.push_back(num[i].second);
				res.push_back(num[j].second);
				++i;
			}
			else if(num[i].first + num[j].first < target) {
				++i;
			}
			else {
				--j;
			}
		}
		return res;
	}
};

void print(int i)
{
	cout << i << "\t";
}

int main(int argc, char const *argv[])
{
	int arr[] = {5, 6, 1, 4, 7, 9, 8};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Solution sol;
	int target = 10;
	vector<int> res = sol.twoSum(vec, target);
	for_each(res.begin(), res.end(), print);

	return 0;
}
