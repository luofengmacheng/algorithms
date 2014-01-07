/*
 * author:	luo feng
 * date:	2013/10/25
 * info:	二分查找
 */

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);

    int target = 1;
    int left = 0, right = vec.size()-1;
    int mid = 0;
    while(left < right) {
        mid = (left+right)/2;
        if(target < vec[mid])
            right = mid-1;
        else if(target > vec[mid])
            left = mid+1;
        else
            break;
    }
    cout<<vec[mid]<<endl;

    return 0;
}
