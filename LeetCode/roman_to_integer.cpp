/*
 * author:	luo feng
 * date:	2013/10/23
 * source:	LeetCode OJ
 * title:	Roman to Integer
 * language:	C++
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int romanToInt(string s)
    {
        int i = 0, res = 0;

        char prev = ' ';
        while(i < s.length()) {
            switch(s.at(i)) {
            case 'I':
                res += 1;
                break;
            case 'V':
                if(prev == 'I')
                    res += 3;
                else
                   res += 5;
                break;
            case 'X':
                if(prev == 'I')
                    res += 8;
                else
                    res += 10;
                break;
            case 'L':
                if(prev == 'X')
                    res += 30;
                else
                    res += 50;
                break;
            case 'C':
                if(prev == 'X')
                    res += 80;
                else
                    res += 100;
                break;
            case 'D':
                if(prev == 'C')
                    res += 300;
                else
                    res += 500;
                break;
            case 'M':
                if(prev == 'C')
                    res += 800;
                else
                    res += 1000;
                break;
            default:
                res = 0;
            }
            prev = s[i];
            i++;
        }
        return res;
    }
};

int main(int argc, char *argv[])
{
    string input;
    cin>>input;
    Solution sol;
    int res = sol.romanToInt(input);
    cout<<res<<endl;
}
