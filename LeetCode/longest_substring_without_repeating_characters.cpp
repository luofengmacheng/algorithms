#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s)
	{
		if(s.empty())
			return 0;

		set<char> hash;
		unsigned long n = 0;
		string::iterator start = s.begin();
		string::iterator iter = s.begin();

		while(start != s.end()) {
			if(iter != s.end() && hash.find(*iter) == hash.end()) {
				hash.insert(*iter);
				++iter;
			}
			else {
				if(hash.size() > n) {
					n = hash.size();
				}
				if(iter == s.end())
					break;
				hash.clear();
				++start;
				iter = start;
			}
		}
		return n;
	}

	int lengthOfLongestSubstring2(string s)
	{
		if(s.empty())
			return 0;

		unsigned long n = 0;
		string::iterator start = s.begin();
		string::iterator iter = s.begin(), find_iter;

		while(start != s.end()) {
			if(iter != s.end() && (find_iter = find(start, iter, *iter)) == iter) {
				++iter;
			}
			else {
				if(iter - start > n) {
					n = iter - start;
				}
				if(iter == s.end())
					break;
				start = find_iter + 1;
				iter = start;
			}
		}
		return n;
	}
};

int main()
{
	string str("chzdflilrjqfnxz");
	Solution sol;
	cout << sol.lengthOfLongestSubstring(str) << endl;
	cout << sol.lengthOfLongestSubstring2(str) << endl;

	return 0;
}