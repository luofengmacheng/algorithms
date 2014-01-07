#include <iostream>
using namespace std;

template <typename T>
class testClass {
public:
    static const int _datai = 5;
    static const long _datal = 3L;
    static const char _datac = 'c';
};

int main()
{
    cout << testClass<int>::_datai << endl;
    cout << testClass<int>::_datal << endl;
    cout << testClass<int>::_datac << endl;

    return 0;
}
