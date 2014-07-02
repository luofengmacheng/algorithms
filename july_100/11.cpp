/*
 * author:	luo feng
 * date:	2014/7/2
 * source:	July的微软面试100题系列
 * title:	11.求二叉树中节点的最大距离
 * reference:	http://www.cnblogs.com/miloyip/archive/2010/02/25/1673114.html
 * 说明：	这道题是编程之美3.8的题，这里基本是参考上面的博客的解法。这题的解法是：采用递归的思路，求一棵树的最大距离需要知道什么？
 * 根据《编程之美》的分析，一棵树的最大距离 = max(所有子树的最大距离, 所有子树的最大深度的前两名+2)，
 * 因此，求一棵树的最大距离可以转换为求子树的最大距离和子树的深度。
 * 从下面的代码中，还可以学习到如何快速构造一棵树：用数组来构造一个二叉树。
 * language:	C++
 */

#include <iostream>

using namespace std;

struct tnode {
	tnode *left;
	tnode *right;
};

struct result {
	int max_dis;
	int max_dep;
};

result get_max_distance(tnode *root)
{
	if(root == NULL) {
		result empty = {0, -1};
		return empty;
	}

	result lhs = get_max_distance(root->left);
	result rhs = get_max_distance(root->right);

	result rs;
	rs.max_dep = max(lhs.max_dep+1, rhs.max_dep+1);
	rs.max_dis = max(max(lhs.max_dis, rhs.max_dis), lhs.max_dep+rhs.max_dep+2);

	return rs;
}

void link(tnode *nodes, int parent, int left, int right)
{
	if(left != -1) {
		nodes[parent].left = &nodes[left];
	}

	if(right != -1) {
		nodes[parent].right = &nodes[right];
	}
}

int main(int argc, char const *argv[])
{
	tnode test1[9] = { 0 };
	link(test1, 0, 1, 2);
	link(test1, 1, 3, 4);
	link(test1, 2, 5, 6);
	link(test1, 3, 7, -1);
	link(test1, 5, -1, 8);
	cout << "test1: " << get_max_distance(&test1[0]).max_dis << endl;

	tnode test2[4] = { 0 };
	link(test2, 0, 1, 2);
	link(test2, 1, 3, -1);
	cout << "test2: " << get_max_distance(&test2[0]).max_dis << endl;

	tnode test3[9] = { 0 };
	link(test3, 0, -1, 1);
	link(test3, 1, 2, 3);
	link(test3, 2, 4, -1);
	link(test3, 3, 5, 6);
	link(test3, 4, 7, -1);
	link(test3, 5, -1, 8);
	cout << "test3: " << get_max_distance(&test3[0]).max_dis << endl;

	return 0;
}
