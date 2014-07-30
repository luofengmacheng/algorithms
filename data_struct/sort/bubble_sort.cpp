/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	bubble sort
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template < typename input_iter, typename Compare >
void bubble_sort(input_iter beg, input_iter end, Compare cmp)
{
	if(beg == end) {
		return;
	}

	input_iter iter;

	while(beg != end - 1) {
		iter = beg;

		while(iter != end - 1) {
			if(cmp(*(iter + 1), *iter)) {
				iter_swap(iter + 1, iter);
			}
			++iter;
		}

		--end;
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

	bubble_sort(vec.begin(), vec.end(), comp<vector<int>::iterator>());

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}