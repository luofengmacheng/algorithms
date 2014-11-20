## 阿里巴巴一面(挂掉)2014/9/12

> 给定一个存储数字的数组，将数组按照频度排序，相同频度的数字按照第一个出现的相对顺序进行排序。

基本思想：pair<int, int>保存某个数字和它的频度，用一个顺序容器vector保存这些数字和它们的频度。依次访问数组中的元素，访问到某个元素时，在vector中查找该元素是否存在，如果存在，频度自增，如果不存在，就将该数字和频度1放到vector中。然后按照频度进行稳定的排序。再将数字部分输出到结果数组中即可。

``` C++
struct cnt_comp {
    bool operator()(pair<int, int> p1, pair<int, int> p2)
    {
        return p1.second > p2.second;
    }
};

void cnt_sort(vector<int> &num, vector<int> &res)
{
    vector<pair<int, int> > mp;

    for(vector<int>::iterator viter = num.begin();
                              viter != num.end(); ++viter) {
        vector<pair<int, int> >::iterator iter;
        for(iter = mp.begin(); iter != mp.end(); ++iter) {
            if(*viter == (iter->first)) {
                iter->second++;
                break;
            }
        }

        if(iter == mp.end()) {
            mp.push_back(make_pair(*viter, 1));
        }
    }

    stable_sort(mp.begin(), mp.end(), cnt_comp());

    for(vector<pair<int, int> >::iterator iter = mp.begin();
                                          iter != mp.end(); ++iter) {
        res.push_back(iter->first);
    }
}
```

备注：

面试问到的其它问题：

1 如何查看CPU的负载？

2 如何使用tcpdump打印某个时间段的数据包？

3 如果让你设计一个购物网站，你如何做？

同学面试问到的问题：

1 top命令的作用？

2 如何杀死一个进程？kill命令的3和9的作用？

3 当在浏览器中输入域名后发生了什么？

4 HTTP中404是什么意思？重定向是什么意思？

5 mysql中有两种存储引擎，它们的优缺点和应用场景？视图和触发器？

6 如何保证网站的安全？

7 如何查看系统负载？load的三个参数的意义？

8 三个线程，一个线程必须等待其它两个线程结束？

9 C++中静态函数可以是虚函数吗？