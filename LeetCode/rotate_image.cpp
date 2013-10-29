/*
 * author:	luo feng
 * date:	2013/10/29
 * source:	LeetCode OJ
 * title:	Rotate Image
 * language:	C++
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int> > &matrix)
    {
        int n = matrix.size();

        int temp = 0;
        int i = 0, j = 0;
        int start = 0, end = n-1;
        int index = 0;
        int width = 0;
        width = n-1;
        while(start < end) {
            for(j = start; j < end; j++) {
                temp = matrix[index][j];
                matrix[index][j] = matrix[width-j][index];
                matrix[width-j][index] = matrix[width-index][width-j];
                matrix[width-index][width-j] = matrix[j][width-index];
                matrix[j][width-index] = temp;
            }
            index++;
            start++;
            end--;
        }
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    vector<vector<int> > vec;
    vector<int> ivec;

    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        ivec.clear();
        for(j = 0; j < 5; j++) {
            ivec.push_back(i*10+j);
            cout<<i*10+j<<"\t";
        }
        vec.push_back(ivec);
        cout<<endl;
    }
    cout<<endl;

    sol.rotate(vec);

    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            cout<<vec[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;

    return 0;
}
