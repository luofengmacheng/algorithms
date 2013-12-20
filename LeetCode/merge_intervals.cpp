/*
 * author:	luo feng
 * date:	2013/12/11
 * source:	LeetCode OJ
 * title:	Merge Intervals
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) { }
    Interval(int s, int e) : start(s), end(e) { }
};

void print_res(Interval i)
{
    cout << i.start << "," << i.end << endl;
}

class Solution {
public:
    static bool cmp_func(const Interval &i1, const Interval &i2)
    {
        return i1.start < i2.start;
    }

    vector<Interval> merge(vector<Interval> &intervals)
    {
        vector<Interval> ivec;
        vector<Interval>::iterator iter;
        if(intervals.size() == 0)
           return vector<Interval>();
        
        sort(intervals.begin(), intervals.end(), cmp_func);
        for_each(intervals.begin(), intervals.end(), print_res);
        cout << endl;
        for(iter = intervals.begin();
            iter != intervals.end() - 1;) {
            if((*iter).end < (*(iter + 1)).start) {
                ivec.push_back(*iter);
                ++iter;
            }
            else {
                int e = (*(iter + 1)).end;
                (*iter).end = max(e, (*iter).end);
                iter = intervals.erase(iter + 1);
                --iter;
            }
        }
        ivec.push_back(*iter);
        return ivec;
    }
};

int main(int argc, char *argv[])
{
    vector<Interval> intvec;
    intvec.push_back(Interval(8, 10));
    intvec.push_back(Interval(1, 3));
    intvec.push_back(Interval(8, 18));
    intvec.push_back(Interval(1, 6));
    Solution sol;
    vector<Interval> ivec = sol.merge(intvec);
    for_each(ivec.begin(), ivec.end(), print_res);

    return 0;
}
