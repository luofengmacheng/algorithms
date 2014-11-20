## 恒生电子(笔试[武汉]2014/10/11)

1 给定主字符串、子字符串和分隔符，判断主字符串分隔后的字符串是否包含子字符串。函数原型：bool contain(const char *src, const char *pattern, char delim);

``` C++
bool contain(const char* src, const char *pattern, char delim)
{
    if(src == NULL || pattern == NULL) {
        return false;
    }

    string str;
    bool flag = false;

    while(*src != '\0') {
        if(*src == delim) {
            if(flag && str == pattern) {
                return true;
            }
            str.clear();
            flag = false;
        }
        else {
            str += *src;
            flag = true;
        }

        ++src;
    }

    if(flag && str == pattern) {
        return true;
    }

    return false;
}
```

2 有N个人旅游，住在N个房间中，于是，有N把钥匙，那么，钥匙全拿错的情况有多少种，编程实现。

假设前n个人的钥匙全拿错了，那么，可以根据前n个人的结果构造出前n+1个人全拿错的结果。

例如，前3个人都拿错的情况有两种：(1拿2,2拿3,3拿1),(1拿3,2拿1,3拿2)。要求前4个人都拿错的情况：

对于(1拿2,2拿3,3拿1)，将每个人的钥匙分别与4的钥匙交换，可以得到(1拿4,2拿3,3拿1,4拿2)，(1拿2,2拿4,3拿1,4拿3)，(1拿2,2拿3,3拿4,4拿1)。

对于(1拿3,2拿1,3拿2)，将每个人的钥匙分别与4的钥匙交换，可以得到(1拿4,2拿1,3拿2,4拿3)，(1拿3,2拿4,3拿2,4拿1)，(1拿3,2拿1,3拿4,4拿2)。

从上面可以看出：

假设前n个人钥匙全拿错的情况有f(n)中，那么，前n+1个人钥匙全拿错的情况有f(n+1) = n * f(n)。

因此，如果只需要求出情况的个数，可以直接用上面的表达式。

``` C++
int all_wrong(int n)
{

	if(n <= 1) {
		return 0;
	}

	if(n == 2) {
		return 1;
	}

	return (n - 1) * f(n - 1);
}
```

如果要求出全拿错的所有情况，可以使用下面的函数：

``` C++
vector<vector<pair<int, int> > > all_wrong(int n)
{
    if(n <= 1) {
        return vector<vector<pair<int, int> > >();
    }

    if(n == 2) {
        vector<vector<pair<int, int> > > res;
        vector<pair<int, int> > vp;
        vp.push_back(make_pair(1, 2));
        vp.push_back(make_pair(2, 1));
        res.push_back(vp);
        return res;
    }

    vector<vector<pair<int, int> > > res1 = all_wrong(n - 1);
    vector<vector<pair<int, int> > > res;
    typedef vector<pair<int, int> >::iterator VITER;
    typedef vector<vector<pair<int, int> > >::iterator VVITER;
    for(VVITER iter = res1.begin(); iter != res1.end(); ++iter) {
        vector<pair<int, int> > vp = *iter;
        vp.push_back(make_pair(n, n));
        VITER last = vp.end() - 1;
        for(VITER viter = vp.begin(); viter != last; ++viter) {
            swap(viter->second, last->second);
            res.push_back(vp);
            swap(viter->second, last->second);
        }
    }

    return res;
}
```