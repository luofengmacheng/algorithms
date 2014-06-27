/*
 * author:	luo feng
 * date:	2014/6/27
 * source:	July的微软面试100题系列
 * title:	4.在二叉查找树中找出和为某一值的所有路径
 * language:	C++
 */

#include <iostream>
#include <stack>
#include "btree.hpp"

using namespace std;
typedef bnode_base<int> bnode;

void traverse_tree(bnode *pnode, int val, stack<int> sta)
{
	if(pnode == NULL) {
		return;
	}
	if(pnode->left == NULL && pnode->right == NULL && pnode->data == val) {
		int x = 0;
		cout << pnode->data << " ";
		while(!sta.empty()) {
			x = sta.top();
			sta.pop();
			cout << x << " ";
		}
		cout << endl;
	}
	sta.push(pnode->data);
	traverse_tree(pnode->left, val - pnode->data, sta);
	traverse_tree(pnode->right, val - pnode->data, sta);
}

void print(int t)
{
	cout << t << " ";
}

void solve(btree<int> &bt, int val)
{
	bnode *root = bt.get_root();
	stack<int> sta;
	bt.traverse(print);
	cout << endl;
	sta.push(root->data);

	traverse_tree(root->left, val - root->data, sta);
	traverse_tree(root->right, val - root->data, sta);
}

int main(int argc, char const *argv[])
{
	int arr[] = {10, 5, 12, 7, 0, 0, 0, 0};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	btree<int> bt(vec.begin(), vec.end());
	int a = 22;
	solve(bt, a);

	return 0;
}
