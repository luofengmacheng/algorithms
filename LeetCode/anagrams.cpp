/*
 * author:	luo feng
 * date:	2013/11/21
 * source:	LeetCode OJ
 * title:	Anagrams
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iterator>
using namespace std;

class Solution {
public:
    vector<string> anagrams(vector<string> &strs)
    {
        if(strs.size() <= 1)
            return vector<string>();
        
        multimap<string, string> records;
        set<string> sset;
        string tmp;

        for(vector<string>::iterator iter = strs.begin();
                                     iter != strs.end(); ++iter) {
            tmp = *iter;
            sort(tmp.begin(), tmp.end());
            records.insert(make_pair(tmp, *iter));
            sset.insert(tmp);
        }

        vector<string> svec;
        pair<multimap<string, string>::iterator, multimap<string, string>::iterator> loc;
        for(set<string>::iterator iter = sset.begin();
                                  iter != sset.end(); ++iter) {
            if(records.count(*iter) > 1) {
                loc = records.equal_range(*iter);
                for(multimap<string, string>::iterator iter = loc.first;
                                                       iter != loc.second; ++iter) {
                    svec.push_back((*iter).second);                                           
                }
            }
        }

        return svec;
    }
};

int main(int argc, char *argv[])
{
    vector<string> strs;
    strs.push_back("abc");
    strs.push_back("pqd");
    strs.push_back("bca");

    Solution sol;
    vector<string> svec = sol.anagrams(strs);
    for(vector<string>::iterator iter = svec.begin();
                                 iter != svec.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}
