/*
 * author:	luo feng
 * date:	2014/7/30
 * title:	heap sort
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

namespace luofengmacheng {

// 建堆：将该节点的值从上往下调整
template < typename input_iter, typename Compare >
void make_heap(input_iter beg, input_iter end, Compare cmp)
{
	typename iterator_traits<input_iter>::difference_type len = end - beg;

	for(int i = len / 2 - 1; i >= 0; --i) {
		int j = i;
		int k = j * 2 + 1;
		while(j < len && k < len) {

			if(k + 1 < len && cmp(*(beg + k), *(beg + k + 1))) {
				++k;
			}

			if(k < len && cmp(*(beg + j), *(beg + k))) {
				iter_swap(beg + j, beg + k);	
			}
			else {
				break;
			}
			j = k;
			k = j * 2 + 1;
		}
	}
}

// 弹出：将堆顶元素和最后一个元素交换，然后将堆顶的元素往下调整
template < typename input_iter, typename Compare >
void pop_heap(input_iter beg, input_iter end, Compare cmp)
{
	if(beg == end) {
		return;
	}

	iter_swap(beg, end - 1);

	typename iterator_traits<input_iter>::difference_type len = end - beg - 1;

	int i = 0, k = i * 2 + 1;
	while(i < len && k < len) {

		if(k + 1 < len && cmp(*(beg + k), *(beg + k + 1))) {
			++k;
		}

		if(k < len && cmp(*(beg + i), *(beg + k))) {
			iter_swap(beg + i, beg + k);
		}
		else {
			break;
		}

		i = k;
		k = i * 2 + 1;
	}
}

// 压入：将最后一个元素往上调整
template < typename input_iter, typename Compare >
void push_heap(input_iter beg, input_iter end, Compare cmp)
{
	if(beg == end) {
		return;
	}

	typename iterator_traits<input_iter>::difference_type len = end - beg - 1;

	int i = len, k = (i + 1) / 2 - 1;
	while(i >= 0 && k >= 0) {

		if(cmp(*(beg + k), *(beg + i))) {
			iter_swap(beg + i, beg + k);
		}
		else {
			break;
		}

		i = k;
		k = (i + 1) / 2 - 1;
	}
}

template < typename input_iter, typename Compare >
void heap_sort(input_iter beg, input_iter end, Compare cmp)
{
	make_heap(beg, end, cmp);

	while(beg != end) {
		pop_heap(beg, end, cmp);

		--end;
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
	int arr[] = {67, 56, 34, 98, 23, 76, 78, 45, 82, 39};
	vector<int> vec1(arr, arr + 10);
	vector<int> vec2(arr, arr + 10);

	luofengmacheng::make_heap(vec1.begin(), vec1.end(), comp<vector<int>::iterator>());
	copy(vec1.begin(), vec1.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	vector<int>::iterator iter1 = vec1.end();
	while(iter1 != vec1.begin()) {
		luofengmacheng::pop_heap(vec1.begin(), iter1, comp<vector<int>::iterator>());
		copy(vec1.begin(), iter1, ostream_iterator<int>(cout, " "));
		cout << endl;
		--iter1;
	}

	std::make_heap(vec2.begin(), vec2.end());
	cout << endl;
	copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	vector<int>::iterator iter2 = vec2.end();
	while(iter2 != vec2.begin()) {
		std::pop_heap(vec2.begin(), iter2);
		copy(vec2.begin(), iter2, ostream_iterator<int>(cout, " "));
		cout << endl;
		--iter2;
	}

	return 0;
}
