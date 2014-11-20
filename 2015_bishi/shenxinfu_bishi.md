## 深信服(笔试[武汉]2014/10/12)

1 给定一个字符串，只包含字母和空格，统计单词个数。给定函数原型：int stat_word(const char *str)

``` C
int stat_word(const char *str)
{
    if(str == NULL) {
        return 0;
    }

    int cnt = 0;
    bool flag = false;
    const char *s = str;

    while(*s != '\0') {
        if(*s == ' ') {
            if(flag) {
                ++cnt;
                flag = false;
            }
        }
        else {
            if(!flag) {
                flag = true;
            }
        }

        ++s;
    }

    if(flag) {
        return cnt + 1;
    }

    return cnt;
}
```

2 不能使用除malloc/free之外的系统函数，写两个函数create_list和remove_sequence，其中，create_list用数组创建链表，remove_sequence删除链表中的一个序列。以下是节点定义和函数原型：

``` C
struct list {
	int val;
	struct list *next;
}

list* create_list(const int*, int size);

bool remove_sequence(list **, const int*, int size);
```

``` C
list* create_list(const int *arr, int size)
{
    list *root = NULL;
    list *tail = NULL;

    for(int i = 0; i < size; ++i) {
        if(root) {
            list *pnode = (list*)malloc(sizeof(list));
            pnode->next = NULL;
            pnode->val = arr[i];
            tail->next = pnode;
            tail = tail->next;
        }
        else {
            list *pnode = (list*)malloc(sizeof(list));
            pnode->next = NULL;
            pnode->val = arr[i];
            root = pnode;
            tail = pnode;
        }
    }

    return root;
}
```