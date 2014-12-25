/*
 * author:	luo feng
 * date:	2014/7/2
 * source:	LeetCode OJ
 * title:	Binary Tree Maximum Path Sum
 * language:	C++
 */

#include <iostream>
#include <limits>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	//TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

void link(TreeNode *tree, int val, int parent, int left, int right)
{
	tree[parent].val = val;
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

class Solution {
public:
	struct result {
		int max_sum;
		int max_hsum;
		result(int x, int y) : max_sum(x), max_hsum(y) { }
	};

	result max_path_sum(TreeNode *root)
	{
		if(root == NULL) {
			return result(numeric_limits<int>::min(), numeric_limits<int>::min());
		}

		if(root->left == NULL && root->right == NULL) {
			result empty = { root->val, root->val};
			return empty;
		}

		if(root->left != NULL && root->right == NULL) {
			result lhs = max_path_sum(root->left);
			result rs;
			rs.max_hsum = lhs.max_hsum + root->val;
			rs.max_sum = max(max(lhs.max_sum, rs.max_hsum), root->val);
			return rs;
		}

		if(root->left == NULL && root->right != NULL) {
			result rhs = max_path_sum(root->right);
			result rs;
			rs.max_hsum = rhs.max_hsum + root->val;
		}

		result lhs = max_path_sum(root->left);
		result rhs = max_path_sum(root->right);

		result rs;
		rs.max_hsum = max(lhs.max_hsum, rhs.max_hsum) + root->val;
		int child_sum = max(lhs.max_sum, rhs.max_sum);
		int l_sum = lhs.max_hsum + root->val;
		int r_sum = rhs.max_hsum + root->val;
		int tmp = max(max(l_sum, r_sum), child_sum);
		rs.max_sum = max(tmp, lhs.max_hsum+rhs.max_hsum+root->val);

		return rs;
	}

	int maxPathSum(TreeNode *root)
	{
		return max_path_sum(root).max_sum;
	}
};

int main(int argc, char const *argv[])
{
	TreeNode test[3] = { 0 };
	link(test, 1, 0, 1, 2);
	link(test, 2, 1, -1, -1);
	link(test, 3, 2, -1, -1);

	Solution sol;
	cout << sol.maxPathSum(&test[0]) << endl;

	return 0;
}