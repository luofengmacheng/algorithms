/*
 * author:	luo feng
 * date:	2013/11/6
 * source:	LeetCode OJ
 * title:	Subsets
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > selectn(vector<int> s, int n)
    {
        if(s.size() <= n)
            return vector<vector<int> >(1, s);

        if(n == 0)
            return vector<vector<int> >();

        if(n == 1) {
            vector<vector<int> > vec;
            vector<int> ivec;
            for(vector<int>::iterator iter = s.begin();
                                      iter != s.end(); ++iter) {
                ivec.push_back(*iter);
                vec.push_back(ivec);
                ivec.clear();
            }

            return vec;
        }

        int first_elem = s.front();
        s.erase(s.begin());
        vector<vector<int> > vec1 = selectn(s, n - 1);
        vector<vector<int> > vec2 = selectn(s, n);
        for(vector<vector<int> >::iterator iter = vec1.begin();
                                           iter != vec1.end(); ++iter) {
            (*iter).insert((*iter).begin(), first_elem);
            vec2.push_back(*iter);
        }

        return vec2;
    }

    vector<vector<int> > subsets(vector<int> &S)
    {
        int len = 0;

        sort(S.begin(), S.end());
        vector<vector<int> > vec;
        vector<vector<int> > vec_tmp;
        vec.push_back(vector<int>());
        for(len = 0; len <= S.size(); ++len) {
            vec_tmp = selectn(S, len);
            for(vector<vector<int> >::iterator iter = vec_tmp.begin();
                                               iter != vec_tmp.end(); ++iter) {
                vec.push_back(*iter);
            }
        }

        return vec;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    int arr[3] = {4, 1, 0};
    vector<int> ivec(arr, arr+3);
    vector<vector<int> > vec = sol.subsets(ivec);

    for(vector<vector<int> >::iterator vv_iter = vec.begin();
                                       vv_iter != vec.end(); ++vv_iter) {
        ivec = *vv_iter;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            cout << *iter << "\t";
        }
        cout << endl;
    }

    return 0;
}
