/*
 * author:	luo feng
 * date:	2014/7/2
 * source:	LeetCode OJ
 * title:	String to Integer(atoi)
 * language:	C++
 * 说明：	将字符串转换为数字是常用的库函数atoi。真正实现的话，需要考虑的问题很多，在这里根据题目给的提示来考虑。
 * case 1:	滤掉字符串起始位置的空白字符；
 * case 2:	在字符串后面可以包含无效字符，不影响；
 * case 3:	前面的有效字符如果不能构成合法的数字，字符串只包含空白空白字符或者字符串是空，就返回0；
 * case 4:	如果得到的数字超过了所能表示的范围，就返回INT_MAX或者INT_MIN。
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
	const char *s9 = "-1"; // -1
	Solution sol;
	cout << sol.atoi(s1) << endl;
	cout << sol.atoi(s2) << endl;
	cout << sol.atoi(s3) << endl;
	cout << sol.atoi(s4) << endl;
	cout << sol.atoi(s5) << endl;
	cout << sol.atoi(s6) << endl;
	cout << sol.atoi(s7) << endl;
	cout << sol.atoi(s8) << endl;
	cout << sol.atoi(s9) << endl;

	return 0;
}
