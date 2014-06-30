/*
 * author:	luo feng
 * date:	2014/6/30
 * source:	July的微软面试100题系列
 * title:	9.判断整数序列是不是二叉查找树的后序遍历结果
 * language:	C++
 * 本题主要是要明确二叉查找树的性质。判断一个序列是否是二叉查找树的后序遍历的方法是，如果一个序列是二叉查找树的后序遍历，那么最后一个元素就是这个树的根，
 * 然后，从前往后遍历，找到第一个比根大的值a，那么根的左子树就是起始元素到a的前一个元素，从a开始到倒数第二个元素就是根的右子树，
 * 而且左右子树必须都是二叉查找树。并且，还必须遍历从a开始到倒数第二个元素，检查它们是否比最后一个元素大。
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>

using namespace std;

bool solve(vector<int>::iterator beg, vector<int>::iterator end)
{
	if(beg == end) {
		return true;
	}
	int last = *(end-1);

	vector<int>::iterator iter = beg;
	while(iter != end-1 && *iter < last) {
		++iter;
	}
	vector<int>::iterator iter2 = iter;
	while(iter2 != end-1 && *iter2 >= last) {
		++iter2;
	}
	if(iter2 != end-1) {
		return false;
	}
	--end;

	if(solve(beg, iter) && solve(iter, end)) {
		return true;
	}

	return false;
}

int main(int argc, char const *argv[])
{
	int arr[] = {5, 7, 6, 9, 11, 10, 8};
	vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
	cout << boolalpha << solve(vec.begin(), vec.end()) << endl;

	return 0;
}
