/*
 * author:	luo feng
 * date:	2014/5/13
 * source:	LeetCode
 * title:	KMP algorithm(http://www.ituring.com.cn/article/59881,http://kb.cnblogs.com/page/176818/)
 * language:	C++
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void get_next(const string& str, vector<int> &next)
{
	next[0] = -1;
	int j = -1;

	for(int i = 1; i < str.size(); ++i) {
		while(str[i] != str[j + 1] && j >= 0) {
			j = next[j];
		}
		if(str[i] == str[j + 1]) {
			++j;
		}
		next[i] = j;
	}
}

int kmp(const string& str1, const string& str2)
{
	if(str1.size() < str2.size()) {
		return -1;
	}
	
	vector<int> next(str2.size(), 0);
	get_next(str2, next);
	copy(next.begin(), next.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	int j = -1;
	for(int i = 0; i < str1.size(); ++i) {
		while(str1[i] != str2[j + 1] && j >= 0) {
			j = next[j];
		}
		if(str1[i] == str2[j + 1]) {
			++j;
		}
		if(j == str2.size() - 1) {
			return i - j;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	string str1("ababcdabd"), str2("abdabdc");
	cout << kmp(str1, str2) << endl;

	return 0;
}