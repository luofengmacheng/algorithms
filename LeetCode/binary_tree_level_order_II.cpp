/*
 * author:	luo feng
 * date:	2013/10/24
 * source:	LeetCode OJ
 * title:	Binary Tree Level Order Traversal II
 * language:	C++
 */

#include <iostream>
#include <stack>
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
    vector<vector<int> > levelOrderBottom(TreeNode *root)
    {
        if(root == NULL)
            return vector<vector<int> >(0);

        queue<pair<TreeNode *, int> > que;
        stack<vector<int> > sta;
        vector<int> ivec;

        TreeNode *pnode = root;
        int level = 0;
        pair<TreeNode *, int> pair_data;
        que.push(make_pair(pnode, 1));
        while(!que.empty()) {
            pair_data = que.front();
            que.pop();
            pnode = pair_data.first;
            level = pair_data.second;
            ivec.push_back(pnode->val);
            if(que.empty() || level != que.front().second)
                sta.push(ivec);
            if(pnode->left) {
                que.push(make_pair(pnode->left, level+1));
            }
            if(pnode->right) {
                que.push(make_pair(pnode->right, level+1));
            }
        }

        vector<vector<int> > vec;
        while(!sta.empty()) {
            ivec = sta.top();
            vec.push_back(ivec);
            sta.pop();
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
    
    tree_destory(&tree);

    return 0;
}
