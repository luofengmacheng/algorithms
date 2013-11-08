/*
 * author:	luo feng
 * date:	2013/11/8
 * source:	LeetCode OJ
 * title:	Longest Common Prefix
 * language:	C++
 */

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    string strprefix(string str1, string str2)
    {
        int i = 0;
        string str;

        while(i < str1.size() && i < str2.size() && str1.at(i) == str2.at(i)) {
            str += str1.at(i);
            ++i;
        }

        return str;
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        if(strs.size() == 0)
            return string();

        string str = strs[0];

        for(vector<string>::iterator iter = strs.begin();
                                     iter != strs.end(); ++iter) {
            str = strprefix(str, *iter);
        }

        return str;
    }
};

int main(int argc, char *argv[])
{
    string strs[] = {"abc", "abcd", "ab"};
    vector<string> vec(strs, strs+3);
    Solution sol;
    cout << sol.longestCommonPrefix(vec) << endl;

    return 0;
}
