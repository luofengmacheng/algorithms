/*
 * author:	luo feng
 * date:	2013/12/11
 * source:	LeetCode OJ
 * title:	Binary Tree Preorder Traversal
 *              Binary Tree Postorder Traversal
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <stack>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
} TreeNode;

void tree_create(TreeNode *&root, vector<int> vec)
{
    int i = 0;
    root = NULL;

    if(vec.empty())
        return;
    TreeNode *pnode = new TreeNode(vec.at(0));
    root = pnode;
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

void tree_destory(TreeNode *&root)
{
    if(root == NULL)
        return;

    if(root->left)
        tree_destory(root->left);

    if(root->right)
        tree_destory(root->right);

    delete root;
}

class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> sta;
        TreeNode *pnode = root;
        vector<int> vec;

        while(pnode || !sta.empty()) {
            while(pnode) {
                vec.push_back(pnode->val);
                sta.push(pnode);
                pnode = pnode->left;
            }
            if(!sta.empty()) {
                pnode = sta.top();
                sta.pop();
                pnode = pnode->right;
            }
        }
        return vec;
    }

    vector<int> postorderTraversal(TreeNode *root)
    {
        stack<pair<TreeNode *, int> > sta;
        TreeNode *pnode = root;
        vector<int> vec;
        pair<TreeNode *, int> ptnode;

        //从根节点开始，往左下方走，一直走到头，将路径上的每个节点入栈
        while(pnode) {
            sta.push(make_pair(pnode, 0)); //压入栈的有两个信息，一是节点指针，二是其右节点是否被访问过
            pnode = pnode->left;
        }

        while(!sta.empty()) { //当栈非空时
            ptnode = sta.top(); //获取栈顶元素

            //若其右孩子已经被访问过，或是该元素没有右孩子，则由后序遍历的定义，此时就可以访问这个节点了
            if(!ptnode.first->right || ptnode.second) {
                ptnode = sta.top();
                sta.pop();
                vec.push_back(ptnode.first->val);
            }
            else { //若其右孩子存在且它的右孩子没有被访问过，就去处理其右孩子
                ptnode.second = 1;
                sta.pop();
                sta.push(ptnode);
                pnode = ptnode.first->right;
                while(pnode) {
                    sta.push(make_pair(pnode, 0));
                    pnode = pnode->left;
                }
            }
        }
        return vec;
    }
};

void print_res(int x)
{
    cout << x << "\t";
}

int main(int argc, char *argv[])
{
    TreeNode *tree;
    int arr[] = {1, 0, 2, 3};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    tree_create(tree, vec);
    //tree_traverse(tree);
    cout<<endl;
    Solution sol;
    cout << "Preorder Traversal:" << endl;
    vec = sol.preorderTraversal(tree);
    for_each(vec.begin(), vec.end(), print_res);
    cout << endl;
    vec.clear();
    cout << "Postorder Traversal:" << endl;
    vec = sol.postorderTraversal(tree);
    for_each(vec.begin(), vec.end(), print_res);
    cout<<endl;
    tree_destory(tree);

    return 0;
}
