/*
 * author:	luo feng
 * date:	2013/10/18
 * source:	LeetCode OJ
 * title:	Merge Two Sorted Lists
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void list_create(struct ListNode **l, int arr[], int size)
{
    int i = 0;
    struct ListNode *lnode = NULL;
    *l = NULL;

    for(i = 0; i < size; i++) {
        lnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        lnode->val = arr[i];
        lnode->next = *l;
        *l = lnode;
    }
}

void list_elements(struct ListNode *l)
{
    struct ListNode *lnode = l;

    while(l) {
        printf("%d\t", l->val);
        l = l->next;
    }
}

struct ListNode *list_merge(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *p = l1, *q = l2, *q_prev = l2;
    if(l1 == NULL) {
        return l2;
    }
    if(l2 == NULL) {
        return l1;
    }

    while(p && q) {
        if(p->val > q->val) {
            while(q && p->val > q->val) {
                if(q_prev == q)
                    q = q->next;
                else {
                    q_prev = q;
                    q = q->next;
                }
            }
        }
        l1 = p->next;
        p->next = q;
        if(q_prev == q) {
            l2 = p;
            q_prev = p;
        }
        else {
            q_prev->next = p;
            q_prev = p;
        }
        p = l1;
    }
    if(p && q == NULL) {
        if(q_prev == q) {
            l2 = l1;
            l1 = NULL;
        }
        else {
            q_prev->next = p;
        }
    }

    return l2;
}

void list_destroy(struct ListNode **l)
{
    struct ListNode *lnode = *l;

    while(lnode) {
        *l = lnode->next;
        free(lnode);
        lnode = lnode->next;
    }
}

int main(int argc, char *argv[])
{
    struct ListNode *l1, *l2;
    int arr1[] = {9, 6, 4, 1};
    int len1 = sizeof(arr1)/sizeof(int);
    int arr2[] = {0};
    int len2 = sizeof(arr2)/sizeof(int);

    list_create(&l1, arr1, len1);
    list_create(&l2, arr2, len2);
    printf("array1: ");
    list_elements(l1);
    printf("\n");
    printf("array2: ");
    list_elements(l2);
    printf("\n");
    l2 = list_merge(l1, l2);
    list_elements(l2);
    printf("\n");
    //list_destroy(&l1);
    list_destroy(&l2);

    return 0;
}
