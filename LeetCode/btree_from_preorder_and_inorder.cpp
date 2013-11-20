/*
 * author:	luo feng
 * date:	2013/11/19
 * source:	LeetCode OJ
 * title:	Construct Binary Tree from Preorder and Inorder Traversal
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

    TreeNode *build(bt_iter pre_beg, bt_iter pre_end, bt_iter in_beg, bt_iter in_end)
    {
        if(pre_beg == pre_end)
            return NULL;

        int root_val = *pre_beg;
        bt_iter rt_it = find(in_beg, in_end, root_val);
        bt_iter left_end = pre_beg + (rt_it - in_beg);

        TreeNode *child_root = new TreeNode(root_val);
        child_root->left = build(pre_beg + 1, left_end + 1, in_beg, rt_it - 1);
        child_root->right = build(left_end + 1, pre_end, rt_it + 1, in_end);

        return child_root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return build(preorder.begin(), preorder.end(), inorder.begin(), inorder.end()); 
    }
};

int main(int argc, char *argv[])
{
    int a[] = {1, 2};
    int a_len = sizeof(a) / sizeof(a[0]);
    int b[] = {2, 1};
    int b_len = sizeof(b) / sizeof(b[0]);

    vector<int> preorder(a, a+a_len);
    vector<int> inorder(b, b+b_len);

    Solution sol;
    TreeNode *root = sol.buildTree(preorder, inorder);
    btree_preorder_traverse(root);
    cout << endl;

    return 0;
}
