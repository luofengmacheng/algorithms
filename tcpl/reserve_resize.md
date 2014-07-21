## C++中vector的reserve()和resize()

### 1 reserve()

首先，从字面意思理解，reserve的意思是：预留。那么这个函数是如何控制空间的呢？

``` C++
vector<int> vec(10);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.reserve(5);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.reserve(25);
cout << vec.size() << endl;
cout << vec.capacity() << endl;
```

运行结果：

```
10
10
10
10
10
25
```

从执行结果可以知道(假设reserve的参数为n，vector的容量为c)：
* 当在创建vector时，指定大小参数可以将vector的大小和容量都设置为参数值。
* 在调用reserve()，如果n <= c，什么也不干。
* 在调用reserve()，如果n > c，则进行空间的再分配，使得vector可以容纳n个元素，但是原来的元素并没有改变 。

因此，reserve()的实现可能类似：

``` C++
template < typename T >
void vector<T>::reserve(size_t n)
{
    if(n > c) {
        ptr = realloc(ptr, n * sizeof(T));
    }
}
```

注意：上面的代码中，为了方便，模板参数只写了一个。其中，ptr是内部使用的实际存储数据的指针。

### 2 resize()

下面再来看看resize():

第一个例子：

``` C++
vector<int> vec(10);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.resize(5);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.resize(25);
cout << vec.size() << endl;
cout << vec.capacity() << endl;
```

运行结果：

```
10
10
5
10
25
25
```

第二个例子：

``` C++
vector<int> vec(10);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.resize(7);
cout << vec.size() << endl;
cout << vec.capacity() << endl;

vec.resize(11);
cout << vec.size() << endl;
cout << vec.capacity() << endl;
```

运行结果：

```
10
10
7
10
11
14
```

从执行结果可以知道(假设resize的参数为n，vector的元素个数为s，vector的容量为c)：
* 如果n <= c，vector的底层不会发生空间的再分配，而是根据n和s的大小关系删除或者添加元素(n < s时，会删除后面的s-n个元素；n > s时，会在vector后面添加n-s个元素)。
* 如果n > c时，vector的底层会发生空间的再分配。如果2 * s >= n时，就重新分配2 * s * sizeo(T)的空间。如果2 * s < n时，就分配n * sizeo(T)的空间。

因此，resize()的实现可能类似：

``` C++
template < typename T >
void vector<T>::resize(size_t n)
{
    if(n <= c) {
        if(n < s) {
            // delete s-n elements
        }
        else if(n > s) {
            // insert n-s elements
        }
    }
    else {
        if(2 * s >= n) {
            ptr = realloc(ptr, 2 * s * sizeof(T));
            // delete or insert elements to make size n
        }
        else {
            ptr = realloc(ptr, n * sizeof(T));
            // delete or insert elements to make size n
        }
    }
}
```

### 3 小结

* reserve()针对容量，使得之后向其中添加元素时，不需要进行空间的分配。
* resize()针对元素个数，使得vector的元素为n(n为resize的参数)。
