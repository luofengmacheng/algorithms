/*
 * author:	luo feng
 * date:	2013/10/24
 * source:	LeetCode OJ
 * title:	Balanced Binary Tree
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
    int height(TreeNode *root)
    {
        if(root == NULL)
            return 0;

        int lh = height(root->left);
        int rh = heigth(root->right);
        return lh>rh ? lh+1 : rh+1;
    }

    bool isBalanced(TreeNode *root)
    {
        if(root == NULL)
            return true;

        if(!isBalanced(root->left) ||
           !isBalanced(root->right) ||
           height(root->left) - height(root->right) > 1 ||
           height(root->right) - height(root->left) >1)
            return false;
        else
            return true;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *tree;
    vector<int> vec;
    int data = 0;
    while(cin>>data)
        vec.push_back(data);
    tree_create(&tree, vec);
    //tree_traverse(tree);
    cout<<endl;
    Solution sol;
    
    tree_destory(&tree);

    return 0;
}
