/*
 * author:	luo feng
 * date:	2013/12/10
 * source:	LeetCode OJ
 * title:	Restore IP Address
 * language:	C++
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct tri_counter{
    int val[4];
    tri_counter()
    {
        val[0] = 1;
        val[1] = 1;
        val[2] = 1;
        val[3] = 1;
    }

    tri_counter& operator++()
    {
        int cnt = 3;

        for(cnt = 3; cnt >= 0; --cnt) {
            if(val[cnt] < 3) {
                ++val[cnt];
                return *this;
            }
            else {
                val[cnt] = 1;
            }
        }
        return *this;
    }

    bool finish()
    {
        if(val[0] != 3 || val[1] != 3 || val[2] != 3 || val[3] != 3)
            return false;
        return true;
    }
};

class Solution {
public:
    int getValue(string::iterator beg, int cnt)
    {
        int val = 0;
        int i = 0;
        while(i < cnt) {
            val = val * 10 + *beg - '0';
            ++beg;
            ++i;
        }

        if(val >= 0 && val <= 255) {
            if(val >= 0 && val <= 9 && cnt != 1) {
                return -1;
            }
            if(val >= 10 && val <= 99 && cnt != 2) {
                return -1;
            }
            if(val >= 100 && val <= 255 && cnt != 3) {
                return -1;
            }
            return val;
        }
        else {
            return -1;
        }
    }

    vector<string> restoreIpAddress(string s)
    {
        if(s.size() < 4 || s.size() > 12) {
            return vector<string>();
        }

        tri_counter tc;
        int ip_val = 0;
        bool flag = true;
        string str;
        ostringstream os(str);
        vector<string> svec;
        string::iterator iter = s.begin();
        while(!tc.finish()) {
            if(tc.val[0] + tc.val[1] + tc.val[2] + tc.val[3] != s.size()) {
                ++tc;
                continue;
            }
            iter = s.begin();
            flag = true;
            os.str("");
            for(int i = 0; i < 4; ++i) {
                if((ip_val = getValue(iter, tc.val[i])) == -1) {
                    flag = false;
                    break;
                }
                iter += tc.val[i];
                os << ip_val;
                if(i != 3) {
                    os << '.';
                }
            }
            if(flag && iter == s.end()) {
                cout << tc.val[0] << " " << tc.val[1] << " " << tc.val[2] << " " << tc.val[3] << endl;
                cout << os.str() << endl;
                svec.push_back(os.str());
            }
            ++tc;
        }
        iter = s.begin();
        flag = true;
        os.str("");
        for(int i = 0; i < 4; ++i) {
            if((ip_val = getValue(iter, tc.val[0])) == -1) {
                flag = false;
                break;
            }
            iter += tc.val[i];
            os << ip_val;
            if(i != 3) {
                os << '.';
            } 
        }
        if(flag && iter == s.end()) {
            cout << tc.val[0] << " " << tc.val[1] << " " << tc.val[2] << " " << tc.val[3] << endl;
            cout << os.str() << endl;
            svec.push_back(os.str());
        }

        return svec;
    }
};

void print_vec(string str)
{
    cout << str << endl;
}

int main(int argc, char *argv[])
{
    Solution sol;
    string str("111111111");
    vector<string> svec = sol.restoreIpAddress(str);
    cout << "result:" << endl;
    for_each(svec.begin(), svec.end(), print_vec);

    return 0;
}
