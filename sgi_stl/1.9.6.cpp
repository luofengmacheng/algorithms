#include <iostream>
using namespace std;

template <class T>
struct plus1 {
    T operator()(const T& x, const T& y) const
    {
        return x + y;
    }
};

template <class T>
struct minus1 {
    T operator()(const T& x, const T& y) const
    {
        return x - y;
    }
};

int main()
{
    plus1<int> plusobj;
    minus1<int> minusobj;

    cout << plusobj(3, 5) << endl;
    cout << minusobj(3, 5) << endl;

    cout << plus1<int>()(43, 50) << endl;
    cout << minus1<int>()(43, 50) << endl;

    return 0;
}
