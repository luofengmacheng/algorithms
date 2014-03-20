/*
 * author:	luo feng
 * date:	2014/3/18
 * source:	LeetCode OJ
 * title:	Reverse Words in a String
 * language:	C++
 */

#include <iostream>
#include <string>
#include <stack>
#include <iterator>
using namespace std;

class Solution {
public:
	void reverseWords(string &s) {
		if(s.size() == 0)
			return;

		stack<string> sta;
		string str;
		string::iterator beg = s.begin();
		while(beg != s.end() && *beg == ' ')
			++beg;
		while(beg != s.end()) {
			if(*beg == ' ') {
				sta.push(str);
				str.clear();
				++beg;
				while(beg != s.end() && *beg == ' ')
					++beg;
			}
			else {
				str += *beg;
				++beg;
			}
		}
		if(str.size())
		    sta.push(str);
		s.clear();
		while(!sta.empty()) {
			str = sta.top();
			sta.pop();
			s.append(str.begin(), str.end());
			s += " ";
		}
		if(s.size())
		    s.erase(s.end() - 1);
	}
};

int main()
{
	Solution sol;
	string str(" 1 ");
	sol.reverseWords(str);
	cout << str << endl;

	return 0;
}
