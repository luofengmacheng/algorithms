/*
 * author:	luo feng
 * date:	2013/10/31
 * source:	C++ Primer
 * language:	C++
 * info:	测试数组和vector的有关功能
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef string *pstring;
typedef int *ptint;

int main(int argc, char *argv[])
{
    string *psa = new string[10];
    int *pia = new int[10](5);

    cout<<psa[1]<<endl;
    cout<<pia[1]<<endl;

    delete [] psa;
    delete [] pia;

    int *pia2 = new int[10]();
    cout<<pia2[3]<<endl;

    const size_t arr_size = 6;
    int int_arr[arr_size] = {0, 1, 2, 3, 4, 5};
    vector<int> ivec(int_arr, int_arr + arr_size);
    cout<<ivec[3]<<endl;

    int a[0];
    int *pint = new int[0];

    string s1 = "abc";
    string s2 = "def";
    const pstring cstr = &s1;
    *cstr = s2;
    //cstr = &s2;

    int m = 1, n = 2;
    //const ptint pt;
    //pt = &m;
    //pt = &n;

    return 0;
}
