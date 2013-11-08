/*
 * author:	luo feng
 * date:	2013/11/8
 * source:	LeetCode OJ
 * title:	Length of Last Word
 * language:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(const char *s)
    {
        int len = 0;

        while(*s) {
            if(*s == ' ') {
                len = 0;
                while(*s && *s == ' ')
                    ++s;
            }
            ++len;
            ++s;
        }

        return len;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    cout << sol.lengthOfLastWord("Hello World") << endl;

    return 0;
}
