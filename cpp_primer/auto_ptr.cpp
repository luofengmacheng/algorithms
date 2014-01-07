#include <iostream>
#include <stdexcept>
using namespace std;

template <class Type>
class Auto_ptr {
public:
	Auto_ptr() : data(NULL) {}
	Auto_ptr(Type *);
	Auto_ptr(Auto_ptr&);
	~Auto_ptr();
	
	Auto_ptr& operator=(Auto_ptr&);
	Type& operator*();
	Type* operator->();
	
	void reset(Auto_ptr&);
	Type* release();
	Type* get();
	
private:
	Type *data;
};

template <class Type>
Auto_ptr<Type>::Auto_ptr(Type *t)
{
	data = t;
}

template <class Type>
Auto_ptr<Type>::Auto_ptr(Auto_ptr &a_ptr)
{
	if(data)
	    delete data;
	data = a_ptr.release();
}

template <class Type>
Auto_ptr<Type>::~Auto_ptr()
{
	if(data)
	    delete data;
	data = NULL;
}

template <class Type>
Auto_ptr<Type>& Auto_ptr<Type>::operator=(Auto_ptr &a_ptr)
{
	if(data)
	    delete data;
	data = a_ptr.release();
	
	return *this;
}

template <class Type>
Type& Auto_ptr<Type>::operator*()
{
	return *data;
}

template <class Type>
Type* Auto_ptr<Type>::operator->()
{
	return data;
}

template <class Type>
void Auto_ptr<Type>::reset(Auto_ptr &a_ptr)
{
	if(*this == a_ptr)
	    return;
	delete data;
	data = a_ptr.data;
	a_ptr.data = NULL;
}

template <class Type>
Type* Auto_ptr<Type>::release()
{
	Type *ret = data;
	data = NULL;
	return ret;
}

template <class Type>
Type* Auto_ptr<Type>::get()
{
	return data;
}

int main(int argc, char *argv[])
{
	try {
		//Auto_ptr a_ptr(new int(3));
		Auto_ptr<string> a_ptr(new string("shit"));
		cout << a_ptr->c_str() << endl;
		//string *s = new string("shit");
	}
	catch(runtime_error &e) {
		cout << e.what() << endl;
	}
	
	return 0;
}
