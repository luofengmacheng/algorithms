/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	insert sort
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template < typename input_iter, typename Compare >
void insert_sort(input_iter beg, input_iter end, Compare cmp)
{
	for(input_iter iter = beg; iter != end; ++iter) {

		input_iter iter2 = iter;
		
		while(iter2 != beg && cmp(*iter2, *(iter2 - 1))) {
			iter_swap(iter2, iter2 - 1);
			--iter2;
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

	insert_sort(vec.begin(), vec.end(), comp<vector<int>::iterator>());

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
