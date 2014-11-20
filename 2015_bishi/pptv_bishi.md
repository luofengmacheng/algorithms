## PPTV聚力(笔试[武汉]2014/10/9)

1 最大子段和。数组A[]保存的整数有正有负，求其中的某个序列A[i]~A[j]的和最大，求出这个最大的和。

``` C++
int max_sum(int A[], size_t size)
{
    if(A == NULL || size <= 0) {
        throw string("invalid array");
    }

    int max_s = numeric_limits<int>::min(), sum = 0;

    for(size_t i = 0; i < size; ++i) {
        if(sum >= 0) {
            sum += A[i];
        }
        else {
            sum = A[i];
        }

        if(sum > max_s) {
            max_s = sum;
        }
    }

    return max_s;
}
```

2 栈。给定一个整数n，表示入栈顺序是[1, 2, ..., n]，给定一个出栈序列B[]，判断出栈序列是否是入栈序列的合法序列。

``` C++
bool is_pop_seq(int n, int B[])
{
    stack<int> sta;
    int i = 1, j = 0;

    while(i <= n && j < n) {
        while(i <= n && (sta.empty() || sta.top() != B[j])) {
            sta.push(i++);
        }

        if(!sta.empty() && sta.top() == B[j]) {
            sta.pop();
            ++j;
        }
    }

    if(i == n + 1 && j == n && sta.empty()) {
        return true;
    }
    return false;
}
```

3 海量数据处理。有海量的日志数据，查找某天访问的次数最多的IP。(系统内存为2GB)

获取当天的日志数据。对IP进行哈希，映射到1000个小文件中，统计每个小文件中次数最多的IP，然后在这1000个次数最多的IP中选择最多次数的IP。进行映射时，每个小文件的大小小于2GB，如果映射时，某个文件的大小大于2GB，就再对这个文件进行映射，使得每个文件大小都小于2GB。