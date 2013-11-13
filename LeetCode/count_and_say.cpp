/*
 * author:	luo feng
 * date:	2013/11/13
 * source:	LeetCode OJ
 * title:	Count and Say
 * language:	C++
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string countAndSay(int n)
    {
        int cnt = 0, i = 0, icnt = 0;
        string s("1"), str;

        for(cnt = 1; cnt < n; ++cnt) {
            icnt = 0;
            if(s.size() == 1) {
                s.append(1, '1');
                continue;
            }
            for(i = 1; i < s.size(); ++i) {
                if(s.at(i-1) != s.at(i) && i != s.size()-1) {
                    ++icnt;
                    str.append(1, static_cast<char>(icnt)+48);
                    str.append(1, s.at(i-1));
                    icnt = 0;
                }
                else if(s.at(i-1) != s.at(i) && i == s.size()-1) {
                    ++icnt;
                    str.append(1, static_cast<char>(icnt)+48);
                    str.append(1, s.at(i-1));
                    str.append(1, '1');
                    str.append(1, s.at(i));
                }
                else if(s.at(i-1) == s.at(i) && i != s.size()-1) {
                    ++icnt;
                }
                else if(s.at(i-1) == s.at(i) && i == s.size()-1) {
                    icnt += 2;
                    str.append(1, static_cast<char>(icnt)+48);
                    str.append(1, s.at(i-1));
                }
            }

            s = str;
            str.clear();
        }

        return s;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;

    cout << sol.countAndSay(5) << endl;

    return 0;
}
