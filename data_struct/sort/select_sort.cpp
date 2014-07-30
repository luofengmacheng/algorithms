/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	select sort
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template < typename input_iter, typename Compare >
void select_sort(input_iter beg, input_iter end, Compare cmp)
{
	input_iter iter, iter2;

	while(beg != end) {
		iter = beg;

		while(iter != end) {
			if(cmp(*iter, *beg)) {
				iter_swap(iter, beg);
			}

			++iter;
		}

		++beg;
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

	select_sort(vec.begin(), vec.end(), comp<vector<int>::iterator>());

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
