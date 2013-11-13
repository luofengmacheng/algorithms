/*
 * author:	luo feng
 * date:	2013/11/13
 * source:	LeetCode OJ
 * title:	Binary Tree Zigzag Level Order Traversal
 * language:	C++
 */

#include <iostream>
#include <stack>
#include <queue>
#include <iterator>
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        if(root == NULL)
            return vector<vector<int> >(0, vector<int>());

        stack<TreeNode *> sta1, sta2;
        vector<vector<int> > vec;
        vector<int> ivec;
        TreeNode *pnode = NULL;
        sta1.push(root);
        ivec.push_back(root->val);
        vec.push_back(ivec);
        ivec.clear();
        while(!sta1.empty()) {
            while(!sta1.empty()) {
                pnode = sta1.top();
                sta1.pop();
                if(pnode->right) {
                    sta2.push(pnode->right);
                    ivec.push_back(pnode->right->val);
                }
                if(pnode->left) {
                    sta2.push(pnode->left);
                    ivec.push_back(pnode->left->val);
                }
            }

            if(!ivec.empty()) {
                vec.push_back(ivec);
                ivec.clear();
            }

            while(!sta2.empty()) {
                pnode = sta2.top();
                sta2.pop();
                if(pnode->left) {
                    sta1.push(pnode->left);
                    ivec.push_back(pnode->left->val);
                }
                if(pnode->right) {
                    sta1.push(pnode->right);
                    ivec.push_back(pnode->right->val);
                }
            }

            if(!ivec.empty()) {
                vec.push_back(ivec);
                ivec.clear();
            }
        }

        return vec;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *tree;
    int arr[] = {3, 9, 20, 0, 0, 15, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    tree_create(&tree, vec);
    //tree_traverse(tree);
    Solution sol;
    vector<vector<int> > vvec = sol.zigzagLevelOrder(tree);
    for(vector<vector<int> >::iterator iter1 = vvec.begin();
                                       iter1 != vvec.end(); ++iter1) {
        cout << "[ ";
        for(vector<int>::iterator iter2 = (*iter1).begin();
                                  iter2 != (*iter1).end(); ++iter2) {
            cout << *iter2 << " ";
        }
        cout << "]" << endl;
    }
    
    tree_destory(&tree);

    return 0;
}
