/*
 * author:	luo feng
 * date:	2013/10/23
 * source:	LeetCode OJ
 * title:	Binary Tree Inorder Traversal
 * language:	C++
 */

#include <iostream>
#include <queue>
#include <stack>
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
    vector<int> inorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> sta;
        TreeNode *pnode = root;
        vector<int> vec;

        while(pnode || !sta.empty()) {
            while(pnode) {
                sta.push(pnode);
                pnode = pnode->left;
            }
            if(!sta.empty()) {
                pnode = sta.top();
                vec.push_back(pnode->val);
                sta.pop();
                pnode = pnode->right;
            }
        }
        return vec;
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
    vec = sol.inorderTraversal(tree);
    tree_destory(&tree);
    int i = 0;
    while(i < vec.size())
        cout<<vec.at(i++);
    cout<<endl;

    return 0;
}
