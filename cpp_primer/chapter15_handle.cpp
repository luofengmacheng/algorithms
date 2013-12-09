/*
 * author:	luo feng 
 * date:	2013/12/9
 * source:	C++ Primer
 * title:	句柄类
 */

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class base {
public:
    virtual base* clone() const
    {
        return new base(*this);
    }

    virtual void func()
    {
        cout << "base function is called" << endl;
    }
};

class derived : public base {
public:
    derived* clone() const
    {
        return new derived(*this);
    }

    void func()
    {
        cout << "derived function is called" << endl;
    }
};

class handle {
public:
    handle() : p(0), use(new size_t(1)) { }
    handle(const base& b) : p(b.clone()), use(new size_t(1)) { }
    handle(const handle& h) : p(h.p), use(h.use) { ++*use; }

    ~handle() { decr_use(); }

    handle& operator=(const handle&);
    const base* operator->() const
    {
        if(p)
            return p;
        else
            throw logic_error("unbound handle");
    }
    const base& operator*() const
    {
        if(p)
            return *p;
        else
            throw logic_error("unbound handle");
    }
private:
    base *p;
    size_t *use;
    void decr_use()
    {
        if(--*use == 0) {
            delete p;
            delete use;
        }
    }
};

handle& handle::operator=(const handle& h)
{
    ++*h.use;
    decr_use();
    p = h.p;
    use = h.use;
    return *this;
}

int main(int argc, char *argv[])
{
    vector<handle> hvec;
    base b;
    handle h1(b);
    derived d;
    handle h2(d);
    hvec.push_back(h1);
    hvec.push_back(h2);
    hvec[0]->func();
    hvec[1]->func();

    return 0;
}
