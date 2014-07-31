/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	shell sort
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template < typename input_iter, typename Compare >
void shell_sort(input_iter beg, input_iter end, Compare cmp)
{
	typename iterator_traits<input_iter>::difference_type len = end - beg;

	for(int gap = len / 2; gap > 0; gap /= 2) {
		for(int i = gap; i < len; ++i) {
			for(int j = i - gap; j >= 0 && cmp(*(beg + j + gap), *(beg + j)); j -= gap) {
				iter_swap(beg + j + gap, beg + j);
			}
		}
	}
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

	shell_sort(vec.begin(), vec.end(), comp<vector<int>::iterator>());

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
