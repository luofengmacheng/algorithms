/*
 * author:	luo feng
 * date:	2013/12/23
 * source:	LeetCode OJ
 * title:	Permutation Sequence
 * language:	C++
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
    string s;
public:
    int factorial(int n)
    {
        if(n == 1)
            return n;
        return n * factorial(n- 1);
    }

    string get_per(int n, int k)
    {
        if(n == 1)
            return string(1, s[n - 1]);
        int group = 0, n_tmp = n, fac = factorial(n - 1);
        string str;
        if(k % fac)
            group = k / fac + 1;
        else
            group = k / fac;
        k -= fac * (group - 1);
        str += s[group - 1];
        s.erase(s.begin() + group - 1);
        str += get_per(--n, k);
        return str;
    }

    string getPermutation(int n, int k)
    {
        int n_tmp = n;
        char ch = '1';
        s.clear();
        while(n_tmp--) {
            s += ch;
            ++ch;
        }
        return get_per(n, k);
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    for(int i = 1; i <= 24; ++i) {
        string str = sol.getPermutation(4, i);
        cout << str << endl;
    }

    return 0;
}
