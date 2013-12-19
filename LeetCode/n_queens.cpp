/*
 * author:	luo feng
 * date:	2013/12/13
 * source:	LeetCode OJ
 * title:	N-Queens
 * language:	C++
 */

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<int> queens;
    vector<vector<int> > sols;

    void place_queen(int i, int n)
    {
        int j = 0;

        for(j = 0; j < n; ++j) {
            if(i == n) {
                sols.push_back(queens);
                return;
            }

            queens[i] = j;

            if(is_valid(i))
                place_queen(i+1, n);
        }
    }

    bool is_valid(int n)
    {
        int i = 0, j = 0;

        for(i = 0; i < n; ++i) {
            if(queens[i] == queens[n]) {
                return false;
            }

            if(abs(queens[i] - queens[n]) == (n - i)) {
                return false;
            }
        }
        return true;
    }
    

    vector<vector<string> > solveQueens(int n)
    {
        int i = 0, cnt = 0;
        for(i = 0; i < n; ++i) {
            queens.push_back(0);
        }
        place_queen(0, n);

        
        string str;
        vector<string> svec;
        vector<vector<string> > svvec;

        for(vector<vector<int> >::iterator vv_iter = sols.begin();
                                         vv_iter != sols.end(); ++vv_iter) {
            svec.clear();
            for(vector<int>::iterator v_iter = (*vv_iter).begin();
                                      v_iter != (*vv_iter).end(); ++v_iter) {
                str.clear();
                for(i = 0; i < n; ++i) {
                    if(*v_iter == i) {
                        str.push_back('Q');
                    }
                    else {
                        str.push_back('.');
                    }
                }
                svec.push_back(str);
            }
            svvec.push_back(svec);
        }
        return svvec;
    }
};

int main(int argc, char *argv[])
{
    Solution sol;
    vector<vector<string> > svvec = sol.solveQueens(4);
    for(vector<vector<string> >::iterator vv_iter = svvec.begin();
                                          vv_iter != svvec.end(); ++vv_iter) {
        for(vector<string>::iterator v_iter = (*vv_iter).begin();
                                     v_iter != (*vv_iter).end(); ++v_iter) {
            cout << *v_iter << endl;
        }
        cout << endl;
    }

    return 0;
}

/* easy function to get solutions count
void go(int col,int flag1,int flag2)
{
   int pos,p;

   if (col==(1<<n)-1)
   {
       sum++;
   }
   else
   {
       pos = ((1<<n)-1)&~(col|flag1|flag2);
       while(pos)
       {
           p = pos&((~pos)+1);
           pos -= p;
           go(col+p,(flag1+p)>>1,(flag2+p)<<1);
       }
   }
}*/
