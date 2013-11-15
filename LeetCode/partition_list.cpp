/*
 * author:	luo feng
 * date:	2013/11/15
 * source:	LeetCode OJ
 * title:	Partition List
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
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *p = head, *q = head, *r = NULL;
        bool set = false, first = true;

        while(q) {
            if(!first) {
                if(q->val >= x && !set) {
                    r = p;
                    p = q;
                    q = q->next;
                    set = true;
                }
                else if(q->val < x && set) {
                    p->next = q->next;
                    if(r == head && r->val >= x) {
                        q->next = head;
                        head = q;
                        r = head;
                    }
                    else {
                        q->next = r->next;
                        r->next = q;
                        r = q;
                    }
                    q = p->next;
                }
                else {
                    p = q;
                    q = q->next;
                }             
            }
            else {
                if(q->val >= x) {
                    r = q;
                    q = q->next;
                    set = true;
                }
                else
                    q = q->next;
                first = false;
            }
        }

        return head;
    }
};

int main(int argc, char *argv[])
{
    int arr[] = {};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr+len);
    ListNode *head;

    list_create(head, vec.begin(), vec.end());
    list_traverse(head);
    Solution sol;
    head = sol.partition(head, 3);
    list_traverse(head);
    list_destroy(head);

    return 0;
}
