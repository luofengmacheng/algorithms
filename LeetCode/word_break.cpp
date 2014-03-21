/*
 * author:	luo feng
 * date:	2014/3/21
 * source:	LeetCode OJ
 * title:	Word Break
 * language:	C++
 */

#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

class Solution {
public:
	bool word(string::iterator beg, string::iterator end,
		unordered_set<string> &dict) 
	{
		if(beg == end) {
			return true;
		}

		if(dict.find(string(beg, end)) != dict.end()) {
			return true;
		}

		string::iterator sep = beg + 1;
		while(sep != end) {
			if(dict.find(string(beg, sep)) != dict.end() && word(sep, end, dict)) {
				return true;
			}
			++sep;
		}
		return false;
	}

	bool wordBreak(string s, unordered_set<string> &dict)
	{
		if(s.empty())
			return false;
		return word(s.begin(), s.end(), dict);
	}

	bool word2(string::iterator beg, string::iterator end, unordered_set<string> &dict, set<string> &not_seg)
	{
		if(beg == end)
			return true;

		if(dict.find(string(beg, end)) != dict.end()) {
			return true;
		}

		string::iterator sep = beg + 1;
		while(sep != end) {
			if(dict.find(string(beg, sep)) != dict.end() && dict.find(string(sep, end)) != dict.end()) {
				return true;
			}
			if(dict.find(string(beg, sep)) != dict.end()) {
				if(not_seg.find(string(sep, end)) == not_seg.end()) {
					if(word2(sep, end, dict, not_seg)) {
						return true;
					}
					else {
						not_seg.insert(string(sep, end));
					}
				}
			}
			++sep;
		}
		not_seg.insert(string(beg, end));

		return false;
	}

	bool wordBreak2(string s, unordered_set<string> &dict)
	{
		if(s.empty())
			return false;

		set<string> not_seg;

		return word2(s.begin(), s.end(), dict, not_seg);
	}
};

int main()
{
	string str("abcde");
	unordered_set<string> dict;
	dict.insert("ab");
	//dict.insert("bc");
	dict.insert("abc");
	//dict.insert("e");
	dict.insert("de");
	Solution sol;
	cout << boolalpha << sol.wordBreak(str, dict) << endl;

	return 0;
}