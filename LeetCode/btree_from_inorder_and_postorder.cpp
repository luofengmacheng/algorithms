/*
 * author:	luo feng
 * date:	2013/11/20
 * source:	LeetCode OJ
 * title:	Construct Binary Tree from Inorder and Postorder Traversal
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void btree_preorder_traverse(TreeNode *root)
{
    if(root != NULL) {
        cout << root->val << " ";
        btree_preorder_traverse(root->left);
        btree_preorder_traverse(root->right);
    }
}

class Solution {
public:
    typedef vector<int>::iterator bt_iter;

    TreeNode *build(bt_iter in_beg, bt_iter in_end, bt_iter post_beg, bt_iter post_end)
    {
        if(in_beg == in_end)
            return NULL;

        int root_val = *(post_end-1);
        bt_iter rt_it = find(in_beg, in_end, root_val);
        bt_iter left_end = post_beg + (rt_it - in_beg);

        TreeNode *child_root = new TreeNode(root_val);
        child_root->left = build(in_beg, rt_it, post_beg, left_end);
        child_root->right = build(rt_it + 1, in_end, left_end, post_end - 1);

        return child_root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return build(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
    }
};

int main(int argc, char *argv[])
{
    int a[] = {2, 1, 3};
    int a_len = sizeof(a) / sizeof(a[0]);
    int b[] = {2, 3, 1};
    int b_len = sizeof(b) / sizeof(b[0]);

    vector<int> preorder(a, a+a_len);
    vector<int> inorder(b, b+b_len);

    Solution sol;
    TreeNode *root = sol.buildTree(preorder, inorder);
    btree_preorder_traverse(root);
    cout << endl;

    return 0;
}
