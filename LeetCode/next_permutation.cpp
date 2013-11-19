/*
 * author:	luo feng
 * date:	2013/11/19
 * source:	LeetCode OJ
 * title:	Next Permutation
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &num)
    {
        int tmp = 0;
        vector<int>::iterator iter, viter;

        for(viter = num.end()-1;
                                  viter != num.begin(); --viter) {
            if(*viter > *(viter-1)) {
                iter = viter;
                while(iter != num.end() && *iter > *(viter-1))
                    ++iter;
                --iter;
                tmp = *iter;
                num.erase(iter);
                iter = num.insert(viter-1, tmp);
                sort(iter+1, num.end());
                break;
            }
        }

        if(viter == num.begin()) {
            sort(num.begin(), num.end());
        }
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {1, 3, 2};
    int len = sizeof(arr) / sizeof(arr[0]);

    vector<int> n(arr, arr+len);
    Solution sol;
    sol.nextPermutation(n);

    for(vector<int>::iterator iter = n.begin();
                              iter != n.end(); ++iter) {
        cout << *iter << endl;
    }

    return 0;
}
