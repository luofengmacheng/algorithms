/*
 * author:	luo feng
 * date:	2013/12/23
 * source:	LeetCode OJ
 * title:	Insert Interval
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

void print_interval(Interval i)
{
    cout << "[ " << i.start << ", " << i.end << "]" << endl;
}

class Solution {
public:
    bool is_mixed(const Interval &i1, const Interval &i2)
    {
        if(i1.start > i2.end)
            return false;
        else if(i1.end < i2.start)
            return false;
        else
            return true;
    }

    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
        if(intervals.size() == 0)
            return vector<Interval>(1, newInterval);
        int cnt = 0;
        bool begin_set= false, end_set = false;
        vector<Interval>::iterator iter1 = intervals.end(), iter2 = intervals.end();
        vector<Interval>::iterator iter;
        for(iter = intervals.begin();
            iter != intervals.end(); ++iter) {
            if(newInterval.end < (*iter).start) {
                break;
            }
            else {
                if(is_mixed(newInterval, *iter)) {
                    if(!begin_set) {
                        iter1 = iter;
                        begin_set = true;
                    }
                    else {
                        iter2 = iter;
                        end_set = true;
                    }
                    ++cnt;
                }
            }
        }
        if(cnt == 0) {
            intervals.insert(iter, newInterval);
            return intervals;
        }
        (*iter1).start = min(newInterval.start, (*iter1).start);
        if(end_set)
            (*iter1).end = max(newInterval.end, (*iter2).end);
        else
            (*iter1).end = max(newInterval.end, (*iter1).end);
        if(end_set && iter1 + 1 != intervals.end())
            intervals.erase(iter1 + 1, iter2 + 1);
        return intervals;
    }
};

int main(int argc, char *argv[])
{
    vector<Interval> vec;
    vec.push_back(Interval(0, 2));
    vec.push_back(Interval(3, 9));
    Interval newint(6, 8);
    Solution sol;
    sol.insert(vec, newint);
    for_each(vec.begin(), vec.end(), print_interval);
    cout << endl;

    return 0;
}


