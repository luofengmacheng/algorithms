/*
 * author:	luo feng
 * date:	2013/11/20
 * source:	LeetCode OJ
 * title:	Letter Combinations of a Phone Number
 * language:	C++
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        map<char, string> phone;
        phone.insert(make_pair('2', "abc"));
        phone.insert(make_pair('3', "def"));
        phone.insert(make_pair('4', "ghi"));
        phone.insert(make_pair('5', "jkl"));
        phone.insert(make_pair('6', "mno"));
        phone.insert(make_pair('7', "pqrs"));
        phone.insert(make_pair('8', "tuv"));
        phone.insert(make_pair('9', "wxyz"));
        phone.insert(make_pair('0', " "));

        if(digits.size() == 0)
            return vector<string>(1, "");

        char ch = *(digits.end() - 1);
        digits.erase(digits.end() - 1);

        vector<string> svec = letterCombinations(digits);
        vector<string>::size_type svec_size = svec.size();
        vector<string>::size_type i = 0;

        for(i = 0; i != svec_size; ++i) {
            string str = svec[i];
            string tmp = svec[i];
            for(string::iterator siter = phone[ch].begin();
                                 siter != phone[ch].end(); ++siter) {
                tmp = str;
                svec.push_back(tmp + *siter);
            }
        }

        for(i = 0; i != svec_size; ++i) {
            svec.erase(svec.begin());
        }

        return svec;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    string str("23");
    vector<string> vec = sol.letterCombinations(str);

    for(vector<string>::iterator iter = vec.begin();
                                 iter != vec.end(); ++iter) {
        cout << *iter << endl;
    }
    cout << endl;

    return 0;
}
