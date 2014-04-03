/*
 * author:	luo feng
 * date:	2014/4/3
 * source:	LeetCode OJ
 * title:	Evaluate Reverse Polish Notation
 * language:	C++
 */

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include <iterator>
using namespace std;

class Solution
{
public:
	int cal(int l, int r, char op)
	{
		switch(op) {
		case '+':
			return l + r;
		case '-':
			return l - r;
		case '*':
			return l * r;
		case '/':
			return l / r;
		default:
			return -1;
		}
	}

	bool isdata(string str)
	{
		string::iterator iter = str.begin();
		if(*iter == '-') {
			++iter;
		}

		while(iter != str.end() && isdigit(*iter))
			++iter;
		if(iter == str.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	int evalRPN(vector<string> &tokens)
	{
		stack<int> data;
		vector<string>::iterator iter = tokens.begin();

		while(iter != tokens.end()) {
			if(isdigit((*iter)[0]) || iter->size() > 1) {
				data.push(atoi(iter->c_str()));
			}
			else {
				int r = data.top();
				data.pop();
				int l = data.top();
				data.pop();
				int res = cal(l, r, (*iter)[0]);
				data.push(res);
			}
			++iter;
		}

		if(!data.empty())
			return data.top();
		else
			return -1;
	}


};

class Solution2 {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> numeric;
        
        for(auto& t : tokens)
        {
            if (isdigit(t[0]) || t.size()>1)
                numeric.push(atoi(t.c_str()));
            else
            {
                int o1, o2;
                o2 = numeric.top();
                numeric.pop();
                o1 = numeric.top();
                numeric.pop();
                
                switch(t[0])
                {
                    case '+':
                        numeric.push(o1 + o2);
                        break;
                    case '-':
                        numeric.push(o1 - o2);
                        break;
                    case '*':
                        numeric.push(o1 * o2);
                        break;
                    case '/':
                        numeric.push(o1 / o2);
                        break;
                }
            }
        }
        
        return numeric.top();
    }
};

int main(int argc, char const *argv[])
{
	vector<string> svec;
	svec.push_back("-1");
	svec.push_back("1");
	svec.push_back("*");
	svec.push_back("-1");
	svec.push_back("+");
	//svec.push_back("2");
	Solution sol;
	cout << sol.evalRPN(svec) << endl;

	Solution2 sol2;
	cout << sol2.evalRPN(svec) << endl;

	return 0;
}