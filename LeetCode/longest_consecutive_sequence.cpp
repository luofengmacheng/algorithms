/*
 * author:	luo feng
 * date:	2014/4/8
 * source:	LeetCode OJ
 * title:	Longest Consecutive Sequence
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
using namespace std;

class Solution {
	unordered_set<int> hash;
public:
	enum DIRECTION{
		forward, backward
	};

	int find_consecutive(int cur, DIRECTION dir)
	{
		int len = 0;

		unordered_set<int>::iterator iter;
		while((iter = hash.find(cur)) != hash.end()) {
			++len;
			hash.erase(iter);
			if(dir == forward) {
				++cur;
			}
			else if(dir == backward) {
				--cur;
			}
		}

		return len;
	}

	int longestConsecutive(vector<int> &num)
	{
		for(vector<int>::iterator iter = num.begin();
			                      iter != num.end(); ++iter) {
			hash.insert(*iter);
		}

		int len = 0;

		for(vector<int>::iterator iter = num.begin();
			                      iter != num.end(); ++iter) {
		    len = max(find_consecutive(*iter, forward) + find_consecutive(*iter - 1, backward), len);
		}

		return len;
	}
};

int main(int argc, char const *argv[])
{
	int arr[] = {100, 4, 200, 1, 3, 2};
	vector<int> ivec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Solution sol;
	cout << sol.longestConsecutive(ivec) << endl;

	return 0;
}