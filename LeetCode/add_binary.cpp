/*
 * author:	luo feng
 * date:	2013/11/15
 * source:	LeetCode OJ
 * title:	Add Binary
 * language:	C++
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b)
    {
        if(a.size() == 0)
            return b;

        if(b.size() == 0)
            return a;

        string sum;
        int ain = 0, now = 0, tmp = 0;

        string::reverse_iterator a_riter = a.rbegin(), b_riter = b.rbegin();
        for(; a_riter != a.rend() && b_riter != b.rend(); ++a_riter, ++b_riter) {
            tmp = *a_riter-48+*b_riter-48+ain;
            now = tmp % 2;
            if(tmp / 2) {
                ain = 1;
            }
            else {
                ain = 0;
            }
            sum.insert(sum.begin(), 1, now+48);
        }

        if(a_riter == a.rend() && b_riter != b.rend()) {
            while(b_riter != b.rend() && ain == 1) {
                tmp = *b_riter-48+ain;
                now = tmp % 2;
                if(tmp / 2) {
                    ain = 1;
                }
                else {
                    ain = 0;
                }
                sum.insert(sum.begin(), 1, now+48);
                ++b_riter;
            }
            if(b_riter != b.rend()) {
                sum.insert(sum.begin(), b.rend().base(), b_riter.base());
            }
        }

        if(b_riter == b.rend() && a_riter != a.rend()) {
            while(a_riter != a.rend() && ain == 1) {
                tmp = *a_riter-48+ain;
                now = tmp % 2;
                if(tmp / 2) {
                    ain = 1;
                }
                else {
                    ain = 0;
                }
                sum.insert(sum.begin(), 1, now+48);
                ++a_riter;
            }
            if(a_riter != a.rend()) {
                sum.insert(sum.begin(), a.rend().base(), a_riter.base());
            }
        }

        if(ain) {
            sum.insert(sum.begin(), 1, '1');
        }

        return sum;
    }
};

int main(int argc, char *argv[])
{
    string str1("11");
    string str2("1");

    Solution sol;
    cout << sol.addBinary(str1, str2) << endl;

    return 0;
}
