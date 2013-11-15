/*
 * author:	luo feng
 * date:	2013/11/15
 * source:	LeetCode OJ
 * title:	Remove Duplicates from Sorted List II
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void list_create(ListNode *&head, vector<int>::iterator beg, vector<int>::iterator end)
{
    head = NULL;

    ListNode *p = NULL, *q = NULL;
    while(beg != end) {
        p = new ListNode(*beg);
        if(head == NULL) {
            head = p;
            q = head;
        }
        else {
            q->next = p;
            q = q->next;
        }
        ++beg;
    }
}

void list_traverse(ListNode *head)
{
    ListNode *p = head;

    cout << "[ ";
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << "]" << endl;
}

void list_destroy(ListNode *&head)
{
    ListNode *p = NULL;
    while(head) {
        p = head;
        head = head->next;
        delete p;
    }
}

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if(head == NULL)
            return head;

        ListNode *p, *q, *r;
        bool set = false;

        p = head;
        q = head->next;
        r = head;
        while(q) {
            if(p->val == q->val) {
                set = true;
                p->next = q->next;
                delete q;
                q = q->next;
            }
            else if(p->val != q->val && !set) {
                r = p;
                p = q;
                q = q->next;
            }
            else if(p->val != q->val && set) {
                if(p == head) {
                    head = p->next;
                    delete p;
                    p = q;
                    q = q->next;
                }
                else {
                    r->next = p->next;
                    delete p;
                    p = r->next;
                    q = q->next;
                }
                set = false;
            }
        }

        if(set) {
            if(p == head) {
                head = p->next;
                delete p;
            }
            else {
                r->next = p->next;
                delete p;
            }
        }

        return head;
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {1, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr+len);
    ListNode *head;

    list_create(head, vec.begin(), vec.end());
    list_traverse(head);
    Solution sol;
    head = sol.deleteDuplicates(head);
    list_traverse(head);
    list_destroy(head);

    return 0;
}
