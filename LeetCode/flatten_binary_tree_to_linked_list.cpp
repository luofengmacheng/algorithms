/*
 * author:	luo feng
 * date:	2013/12/23
 * source:	LeetCode OJ
 * title:	Flatten Binary Tree to Linked List
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void tree_insert(TreeNode *&root, TreeNode *pnode)
{
    if(root == NULL) {
        root = pnode;
        return;
    }
    if(pnode->val <= root->val) {
        tree_insert(root->left, pnode);
    }
    else {
        tree_insert(root->right, pnode);
    }
}

void tree_create(TreeNode *&root, vector<int>::iterator beg, vector<int>::iterator end)
{
    TreeNode *pnode = NULL;
    while(beg != end) {
        pnode = new TreeNode(*beg);
        tree_insert(root, pnode);
        ++beg;
    }
}

void tree_traverse(TreeNode *root)
{
    if(root != NULL) {
        cout << root->val << " ";
        tree_traverse(root->left);
        tree_traverse(root->right);
    }
}

void tree_structure(TreeNode *root)
{
    if(root != NULL) {
        cout << "root :" << root->val << endl;
        if(root->left == NULL) {
            cout << "left child is NULL " << endl;
            tree_structure(root->right);
        }
        else
            cout << "error!" << endl;
    }
}

void tree_destroy(TreeNode *&root)
{
    if(root != NULL) {
        tree_destroy(root->left);
        tree_destroy(root->right);
        delete root;
    }
}

class Solution {
public:
    TreeNode *flatten_child(TreeNode *root)
    {
        if(root != NULL) {
            if(root->left == NULL && root->right == NULL)
                return root;
            TreeNode *last_node = NULL;
            if(root->left == NULL) {
                return flatten_child(root->right);
            }
            last_node = flatten_child(root->left);
            if(root->right == NULL) {
                root->right = root->left;
                root->left = NULL;
                return last_node;
            }
            last_node->right = root->right;
            last_node->left = NULL;
            root->right = root->left;
            root->left = NULL;
            return flatten_child(last_node->right);
        }
    }

    void flatten(TreeNode *root)
    {
        if(root != NULL)
            flatten_child(root);
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {3, 2, 1, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    TreeNode *tree = NULL;
    tree_create(tree, vec.begin(), vec.end());
    tree_traverse(tree);
    cout << endl;
    Solution sol;
    sol.flatten(tree);
    tree_structure(tree);
    tree_destroy(tree);

    return 0;
}
