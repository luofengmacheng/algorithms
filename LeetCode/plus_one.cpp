/*
 * author:	luo feng
 * date:	2013/10/29
 * source:	LeetCode OJ
 * title:	Plus One
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    /*vector<int> plusOne(vector<int> &digits)
    {
        int out = 0;
        int add = 1;
        for(vector<int>::reverse_iterator riter = digits.rbegin();
                                          riter != digits.rend(); riter++) {
            if(*riter+add > 9) {
                *riter = (*riter+add)%10;
                out = 1;
                if(riter == digits.begin()) {
                    //digits.insert(riter, 1);
                    return digits;
                }
            }
            else {
                *riter += add;
                return digits;
            }
        }
    }*/

    vector<int> plusOne1(vector<int> &digits)
    {
        int out = 0;
        int add = 1;
        for(vector<int>::size_type i = digits.size()-1; i >= 0; i--) {
            if(digits[i]+add > 9) {
                digits[i] = (digits[i]+add)%10;
                out = 1;
                add = out;
                if(i == 0) {
                    digits.insert(digits.begin(), 1);
                    return digits;
                }
            }
            else {
                digits[i] += add;
                return digits;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    vector<int> vec;
    int i = 0;
    for(i = 0; i < 3; i++)
        vec.push_back(i);

    vec = sol.plusOne1(vec);
 
    for(i = 0; i < 3; i++)
        cout<<vec[i]<<"\t";

    cout<<endl;

    return 0;
}
