/*
 * author:	luo feng
 * date:	2014/3/27
 * source:	LeetCode OJ
 * title:	Word Break II
 * language:	C++
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <set>
#include <iterator>
using namespace std;

class Solution {
public:
	vector<string> word(string::iterator beg, string::iterator end, unordered_set<string> &dict, set<string> &not_seg)
	{
		if(beg == end) {
			return vector<string>();
		}

		vector<string> svec;
		string::iterator sep = beg + 1;
		if(dict.find(string(beg, end)) != dict.end()) {
			svec.push_back(string(beg, end));
		}
		while(sep != end) {
			if(dict.find(string(beg, sep)) != dict.end()) {
				if(not_seg.find(string(sep, end)) == not_seg.end()) {
					vector<string> tmp = word(sep, end, dict, not_seg);
					if(tmp.empty()) {
						not_seg.insert(string(sep, end));
					}
					else {
						for(vector<string>::iterator iter = tmp.begin(); iter != tmp.end(); ++iter) {
							svec.push_back(string(beg, sep) + " " + *iter);
						}
					}
				}
			}
			++sep;
		}
		return svec;
	}

	vector<string> wordBreak(string s, unordered_set<string> &dict)
	{
		set<string> not_seg;
		return word(s.begin(), s.end(), dict, not_seg);
	}
};

void print(string s)
{
	cout << s << endl;
}

int main()
{
	Solution sol;
	string s("aaaaaaa");
	unordered_set<string> us;
	us.insert("aaaa");
	us.insert("aa");
	us.insert("a");
	//us.insert("sand");
	//us.insert("dog");
	//us.insert("cat");
	vector<string> svec = sol.wordBreak(s, us);
	for_each(svec.begin(), svec.end(), print);

	return 0;
}