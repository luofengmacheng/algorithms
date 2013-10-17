/*
 * author:	luo feng
 * date:	2013/10/17
 * source:	LeetCode OJ
 * title:	Maximum Depth of Binary Tree
 */

#include <stdio.h>
#include <stdlib.h>

struct btree_node {
    int val;
    struct btree_node *left;
    struct btree_node *right;
};

typedef struct btree_node *btree;

void btree_insert_node(btree *bt, struct btree_node *pnode)
{
    struct btree_node *loc = *bt;

    while(loc) {
        if(loc->left && pnode->val < loc->val) {
            loc = loc->left;
        }
        else if(!(loc->left) && pnode->val < loc->val) {
            loc->left = pnode;
            return;
        }
        else if(loc->right && pnode->val > loc->val) {
            loc = loc->right;
        }
        else if(!(loc->right) && pnode->val > loc->val) {
            loc->right = pnode;
            return;
        }
    }
    *bt = pnode;
}

void btree_create(btree *bt, int arr[], int size)
{
    int i = 0;
    *bt = NULL;

    for(i = 0; i < size; i++) {
        struct btree_node *pnode = (struct btree_node*)malloc(sizeof(struct btree_node));
        pnode->val = arr[i];
        pnode->left = NULL;
        pnode->right = NULL;
        btree_insert_node(bt, pnode);
    }
}

void btree_traverse(btree bt)
{
    if(bt) {
        btree_traverse(bt->left);
        printf("%d\t", bt->val);
        btree_traverse(bt->right);
    }
}

int btree_max_depth(btree bt)
{
    int queue_dep[256];
    int d_front = 0, d_back = 0;
    struct btree_node *queue_bt[256];
    int q_front = 0, q_back = 0;
    int max_depth = 0;
    int depth = 0;

    queue_bt[q_back++] = bt;
    queue_dep[d_back++] = 1;
    max_depth = 1;
    while(q_front != q_back) {
        struct btree_node *pnode = queue_bt[q_front++];
        depth = queue_dep[d_front++];
        if(pnode->left) {
            queue_bt[q_back++] = pnode->left;
            queue_dep[d_back++] = depth+1;
        }
        if(pnode->right) {
            queue_bt[q_back++] = pnode->right;
            queue_dep[d_back++] = depth+1;
        }
        if(depth > max_depth)
            max_depth = depth;
    }

    return max_depth;
}

int btree_max_depth_traverse(btree bt)
{
    if(!bt)
        return 0;

    int left_depth = 0, right_depth = 0;
    if(bt->left)
        left_depth = btree_max_depth_traverse(bt->left);

    if(bt->right)
        right_depth = btree_max_depth_traverse(bt->right);

    return left_depth>right_depth ? left_depth+1 : right_depth+1;
}

void btree_destroy(btree *bt)
{
    struct btree_node *pnode = *bt;

    if(pnode->left)
        btree_destroy(&(pnode->left));

    if(pnode->right)
        btree_destroy(&(pnode->right));

    free(pnode);
}

int main(int argc, char *argv[])
{
    int arr[] = {4, 7, 1, 8, 9};
    int len = sizeof(arr)/sizeof(int);
    btree bt;
    btree_create(&bt, arr, len);
    btree_traverse(bt);
    int depth = btree_max_depth_traverse(bt);
    printf("Maximum depth: %d\n", depth);
    btree_destroy(&bt);

    return 0;
}
