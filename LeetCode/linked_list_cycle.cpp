/*
 * author:	luo feng
 * date:	2014/3/26
 * source:	LeetCode OJ
 * title:	LRU Cache
 * language:	C++
 */

#include <iostream>
using namespace std;

class Solution {
public:
	bool hasCycle(ListNode *head)
	{
		ListNode *fast = head, *slow = head;

		while(fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if(slow == fast) {
				break;
			}
		}
		return ((fast == NULL) || (fast->next == NULL));
	}
};

int main()
{

}