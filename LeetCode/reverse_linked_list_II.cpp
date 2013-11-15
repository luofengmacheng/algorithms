/*
 * author:	luo feng
 * date:	2013/11/15
 * source:	LeetCode OJ
 * title:	Reverse Linked List II
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
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *p, *q, *r;
        int cnt = 1;

        if(head == NULL || head->next == NULL)
            return head;

        if(m == 1) {
            p = head;
            q = head->next;
            while(--n) {
                p->next = q->next;
                q->next = head;
                head = q;
                q = p->next;
            }
        }
        else {
            p = head;
            q = head->next;
            r = q->next;
            while(r && cnt < n-1) {
                if(cnt < m-1) {
                    p = q;
                    q = r;
                    r = r->next;
                }
                else {
                    q->next = r->next;
                    r->next = p->next;
                    p->next = r;
                    r = q->next;
                }
                ++cnt;
            }
        }

        return head;
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr+len);
    ListNode *head;

    list_create(head, vec.begin(), vec.end());
    list_traverse(head);
    Solution sol;
    head = sol.reverseBetween(head, 1, 5);
    list_traverse(head);
    list_destroy(head);

    return 0;
}
