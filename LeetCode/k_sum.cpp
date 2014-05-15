/*
 * author:	luo feng
 * date:	2014/5/13
 * source:	LeetCode
 * title:	K sum
 * reference:	http://tech-wonderland.net/blog/summary-of-ksum-problems.html
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
	vector<vector<int> > findZeroSumInSortedArr(vector<int> num, int begin, int count, int target)
	{
		vector<vector<int> > ret;
		vector<int> tuple;
		set<int> visited;
		if(count == 2) {
			int i = begin, j = num.size() - 1;
			while(i < j) {
				int sum = num[i] + num[j];
				if(sum == target && visited.find(num[i]) == visited.end()) {
					tuple.clear();
					visited.insert(num[i]);
					visited.insert(num[j]);
					tuple.push_back(num[i]);
					tuple.push_back(num[j]);
					ret.push_back(tuple);
					++i;
					--j;
				}
				else if(sum < target) {
					++i;
				}
				else {
					--j;
				}
			}
		}
		else {
			for(int i = begin; i < num.size(); ++i) {
				if(visited.find(num[i]) == visited.end()) {
					visited.insert(num[i]);
					vector<vector<int> > subret = findZeroSumInSortedArr(num, i + 1, count - 1, target - num[i]);
					if(!subret.empty()) {
						for(int j = 0; j < subret.size(); ++j) {
							subret[j].insert(subret[j].begin(), num[i]);
						}

						ret.insert(ret.end(), subret.begin(), subret.end());
					}
				}
			}
		}

		return ret;
	}
};

int main(int argc, char const *argv[])
{


	return 0;
}