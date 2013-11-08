/*
 * author:	luo feng
 * date:	2013/11/8
 * source:	LeetCode OJ
 * title:	Minimum Depth of Binary Tree
 * language:	C++
 */

#include <iostream>
#include <queue>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
} TreeNode;

void tree_create(TreeNode **root, vector<int> vec)
{
    int i = 0;
    *root = NULL;

    if(vec.empty())
        return;
    TreeNode *pnode = new TreeNode(vec.at(0));
    *root = pnode;
    queue<TreeNode *> que;
    que.push(pnode); 
    
    for(i =1; i < vec.size(); i++) {
        TreeNode *qnode = que.front();
        que.pop();
        if(vec.at(i) == 0)
            qnode->left = NULL;
        else {
            pnode = new TreeNode(vec.at(i));
            qnode->left = pnode;
            que.push(pnode);
        }
        i++;
        if(i >= vec.size())
            break;
        if(vec.at(i) == 0)
            qnode->right = NULL;
        else {
            pnode = new TreeNode(vec.at(i));
            qnode->right = pnode;
            que.push(pnode);
        }
    }
}

void tree_traverse(TreeNode *root)
{
    if(root == NULL)
        return;

    if(root->left)
        tree_traverse(root->left);

    cout<<root->val<<"\t";

    if(root->right)
        tree_traverse(root->right);
}

void tree_destory(TreeNode **root)
{
    if(root == NULL)
        return;

    if((*root)->left)
        tree_destory(&((*root)->left));

    if((*root)->right)
        tree_destory(&((*root)->right));

    delete *root;
}

class Solution {
public:
    int minD(TreeNode *root, int lev)
    {
        if(root == NULL)
            return lev;
        
        if(root->left == NULL && root->right == NULL)
            return lev;

        if(root->left == NULL && root->right)
            return minD(root->right, lev + 1);

        if(root->left && root->right == NULL)
            return minD(root->left, lev + 1);
        
        int lh = minD(root->left, lev + 1);
        int rh = minD(root->right, lev + 1);
        
        return lh<rh ? lh : rh;
    }
    
    int minDepth(TreeNode *root) {
        if(root == NULL)
            return 0;
            
        return minD(root, 1);
    }

    int minDepth(TreeNode *root)
    {
        if(root == NULL)
            return 0;

        int lh = minDepth(root->left);
        int rh = minDepth(root->right);

        return lh<rh ? lh+1 : rh+1;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *tree;
    int arr[] = {1, 2};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    tree_create(&tree, vec);
    //tree_traverse(tree);
    Solution sol;
    cout << sol.minDepth(tree) << endl;
    
    tree_destory(&tree);

    return 0;
}
