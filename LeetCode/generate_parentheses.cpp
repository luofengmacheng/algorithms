/*
 * author:	luo feng
 * date:	2013/12/19
 * source:	LeetCode OJ
 * title:	Generate Parentheses
 * language:	C++
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
    vector<vector<string> > svv;
public:
    vector<string> generate(int n)
    {
        if(!svv[n].empty())
            return svv[n];

        if(n == 0)
            return vector<string>(1, "");

        if(n == 1)
            return vector<string>(1, "()");

        vector<string> left;
        vector<string> right;
        vector<string> svec;
        int i = 0, j = 0, k = 0;
        string str;
        for(k = n - 1; k >= 0; --k) {
            left = generateParenthesis(k);
            right = generateParenthesis(n - 1 - k);
            for(i = 0; i < left.size(); ++i) {
                for(j = 0; j < right.size(); ++j) {
                    str.clear();
                    str.append("(");
                    str.append(left[i]);
                    str.append(")");
                    str.append(right[j]);
                    svec.push_back(str);
                }
            }
        }

        return svec;
    }

    vector<string> generateParenthesis1(int n)
    {
        svv = vector<vector<string> >(n + 1);
        return generate(n);
    }

    vector<string> generateParenthesis(int n)
    {
        if(n == 0) {
            return vector<string>(1, "");
        }

        if(n == 1) {
            return vector<string>(1, "()");
        }

        vector<string> left;
        vector<string> right;
        vector<string> svec;
        int i = 0, j = 0, k = 0;
        string str;
        for(k = n - 1; k >= 0; --k) {
            left = generateParenthesis(k);
            right = generateParenthesis(n - 1 - k);
            for(i = 0; i < left.size(); ++i) {
                for(j = 0; j < right.size(); ++j) {
                    str.clear();
                    str.append("(");
                    str.append(left[i]);
                    str.append(")");
                    str.append(right[j]);
                    svec.push_back(str);
                }
            }
        }

        return svec;
    }
};

void print_str(string str)
{
    cout << str << endl;
}

int main(int argc, char *argv[])
{
    Solution sol;
    vector<string> vec = sol.generateParenthesis1(15);
    for_each(vec.begin(), vec.end(), print_str);

    return 0;
}


别人的方法（不太懂）：
1    class Solution {  
    public:  
        vector<string> generateParenthesis(int n) {  
            // Start typing your C/C++ solution below  
            // DO NOT write int main() function  
            vector<string> ans;  
            getAns(n, 0, 0, "", ans);  
            return ans;  
        }  
      
    private:  
        void getAns(int n, int pos, int neg, string temp, vector<string> &ans) {  
            if (pos < neg) {  
                return;  
            }  
            if (pos + neg == 2 * n) {  
                if (pos == neg) {  
                    ans.push_back(temp);  
                }  
                return;  
            }  
            getAns(n, pos + 1, neg, temp + '(', ans);  
            getAns(n, pos, neg + 1, temp + ')', ans);  
        }  
    };


2 class Solution {
private:
    vector<string> ret;
public:
    void solve(int dep, int maxDep, int leftNum, int leftNumTotal, string s)
    {
        if (leftNumTotal * 2 > maxDep)
            return;
            
        if (dep == maxDep)
        {
            ret.push_back(s);
            return;
        }
        
        for(int i = 0; i < 2; i++)
            if (i == 0)
            {
                solve(dep + 1, maxDep, leftNum + 1, leftNumTotal + 1, s + '(');
            }
            else
            {
                if (leftNum > 0)
                    solve(dep + 1, maxDep, leftNum - 1, leftNumTotal, s + ')');
            }
    }
    
    vector<string> generateParenthesis(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ret.clear();
        solve(0, 2 * n, 0, 0, "");
        return ret;
    }
};  
