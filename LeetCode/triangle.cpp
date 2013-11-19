/*
 * author:	luo feng
 * date:	2013/11/18
 * source:	LeetCode OJ
 * title:	Triangle
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle)
    {
        if(triangle.size() == 0)
            return 0;

        vector<vector<int> >::size_type tri_size = triangle.size();
        int *min_route = new int[tri_size]();
        int *tmp = new int[tri_size]();
        
        int i = 0, j = 0;
        for(i = 0; i != tri_size; ++i) {
            for(j = 0; j != triangle[i].size(); ++j) {
                if(i == 0) {
                    tmp[0] = triangle[0][0];
                }
                else if(j == 0) {
                    tmp[j] = min_route[j] + triangle[i].at(j);
                }
                else if(j == triangle[i].size()-1) {
                    tmp[j] = min_route[j-1] + triangle[i].at(j);
                }
                else {
                    tmp[j] = min(min_route[j-1], min_route[j]) + triangle[i].at(j);
                }
            }
            copy(tmp, tmp+tri_size, min_route);
        }

        int min_tot = *min_element(min_route, min_route+tri_size);

        delete [] min_route;
        delete [] tmp;

        return min_tot;
    }
};

int main(int argc, char *argv[])
{
    int i = 4;
    vector<int> vec1;
    vec1.push_back(2);
    vector<int> vec2;
    vec2.push_back(3);
    vec2.push_back(4);
    vector<int> vec3;
    vec3.push_back(6);
    vec3.push_back(5);
    vec3.push_back(7);
    vector<int> vec4;
    vec4.push_back(4);
    vec4.push_back(1);
    vec4.push_back(8);
    vec4.push_back(3);

    vector<vector<int> > vec;
    vec.push_back(vec1);
    vec.push_back(vec2);
    vec.push_back(vec3);
    vec.push_back(vec4);

    Solution sol;
    cout << sol.minimumTotal(vec) << endl;

    return 0;
}
