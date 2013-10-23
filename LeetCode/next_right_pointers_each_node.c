/*
 * author:	luo feng
 * date:	2013/10/21
 * source:	LeetCode OJ
 * title:	Populating Next Right Pointers in Each Node
 * d-level:	difficult level-3
 */

#include <stdio.h>
#include <stdlib.h>

struct _TreeLinkNode {
    int val;
    struct _TreeLinkNode *left, *right, *next;
};

typedef struct _TreeLinkNode TreeLinkNode;

void tree_create(TreeLinkNode **tree, int arr[], int size)
{
    if(size <= 0)
        return;
    TreeLinkNode **queue = (TreeLinkNode**)calloc(size, sizeof(TreeLinkNode*));
    int head = 0, back = 0;
    int i = 0;

    TreeLinkNode *pnode = (TreeLinkNode*)calloc(1, sizeof(TreeLinkNode));
    pnode->left = NULL;
    pnode->right = NULL;
    pnode->next = NULL;
    pnode->val = arr[0];
    *tree = pnode;
    queue[back++] = pnode;
    i = 1;
    while(i < size) {
        TreeLinkNode *l_child = NULL, *r_child = NULL;
        if(i < size && arr[i] != 0) {
            l_child = (TreeLinkNode*)calloc(1, sizeof(TreeLinkNode));
            l_child->left = NULL;
            l_child->right = NULL;
            l_child->next = NULL;
            l_child->val = arr[i++];
        }
        else
            i++;
        if(i < size && arr[i] != 0) {
            r_child = (TreeLinkNode*)calloc(1, sizeof(TreeLinkNode));
            r_child->left = NULL;
            r_child->right = NULL;
            r_child->next = NULL;
            r_child->val = arr[i++];
        }
        else
            i++;
        TreeLinkNode *qnode = queue[head++];
        qnode->left = l_child;
        qnode->right = r_child;
        if(l_child)
            queue[back++] = l_child;
        if(r_child)
            queue[back++] = r_child;
    }
    free(queue);
}

void tree_traverse(TreeLinkNode *tree)
{
    if(tree == NULL)
        return;

    if(tree->next)
        printf("%d\t", tree->val);
    else
        printf("%d-null\t", tree->val);

    if(tree->left)
        tree_traverse(tree->left);

    if(tree->right)
        tree_traverse(tree->right);
}

void connect(TreeLinkNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL)
            return;
        TreeLinkNode *myqueue[1024];
        int level_queue[1024];
        memset(myqueue, 0, 1024*sizeof(TreeLinkNode *));
        int head = 0, back = 0;
        myqueue[back] = root;
        level_queue[back] = 1;
        back++;
        while(head != back) {
            TreeLinkNode *head_node = myqueue[head];
            int cur_level = level_queue[head];
            head++;
            if(head_node->left && head_node->right) {
                head_node->left->next = head_node->right;
            }
            if(head != back) {
                int next_level = level_queue[head];
                if(cur_level == next_level) {
                    if(head_node->right)
                        head_node->right->next = myqueue[head]->left;
                }
                else {
                        if(head_node->right)
                            head_node->right->next = NULL;
                }
            }
            if(head_node->left) {
                myqueue[back] = head_node->left;
                level_queue[back] = cur_level+1;
                back++;
            }
            if(head_node->right) {
                myqueue[back] = head_node->right;
                level_queue[back] = cur_level+1;
                back++; 
            }
        }
}

void tree_level_print(TreeLinkNode *tree)
{
    TreeLinkNode *queue[1024];
    int head = 0, back = 0;

    queue[back++] = tree;
    while(head != back) {
        TreeLinkNode *pnode = queue[head++];
        if(pnode->left)
            queue[back++] = pnode->left;
        while(pnode) {
            printf(" %d ", pnode->val);
            pnode = pnode->next;
        }
        printf(" # ");
    }
}

void tree_destroy(TreeLinkNode **tree)
{
    if(*tree == NULL)
        return;

    if((*tree)->left)
        tree_destroy(&((*tree)->left));

    if((*tree)->right)
        tree_destroy(&((*tree)->right));

    free(*tree);
}

int main(int argc, char *argv[])
{
    int array[] = {8,5,-8,9,8,-1,9,5,-4,5,6,5,-6,-7,9,7,4};
    int len = sizeof(array)/sizeof(int);

    TreeLinkNode *tree;
    tree_create(&tree, array, len);
    tree_traverse(tree);
    connect(tree);
    tree_level_print(tree);
    tree_destroy(&tree);

    return 0;
}
