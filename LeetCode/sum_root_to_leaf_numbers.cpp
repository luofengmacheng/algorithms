/*
 * author:	luo feng
 * date:	2013/11/6
 * source:	LeetCode OJ
 * title:	Sum Root to Leaf Numbers
 * language:	C++
 */

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
} TreeNode;

void tree_create(TreeNode **root, const vector<int> &vec)
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
    vector<int> leafDepth(TreeNode *root, int lev)
    {
        if(root == NULL)
            return vector<int>();

        if(root->left == NULL && root->right == NULL) {
            vector<int> vec;
            vec.push_back(lev);
            return vec;
        }
        
        ++lev;

        if(root->left == NULL && root->right) {
            return leafDepth(root->right, lev);
        }

        if(root->left && root->right == NULL) {
            return leafDepth(root->left, lev);
        }

        if(root->left && root->right) {
            vector<int> lvec = leafDepth(root->left, lev);
            vector<int> rvec = leafDepth(root->right, lev);
            for(vector<int>::iterator iter = rvec.begin();
                                      iter != rvec.end(); ++iter) {
                lvec.push_back(*iter);
            }
            return lvec;
        }
    }
    
    int sumNumbers(TreeNode *root) 
    {
        if(root == NULL)
            return 0;
        
        if(root->left == NULL && root->right == NULL) {
            return root->val;
        }
        
        int lev = 0;
        int sum = 0;
        
        vector<int> vec = leafDepth(root, lev);
        for(vector<int>::iterator iter = vec.begin();
                                  iter != vec.end(); ++iter) {
            sum += (root->val) * pow(10, *iter);
        }
        
        if(root->left == NULL && root->right)
            sum += sumNumbers(root->right);
        else if(root->left && root->right == NULL)
            sum += sumNumbers(root->left);
        else
            sum += sumNumbers(root->left) + sumNumbers(root->right);
        
        return sum;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *tree;
    int arr[9] = {8,3,5,0,9,0,0,9,5};
    vector<int> vec(arr, arr+9);
    /*int data = 0;
    while(cin>>data)
        vec.push_back(data);*/
    tree_create(&tree, vec);
//    tree_traverse(tree);
    cout<<endl;
    Solution sol;
    cout<< sol.sumNumbers(tree) <<endl;
    
    tree_destory(&tree);

    return 0;
}
