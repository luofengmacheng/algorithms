/*
 * author:	luo feng
 * date:	2014/5/27
 * source:	LeetCode OJ
 * title:	Decode Ways
 * language:	C++
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int numDecodings(string s)
	{
		if(s.size() == 0) {
			return 0;
		}

		vector<int> num;
		num.resize(s.size());

		size_t i = 0;
		for(i = 0; i < s.size(); ++i) {
			if(s[i] < '0' || s[i] > '9') {
				num[i] = 0;
				return 0;
			}
			if(i == 0) {
				if(s[i] == '0') {
					num[i] = 0;
					return 0;
				}
				else {
					num[i] = 1;
				}
				continue;
			}
			if(s[i] == '0') {
				if(s[i-1] == '1' || s[i-1] == '2') {
					num[i] = (i >= 2 ? num[i-2] : 1);
				}
				else {
					num[i] = 0;
					return 0;
				}
			}
			else {
				if(s[i-1] == '1' || s[i-1] == '2' && s[i] >= '1' && s[i] <= '6') {
					num[i] = (i >= 2 ? num[i-2] : 1) + num[i-1];
				}
				else {
					num[i] = num[i-1];
				}
			}
		}

		return num[i-1];
	}
};

int main(int argc, const char *argv[])
{
	string str("110");
	Solution sol;
	cout << sol.numDecodings(str) << endl;

	return 0;
}
