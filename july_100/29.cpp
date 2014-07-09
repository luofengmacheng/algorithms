/*
 * author:	luo feng
 * date:	2014/7/7
 * source:	July的微软面试100题系列
 * title:	29.判断某个序列是否可能是栈的push顺序对应的pop顺序
 * language:	C++
 * 详细题目：	输入两个整数序列，其中一个序列表示栈的push顺序，判断另一个序列是否可能是对应的pop顺序。
 * 方法：	用一个栈来处理push序列，看是否可以得到pop序列。当栈不空并且栈顶元素不等于当前pop元素时，说明还没到pop的时候。
 * 如果栈不空并且栈顶元素等于当前pop元素，说明可以执行pop操作了。
 */

#include <iostream>
#include <stack>

using namespace std;

bool is_pop(int push[], int pop[], int n)
{
	if(push == NULL || pop == NULL || n <= 0) {
		return false;
	}

	int i1 = 0, i2 = 0;
	stack<int> sta;

	while(i2 < n) {
		while(sta.empty() || sta.top() != pop[i2]) {
			if(i1 < n) {
				sta.push(push[i1++]);
			}
			else { // i1 >= n说明数据已经全部进栈，但是，进了这个循环则说明数据还没有全部出栈，但是，栈顶元素又不等于当前pop元素，无法出栈。
				return false;
			}
		}
		sta.pop();
		++i2;
	}

	if(sta.empty() && i1 == n && i2 == n) {
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char const *argv[])
{
	int push[] = {1, 2, 3, 4, 5};
	int pop[] = {4, 3, 5, 1, 2};
	cout << boolalpha << is_pop(push, pop, 5) << endl;

	return 0;
}
