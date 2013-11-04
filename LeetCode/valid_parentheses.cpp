/*
 * author:	luo feng
 * date:	2013/11/4
 * source:	LeetCode OJ
 * title:	Valid Parentheses
 * language:	C++
 */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s)
    {
        stack<char> sta;

        for(string::iterator iter = s.begin();
                             iter != s.end(); ++iter) {
            switch(*iter) {
                case '(': case '{': case '[':
                    sta.push(*iter);
                    break;
                case ')':
                    if(sta.empty() || !sta.empty() && sta.top() != '(')
                        return false;
                    sta.pop();
                    break;
                case '}':
                    if(sta.empty() || !sta.empty() && sta.top() != '{')
                        return false;
                    sta.pop();
                    break;
                case ']':
                    if(sta.empty() || !sta.empty() && sta.top() != '[')
                        return false;
                    sta.pop();
                    break;
                default:
                    break;
            }
        }

        if(sta.empty())
            return true;
        else
            return false;
    }
};

int main(int argc, char *argv[])
{
    string s("([)]");
    Solution sol;

    if(sol.isValid(s)) {
        cout<<"Valid Parentheses!"<<endl;
    }
    else {
        cout<<"Invalid Parentheses!"<<endl;
    }

    return 0;
}
