#include <iostream>
#include <iomanip>
#include <typeinfo>
using namespace std;

class INT {
    friend ostream& operator<<(ostream& os, const INT& i);

public:
    INT(int i) : m_i(i) {}
    INT(const INT& I) : m_i(I.m_i) {}

    INT& operator++()
    {
        ++(this->m_i);
        return *this;
    }

    //问题一：后置自增和自减运算的返回值为什么是对象，而且是const对象
    //是因为不允许I++++吗，那++++I呢？
    const INT operator++(int)
    {
        const INT tmp(*this);
        ++(*this);
        return tmp;
    }

    INT& operator--()
    {
        --(this->m_i);
        return *this;
    }

    const INT operator--(int)
    {
        const INT tmp(*this);
        --(*this);
        return tmp;
    }

    //问题二：解引用操作符获取引用时，为什么一定要进行类型转换
    int& operator*() const
    {
        cout << boolalpha << (typeid(const INT) == typeid(*this)) << endl;
        cout << boolalpha << (typeid(const int) == typeid(m_i)) << endl;
        return m_i;
    }

private:
    int m_i;
};

ostream& operator<<(ostream& os, const INT& i)
{
    os << '[' << i.m_i << ']';
    return os;
}

int main()
{
    INT I(5);
    cout << I++ << endl;
    cout << ++I << endl;
    cout << I-- << endl;
    cout << --I << endl;
    cout << *I << endl;

    int i = 0;
    cout << ++++i << endl;
    //cout << i++++ << endl;

    return 0;
}
