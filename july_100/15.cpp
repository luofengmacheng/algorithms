/*
 * author:	luo feng
 * date:	2014/6/27
 * source:	July的微软面试100题系列
 * title:	15.输入一棵二叉查找树，将该树转换为它的镜像
 * 说明：	编译本题时出现了一个错误：用类型为‘tnode*’的右值初始化类型为‘tnode*&’的非常量引用无效。
 * 该错误问题在第95行，最开始写的是solve_r(&test[0])，这是因为，对于引用来说，它必然要绑定某个存储空间，可是，给定的实参是某个成员的地址，
 * 也就是说它没有存储空间，因此，在之前加了一句tnode root = &test[0];然后，将root作为实参，那么，引用就绑定到该实参。
 * language:	C++
 */

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

struct tnode {
	int val;
	tnode *left;
	tnode *right;
};

void solve_r(tnode* &root)
{
	if(root != NULL) {
		swap(root->left, root->right);
		solve_r(root->left);
		solve_r(root->right);
	}
}

void solve(tnode *root)
{
	if(root == NULL) {
		return;
	}

	queue<tnode *> que;
	que.push(root);
	while(!que.empty()) {
		tnode *pnode = que.front();
		que.pop();
		if(pnode != NULL) {
			swap(pnode->left, pnode->right);
			que.push(pnode->left);
			que.push(pnode->right);
		}
	}
}

void link(tnode *tree, int val, int parent, int left, int right)
{
	tree[parent].val =val;

	if(left != -1) {
		tree[parent].left = &tree[left];
	}
	else {
		tree[parent].left = NULL;
	}

	if(right != -1) {
		tree[parent].right = &tree[right];
	}
	else {
		tree[parent].right = NULL;
	}
}

void traverse(tnode *root)
{
	if(root != NULL) {
		traverse(root->left);
		cout << root->val << " ";
		traverse(root->right);
	}
}

int main(int argc, char const *argv[])
{
	tnode test[7];
	memset(test, 0, 7*sizeof(tnode));
	link(test, 8, 0, 1, 2);
	link(test, 6, 1, 3, 4);
	link(test, 10, 2, 5, 6);
	link(test, 5, 3, -1, -1);
	link(test, 7, 4, -1, -1);
	link(test, 9, 5, -1, -1);
	link(test, 11, 6, -1, -1);
	traverse(&test[0]);
	cout << endl;
	tnode *root = &test[0];

	solve_r(root);
	traverse(&test[0]);
	cout << endl;

	solve(root);
	traverse(root);
	cout << endl;

	return 0;
}
