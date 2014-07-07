/*
 * author:	luo feng
 * date:	2014/7/7
 * source:	July的微软面试100题系列
 * title:	25.在字符串中找出连续最长的数字串
 * language:	C++
 * 详细题目：	在字符串中找出连续最长的字符串，并把这个字符串的长度返回。
 * 并把这个最长数字串赋给其中一个参数outputstr所指内存。
 */

#include <iostream>

using namespace std;

int continumax(char *outputstr, char *inputstr)
{
	char *str = inputstr;
	int len = 0, maxlen = 0;
	char *cur = NULL, *maxcur = NULL;

	while(*str != '\0') {
		if(*str >= '0' && *str <= '9') {
			if(len == 0) { // 长度为0说明新发现了一个数字
				cur = str;
				len = 1;
			}
			else {
				++len;
			}
		}
		else {
			if(len > maxlen) {
				maxlen = len;
				maxcur =cur;
			}
			len = 0;
		}
		++str;
	}

	int i = 0;
	while(i < maxlen) {
		*outputstr++ = *maxcur++;
		++i;
	}
	*outputstr = '\0';

	return maxlen;
}

int main(int argc, char const *argv[])
{
	char istr[] = "abcd12345e123456789d125ss";
	char ostr[20] = "";
	cout << continumax(ostr, istr) << endl;
	cout << ostr << endl;

	return 0;
}
