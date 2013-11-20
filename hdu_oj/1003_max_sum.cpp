/*
 * author:	luo feng
 * date:	2013/11/20
 * source:	HDU OJ
 * title:	1003 Max Sum
 * category:	Dynamic Programming
 * language:	C++
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n = 0;
    cin >> n;

    int max_sum = 0;
    int b = 0;
    int i = 0, j = 0;

    while(n--) {
        while(cin >> b) {
            if(b > 0) {
                b += a;
                
            }
            else {
                b = a;
            }
            if(b > max_sum) {
                max_sum = b;
            }
        }
    }

    return 0;
}
