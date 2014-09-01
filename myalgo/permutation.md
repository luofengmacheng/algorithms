## 全排列

### 1 递归1

``` C++
vector<string> permutation1(string str)
{
	if(str.empty()) {
		return vector<string>();
	}

	if(str.size() == 1) {
		return vector<string>(1, str);
	}

	char ch = str[str.size() - 1];
	str.erase(str.size() - 1);
	vector<string> ret = permutation1(str);
	size_t size = ret.size();

	while(size--) {
		string s_tmp = ret.back();
		ret.pop_back();
		string tmp = s_tmp;

		for(size_t i = 0; i < s_tmp.size(); ++i) {
			tmp.insert(i, 1, ch);
			ret.insert(ret.begin(), tmp);
			tmp = s_tmp;
		}

		ret.insert(ret.begin(), tmp + ch);
	}

	return ret;
}
```

字符串的全排列的递归实现，基本想法是，已知一部分字符的全排列，然后再往其中添加字符，来构造更多字符的全排列。

例如，要求字符串abcd的全排列，如果已知ab的全排列是ab、ba，可以对每个字符串添加c来获得abc的全排列，对ab，可以在三个位置添加字符c，得到cab、acb、abc，对ba，可以在三个位置添加c，得到cba、bca、bac。这样就得到了abc的全排列。同样再对abc的全排列添加d就可以得到abcd的全排列。

### 2 递归2

``` C++
template < typename T >
struct print {
	void operator()(T t)
	{
		cout << t;
	}
};

template < typename input_iter >
void _permutation2(input_iter beg1, input_iter end1, input_iter beg2, input_iter end2)
{
	if(beg1 == end1) {
		for_each(beg2, end2, print<typename input_iter::value_type>());
		cout << endl;
		return;
	}

	input_iter iter_tmp = beg1;
	while(iter_tmp != end1) {
		iter_swap(beg1, iter_tmp);
		_permutation2(beg1 + 1, end1, beg2, end2);
		iter_swap(beg1, iter_tmp);
		++iter_tmp;
	}
}

template < typename input_iter >
void permutation2(input_iter beg, input_iter end)
{
	_permutation2(beg, end, beg, end);
}
```

序列的全排列的递归实现，基本想法是，对于某个元素而言，该位置可以放剩余的所有元素。

### 3 非递归(字典序排列)

``` C++
template < typename input_iter, typename Compare >
bool _permutation3(input_iter beg, input_iter end, Compare comp)
{
	if(beg == end || end - beg == 1) {
		return false;
	}

	input_iter iter;
	for(iter = end - 1; iter != beg; --iter) {
		if(comp(*(iter - 1), *iter)) {
			break;
		}
	}

	if(iter == beg) {
        return false;
	}

	input_iter big_iter;
	for(big_iter = end - 1; big_iter != beg; --big_iter) {
		if(comp(*(iter - 1), *big_iter)) {
			break;
		}
	}

	iter_swap(iter - 1, big_iter);

	reverse(iter, end);

	for_each(beg, end, print<typename input_iter::value_type>());
	cout << endl;

	return true;
}

template < typename input_iter, typename Compare >
bool permutation3(input_iter beg, input_iter end, Compare comp)
{
	for_each(beg, end, print<typename input_iter::value_type>());
	cout << endl;

	while(_permutation3(beg, end, comp))
		;
}
```

全排列的非递归实现，而且，结果是按照字典顺序或者大小顺序排列的。从后往前扫描，找到为升序的相邻的元素。如果不存在这样的相邻的元素。如果存在，记为i和j，再从后往前扫描，找到一个大于i的元素k，交换i和k，然后将从j开始到结束的子序列反转，就得到了下一个字符串。

例如，要求abcd的全排列，假如已经得到了一个全排列acdb，首先，从后往前扫描，找到为升序的相邻的元素，就是cd，再从后往前扫描，找到一个大于c的元素，就是d，交换c和d，就变成了adcb，然后将cb反转，就变成了adbc。
