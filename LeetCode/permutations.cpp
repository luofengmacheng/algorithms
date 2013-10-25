/*
 * author:	luo feng
 * date:	2013/10/25
 * source:	LeetCode OJ
 * title:	Permutations
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<vector<int> > permute(vector<int> &num)
    {
        vector<vector<int> > vec;
        vector<int> ivec(num);

        int size = num.size();
        if(size == 1) {
            vec.push_back(num);
            return vec;
        }
       
        int data = ivec.back();
        ivec.pop_back();

        vec = permute(ivec);
        int vec_size = vec.size();
        ivec.clear();
        vector<int> tmp_vec;
        vector<int>::iterator iter;
        unsigned int i = 0, j = 0;
        for(i = 0; i < vec_size; i++) {
            ivec = vec[i];
            int ivec_size = ivec.size();
            for(j = 0; j < ivec_size+1; j++) {
                tmp_vec = ivec;
                iter = tmp_vec.begin()+j;
                tmp_vec.insert(iter, data);
                vec.push_back(tmp_vec);
            }
        }

        vector<vector<int> >::iterator vv_iter;
        for(i = 0; i < vec_size; i++) {
            vv_iter = vec.begin();
            vec.erase(vv_iter);
        }
        return vec;
    }
};

int main(int argc, char *argv[])
{
    vector<int> ivec;
    ivec.push_back(1);
    ivec.push_back(2);
    ivec.push_back(3);

    Solution sol;
    vector<vector<int> > vec = sol.permute(ivec);

    for(vector<vector<int> >::iterator vv_iter = vec.begin();
                                       vv_iter != vec.end(); vv_iter++) {
        ivec = *vv_iter;
        for(vector<int>::iterator v_iter = ivec.begin();
                                  v_iter != ivec.end(); v_iter++) {
            cout<<*v_iter<<"\t";
        }
        cout<<endl;
    }

    return 0;
}
