/*
 * author:	luo feng
 * date:	2014/7/2
 * source:	LeetCode OJ
 * title:	String to Integer(atoi)
 * language:	C++
 */

#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
	int atoi(const char *str)
	{
		int i = 0;
		int num = 0;
		int flag = 0;
		bool flag_set = false;
		bool valid = false;

		while(isspace(str[i])) {
			++i;
		}
		if(str[i] == '-') {
			flag = 1;
			++i;
			flag_set = true;
		}
		else if(str[i] == '+') {
			++i;
			flag_set = true;
		}
		if((str[i] == '+' || str[i] == '-') && flag_set) {
			return 0;
		}

		while(str[i] != '\0') {
			if(isalnum(str[i]) && !isalpha(str[i])) {
				if(INT_MAX / 10 < num) {
					return flag ? INT_MIN : INT_MAX;
				}
				if(INT_MAX - num * 10 < str[i] - '0') {
					return flag ? INT_MIN : INT_MAX;
				}
				num = num * 10 + str[i] - '0';
				valid = true;
				//cout << str[i] << endl;
				//cout << num << endl;
			}
			else if(valid) {
				return flag ? -num : num;
			}
			else if(!valid) {
				return 0;
			}
			++i;
		}

		return flag ? -num : num;
	}
};

int main(int argc, char const *argv[])
{
	const char *s1 = "  "; // 0
	const char *s2 = ""; // 0
	const char *s3 = "-+1"; // 0
	const char *s4 = "  123"; // 123
	const char *s5 = " -987"; // -987
	const char *s6 = " 345bac"; // 345
	const char *s7 = "9999999999999999999999999"; // INT_MAX
	const char *s8 = " 10522545459"; // INT_MAX
	const char *s9 = "+1"; // -1
	Solution sol;
	/*cout << sol.atoi(s1) << endl;
	cout << sol.atoi(s2) << endl;
	cout << sol.atoi(s3) << endl;
	cout << sol.atoi(s4) << endl;
	cout << sol.atoi(s5) << endl;
	cout << sol.atoi(s6) << endl;
	cout << sol.atoi(s7) << endl;*/
	cout << sol.atoi(s8) << endl;
	cout << sol.atoi(s9) << endl;

	return 0;
}