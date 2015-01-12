## C语言中的qsort和C++中的sort

### 1 问题的由来

最近看C语言的代码，遇到了qsort函数：

``` C
int VocabCompare(const void *a, const void *b) {
    return ((struct vocab_word *)b)->cn - ((struct vocab_word *)a)->cn;
}

qsort(&vocab[1], vocab_size - 1, sizeof(struct vocab_word), VocabCompare);
```

上面的代码对数组vocab进行排序，排序的大小规则按照VocabCompare进行，由于对C++中sort的思维定势，认为VocabCompare是按照返回值大于0排序，于是，错误地理解为按照从小到大排序。

### 2 C语言中的qsort

qsort的头文件是stdlib.h(cstdlib)。

原型：

``` C
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
```

* base: 排序数组的基地址
* nmemb: 排序数组的成员个数
* size: 排序数组的成员大小
* compar: 排序规则

compar的参数是两个const void的指针，这两个指针分别指向base数组的两个成员，对这两个成员进行比较，返回值为int，最终的结果是按照compar的返回值为负值进行排序。

例如：

``` C
#include <iostream>
#include <cstdlib>
#include <iterator>

using namespace std;

int compare(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main(int argc, char const *argv[])
{
	int arr[] = {4, 5, 2, 7, 1};

	qsort(arr, 5, sizeof(int), compare);

	copy(arr, arr+5, ostream_iterator<int>(cout, " "));

	cout << endl;

	return 0;
}
```

对arr数组的成员进行排序，排序的规则是使得a指向的值小于b指向的值，也就是按照从小到大的顺序排序。

运行结果为：

```
1 2 4 5 7
```

### 3 C++中的sort

sort的头文件是algorithm

C++中的sort一般有两种形式：

第一种形式是：

``` C++
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
```

只用两个随机访问迭代器限定排序范围。

第二种形式是：


``` C++
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

除了随机访问迭代器限定的范围外，还有一个参数comp:排序规则。

comp是二元函数，接受两个迭代器范围内的成员，返回bool值。排序的规则就是使得comp的结果为true。

``` C++
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

bool cmp(int a, int b)
{
	return a < b;
}

int main(int argc, char const *argv[])
{
	int arr[] = {4, 5, 2, 7, 1};

	sort(arr, arr+5, cmp);

	copy(arr, arr+5, ostream_iterator<int>(cout, " "));

	cout << endl;

	return 0;
}
```

以上的代码使用cmp进行排序，排序的规则是从小到大，这也是只有两个参数的sort的行为。

### 4 小结

上面简单介绍了C语言中的qsort和C++中的sort。参数基本都是排序范围和排序规则。

不同的是：

* qsort使用基地址和元素个数确定排序范围，sort使用两个迭代器确定排序范围。
* qsort的排序规则的参数类型为指针，sort的参数类型为排序成员类型。
* qsort的排序规则的返回值为int，sort的排序规则的返回值为bool。
* qsort的排序使得排序规则返回负值，sort的排序使得返回值为true。

参考文档：

1 [std::sort @ cplusplus](http://www.cplusplus.com/reference/algorithm/sort/)
