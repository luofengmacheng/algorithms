/*
 * author:	luo feng
 * date:	2014/5/13
 * source:	LeetCode
 * title:	3Sum Closest
 * language:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
	int threeSumClosest(vector<int> &num, int target)
	{
		sort(num.begin(), num.end());

		int ret = 0;

		for(int i = 0; i < num.size(); ++i) {
			int j = i + 1;
			int k = num.size() - 1;

			while(j < k) {
				int sum = num[i] + num[j] + num[k];
				if(first) {
					ret = sum;
					first = false;
				}
				else {
					if(abs(sum - target) < abs(ret - target)) {
						ret = sum;
					}
				}

				if(ret == target) {
					return ret;
				}

				if(sum > target) {
					--k;
				}
				else {
					++j;
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