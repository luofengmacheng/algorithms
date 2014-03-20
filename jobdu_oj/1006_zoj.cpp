/*
 * author:	luo feng
 * date:	2014/3/20
 * source:	Jobdu OJ
 * title:	ZOJ problem
 * language:	C++
 */

#include <iostream>
#include <string>
#include <iterator>
using namespace std;

int main()
{
	string str;
	bool flag = false;
	unsigned int o_left = 0, o_mid = 0, o_right = 0;

	while(cin >> str) {
        string::iterator z_iter = str.end(), j_iter = str.end();
        o_left = 0;
        o_mid = 0;
        o_right = 0;
        flag = false;
		for(string::iterator iter = str.begin(); iter != str.end(); ++iter) {
			if(*iter == 'z' && z_iter == str.end() && j_iter == str.end()) {
				z_iter = iter;
			}
			else if(*iter == 'o' && z_iter == str.end() && j_iter == str.end()) {
				++o_left;
			}
			else if(*iter == 'o' && z_iter != str.end() && j_iter == str.end()) {
				++o_mid;
			}
			else if(*iter == 'o' && z_iter != str.end() && j_iter != str.end()) {
				++o_right;
			}
			else if(*iter == 'j' && z_iter != str.end() && j_iter == str.end()) {
				j_iter = iter;
			}
			else {
				cout << "Wrong Answer" << endl;
				flag = true;
				break;
			}
		}

		if(flag)
			continue;

		if(z_iter != str.end() && j_iter != str.end() && (o_mid == 1 || o_mid == 2) && o_right == o_left * o_mid) {
			cout << "Accepted" << endl;
		}
		else {
			cout << "Wrong Answer" << endl;
		}
	}

	return 0;
}