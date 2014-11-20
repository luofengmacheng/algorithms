## 携程(笔试[武汉]2014/9/24)

1 判断两个字符串是否相等，如果相等则返回0，不等则返回-1。

``` C++
int issame(const string &str1, const string &str2)
{
    if(str1.size() != str2.size()) {
        return -1;
    }

    for(size_t i = 0; i < str1.size(); ++i) {
        if(str1[i] != str2[i]) {
            return -1;
        }
    }

    return 0;
}
```

2 给定一个链表和一个整数，例如，给定一个链表1 -> 2 -> 3 -> 4 -> 5 -> 6，和一个整数2，将链表转换成2 -> 1 -> 4 -> 3 -> 6 -> 5，如果整数为3，链表则转换成3 -> 2 -> 1 -> 6 -> 5 -> 4，如果整数为4，链表则转换成4 -> 3 -> 2 -> 1 -> 5 -> 6。

``` C++
struct ListNode {
    ListNode *next;
    int data;
};

void list_reverse(ListNode *&head, int v)
{
    if(head == NULL || head->next == NULL || v <= 1) {
        return;
    }

    ListNode *pnode = head; // 每个区段的第一个节点
    ListNode *qnode = head; // 用于将该区段的节点取出来
    ListNode *rnode = head;
    ListNode *pre = head; // 前一个区段的最后一个节点，如果处于第一个区段则为头节点

    while(pnode) {

        int i = 0;
        while(i < v && qnode != NULL) { // 测试以qnode开始后面是否有v个节点 
            qnode = qnode->next;
            ++i;
        }

        if(i < v && qnode == NULL) { // 如果没有v个节点就退出
            return;
        }

        qnode = pnode->next;
        rnode = qnode->next;

        if(pnode == head) {
            for(int i = 1; i < v; ++i) {
                qnode->next = head;
                head = qnode;
                qnode = rnode;
                if(qnode != NULL) {
                        rnode = qnode->next;
                }
            }
            pre->next = qnode;
            pnode = qnode;
        }
        else {
            for(int i = 1; i < v; ++i) {
                qnode->next = pre->next;
                pre->next = qnode;
                qnode = rnode;
                if(qnode != NULL) {
                        rnode = qnode->next;
                }
            }
            pre = pnode;
            pnode->next = qnode;
            pnode = qnode;
        }
    }
}
```

3 写出红黑树的左旋。