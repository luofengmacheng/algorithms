/*
 * author:	luo feng
 * date:	2013/10/24
 * source:	LeetCode OJ
 * title:	Integer to Roman
 * language:	C++
 */

#include <iostream>
#include <map>
#include <utility>
using namespace std;

class Solution {
public:
    string intToRoman(int num)
    {
        int data = num;
        string str;

        map<int, pair<int, string> > map_data;
        map_data.insert(make_pair(0, make_pair(1000, "M")));
        map_data.insert(make_pair(1, make_pair(900, "CM")));
        map_data.insert(make_pair(2, make_pair(500, "D")));
        map_data.insert(make_pair(3, make_pair(400, "CD")));
        map_data.insert(make_pair(4, make_pair(100, "C")));
        map_data.insert(make_pair(5, make_pair(90, "XC")));
        map_data.insert(make_pair(6, make_pair(50, "L")));
        map_data.insert(make_pair(7, make_pair(40, "XL")));
        map_data.insert(make_pair(8, make_pair(10, "M")));
        map_data.insert(make_pair(9, make_pair(9, "IX")));
        map_data.insert(make_pair(10, make_pair(5, "V")));
        map_data.insert(make_pair(11, make_pair(4, "IV")));
        map_data.insert(make_pair(12, make_pair(1, "I")));

        pair<int, string> pair_data;
        while(data) {
            int i = 0;
            while(i < 13) {
               pair_data = map_data[i];
               if(data >= pair_data.first) {
                   str += pair_data.second;
                   data -= pair_data.first;
                   break;
               }
                   i++;
            }
        }

        return str;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    int n = 0;
    cin>>n;
    string s = sol.intToRoman(n);
    cout<<s<<endl;  

    return 0;
}
