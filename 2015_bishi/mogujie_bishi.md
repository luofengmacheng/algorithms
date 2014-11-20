## 蘑菇街(笔试[武汉]2014/10/11)

1 逆波兰表示是一种数学表达式方式，所有操作符都置于操作数后面，因此也被称为后缀表示法。编程实现一个函数，能够计算逆波兰表示法表示的字符串，操作数只限于小于100的正整数，操作符只限于加、减、乘、除。

``` C++
int op(int op1, int op2, char oper)
{
    switch(oper) {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    default:
        break;
    }
}

int compute(const string &str)
{
    stack<int> sta;
    bool flag = false;
    int data = 0;

    for(size_t i = 0; i < str.size(); ++i) {
        if(isdigit(str[i])) {
            if(flag) {
                data = data * 10 + str[i] - '0';
            }
            else {
                data = str[i] - '0';
                flag = true;
            }
        }
        else if(isspace(str[i])) {
            if(flag) {
                sta.push(data);
                flag = false;
            }
        }
        else if(str[i] == '+' ||
                str[i] == '-' ||
                str[i] == '*' ||
                str[i] == '/') {
            int op2 = sta.top();
            sta.pop();
            int op1 = sta.top();
            sta.pop();
            sta.push(op(op1, op2, str[i]));
        }
    }
    return sta.top();
}
```

2 有两个较长的单向链表A和B，为了找出节点node，满足node in A且node in B，请设计空间复杂度尽量小的算法，并且编程实现。