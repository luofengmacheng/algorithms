/*
 * author:	luo feng
 * date:	2014/3/28
 * source:	LeetCode OJ
 * title:	Sort List
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
	void partion(ListNode *head, ListNode *&l1, ListNode *&l2)
	{
		if(head == NULL) {
			l1 = l2 = NULL;
			return;
		}
		ListNode *p = head, *pp = head;
		ListNode *q = head;
		while(q && q->next) {
			if(p != pp) {
				pp = pp->next;
			}
			p = p->next;
			q = q->next->next;
		}
		pp->next = NULL;
		l1 = head;
		l2 = p;
	}

	ListNode* merge(ListNode *head1, ListNode *head2)
	{
		if(head1 == NULL) {
			return head2;
		}
		if(head2 == NULL) {
			return head1;
		}
		ListNode *head = NULL;
		ListNode *p = NULL;
		while(head1 && head2) {
			if(head1->val < head2->val) {
				if(head == NULL) {
					head = head1;
					p = head1;
				}
				else {
					p->next = head1;
					p = p->next;
				}
				head1 = head1->next;
			}
			else {
				if(head == NULL) {
					head = head2;
					p = head2;
				}
				else {
					p->next = head2;
					p = p->next;
				}
				head2 = head2->next;
			}
		}
		if(head1) {
			p->next = head1;
		}
		else {
			p->next = head2;
		}
		return head;
	}

    ListNode *sortList(ListNode *head)
    {
    	if(head == NULL || head->next == NULL)
    		return head;

    	ListNode *l1 = NULL, *l2 = NULL;
    	partion(head, l1, l2);
    	l1 = sortList(l1);
    	l2 = sortList(l2);

    	return merge(l1, l2);
    }
};

int main()
{
	ListNode *list;
	int a[] = {5, 3, 7, 1, 9};
	vector<int> ivec(a, a + 5);
	list_create(list, ivec);
	list_traverse(list);
	cout << endl;
	Solution sol;
	list = sol.sortList(list);
	list_traverse(list);
	cout << endl;
	list_destroy(list);

	return 0;
}