/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	merge sort
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template < typename input_iter, typename Compare >
void merge_sort(input_iter beg, input_iter end, Compare cmp)
{
	if(beg == end || end - beg == 1) {
		return;
	}

	typename iterator_traits<input_iter>::difference_type len = end - beg;
	input_iter mid = beg + len / 2;

	merge_sort(beg, mid, cmp);
	merge_sort(mid, end, cmp);

	typedef typename iterator_traits<input_iter>::value_type val_type;
	vector<val_type> vec(len);

	// 注意下面这行，不能直接用vector<val_type>::iterator
	typename vector<val_type>::iterator iter = vec.begin();
	input_iter iter1 = beg, iter2 = mid;
	while(iter1 != mid && iter2 != end) {
		if(cmp(*iter1, *iter2)) {
			*iter++ = *iter1++;
		}
		else {
			*iter++ = *iter2++;
		}
	}

	if(iter1 != mid) {
		copy(iter1, mid, iter);
	}

	if(iter2 != end) {
		copy(iter2, end, iter);
	}

	copy(vec.begin(), vec.end(), beg);
}

template < typename input_iter >
struct comp {

	typedef typename iterator_traits<input_iter>::value_type val_type;

	bool operator()(val_type op1, val_type op2)
	{
		return op1 < op2;
	}
};

int main(int argc, char const *argv[])
{
	int arr[] = {4, 2, 6, 5, 1};
	vector<int> vec(arr, arr + 5);

	merge_sort(vec.begin(), vec.end(), comp<vector<int>::iterator>());

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
