/*
 * author:	luo feng
 * date:	2014/5/14
 * source:	More Effective C++
 * title:	auto_ptr
 * language:	C++
 */

#include <iostream>
using namespace std;

template < typename T >
class auto_ptr {
public:
	auto_ptr(T *ptr = 0) : pointee(ptr) { }
	~auto_ptr() { delete pointee; }

	auto_ptr(auto_ptr<T>& rhs);
	auto_ptr<T>& operator=(auto_ptr<T>& rhs);

	T* operator->();
	T& operator*();

private:
	T *pointee;
};

template < typename T >
auto_ptr<T>::auto_ptr(auto_ptr<T>& rhs)
{
	pointee = rhs.pointee;
	rhs.pointee = 0;
}

template < typename T >
auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>& rhs)
{
	if(this == &rhs) {
		return *this;
	}

	delete pointee;

	pointee = rhs.pointee;
	rhs.pointee = 0;

	return *this;
}

template < typename T >
T* auto_ptr<T>::operator->()
{
	return pointee;
}

template < typename T >
T& auto_ptr<T>::operator*()
{
	return *pointee;
}

int main(int argc, char const *argv[])
{

	return 0;
}