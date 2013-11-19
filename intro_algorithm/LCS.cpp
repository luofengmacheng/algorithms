/*
 * author:	luo feng
 * date:	2013/11/19
 * source:	Introduction to Algorithm
 * title:	Longest Common Subsequence
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> LCS(vector<int> &x, vector<int> &y)
    {
        vector<int>::size_type x_size = x.size();
        vector<int>::size_type y_size = y.size();

        if(x_size == 0 || y_size == 0)
            return vector<int>();

        int **e = new int*[x_size];
        int i = 0, j = 0;
        for(i = 0; i < x_size; ++i) {
            e[i] = new int[y_size];
            fill_n(e[i], y_size, 0);
            for(j = 0; j < y_size; ++j) {
                if(x[i] == y[j]) {
                    if(i == 0 && j == 0) {
                        e[i][j] = 1;
                    }
                    else if(i == 0) {
                        e[i][j] = e[i][j-1] + 1;
                    }
                    else if(j == 0) {
                        e[i][j] = e[i-1][j] + 1;
                    }
                    else {
                        e[i][j] = e[i-1][j-1] + 1;
                    }
                }
                else {
                    if(i == 0 && j == 0) {
                        e[i][j] = 0;
                    }
                    else if(i == 0) {
                        e[i][j] = e[i][j-1];
                    }
                    else if(j == 0) {
                        e[i][j] = e[i-1][j];
                    }
                    else {
                        e[i][j] = max(e[i-1][j], e[i][j-1]);
                    }
                }
            }
        }

        cout << "length of LCS: " << e[x_size-1][y_size-1] << endl;

        i = x_size-1;
        j = y_size-1;
        vector<int> ivec;
        while(i >= 0 && j >= 0) {
            if(x[i] == y[j]) {
                ivec.push_back(x[i]);
                --i;
                --j;
            }
            else {
                if(i == 0) {
                    --j;
                }
                else if(j == 0) {
                    --i;
                }
                else if(e[i-1][j] >= e[i][j-1]) {
                    --i;
                }
                else {
                    --j;
                }
            }
        }
        reverse(ivec.begin(), ivec.end());

        for(i = 0; i < x_size; ++i)
            delete[] e[i];

        delete[] e;

        return ivec;
    }
};

int main(int argc, char *argv[])
{
    int a[] = {2, 5, 6, 9, 3};
    int a_len = sizeof(a) / sizeof(a[0]);
    int b[] = {2, 3, 1, 9};
    int b_len = sizeof(b) / sizeof(b[0]);

    vector<int> a_v(a, a+a_len);
    vector<int> b_v(b, b+b_len);
    Solution sol;
    vector<int> ivec = sol.LCS(a_v, b_v);

    cout << "LCS : "; 
    for(vector<int>::iterator iter = ivec.begin();
                              iter != ivec.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}
