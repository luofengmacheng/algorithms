#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int main()
{
    deque<int, allocator<int> > ideq(20, 9);
    cout << "size = " << ideq.size() << endl;

    return 0;
}
