/* 
 * author:	luo feng
 * date:	2013/12/19
 * source:	LeetCode OJ
 * title:	Rotate List
 * language:	C++
 */

#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void list_create(ListNode *&head, vector<int> vec)
{
    ListNode *pnode = NULL;
    head = NULL;

    for(vector<int>::iterator iter = vec.begin();
                              iter != vec.end(); ++iter) {
        if(head) {
            pnode->next = new ListNode(*iter);
            pnode = pnode->next;
        }
        else {
            head = new ListNode(*iter);
            pnode = head;
        }
    }
}

void list_traverse(ListNode *head)
{
    ListNode *pnode = head;

    while(pnode) {
        cout << pnode->val << " ";
        pnode = pnode->next;
    }
}

void list_destroy(ListNode *&head)
{
    ListNode *pnode = NULL;

    while(head) {
        pnode = head->next;
        delete head;
        head = pnode;
    }
}

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        stack<ListNode *> sta;
        ListNode *pnode = head, *rear = NULL;
        int len = 0;

        if(head == NULL || k == 0)
            return head;

        while(pnode) {
            sta.push(pnode);
            pnode = pnode->next;
            ++len;
        }

        k %= len;
        ++k;
        rear = sta.top();
        while(k--) {
            pnode = sta.top();
            sta.pop();
        }

        rear->next = head;
        head = pnode->next;
        pnode->next = NULL;

        return head;
    }
};

int main(int argc, char *argv[])
{
    ListNode *head = NULL;
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    list_create(head, vec);
    list_traverse(head);
    cout << endl;
    Solution sol;
    head = sol.rotateRight(head, 2);
    list_traverse(head);
    cout << endl;
    list_destroy(head);

    return 0;
}
