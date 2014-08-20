## 如何限制类对象只能在堆上或者栈上分配

### 1 限制类对象只能在堆上分配

采用跟单例模式类似的方法：

``` C++
class test {
	test() { }
	~test() { }

public:
	static test* create()
	{
		return new test();
	}

	void destroy()
	{
		delete this;
	}
};
```

### 2 限制类对象只能在栈上分配

使用new操作符在堆上分配对象，首先会调用operator new()分配存储空间，然后在存储空间上构造对象。operator new()分为全局的和类的，如果类重载了operator new()，编译器不会去查找全局的operator new()，因此，如果类重载operator new()，并将它设为私有的，调用operator new()就会失败，于是，new操作会失败。

``` C++
class test {
public:
	test() { }
	~test() { }

private:
	void* operator new(size_t s) { }
	void operator delete(void *ptr) { }
};
```
