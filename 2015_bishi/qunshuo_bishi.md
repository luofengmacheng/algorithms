## 群硕(笔试[武汉]2014/10/8)

1 判断一个整数是否是回文素数。

回文素数：既是回文又是素数。因此，需要两个判断回文和素数的函数。

``` C++
bool is_prime(int num)
{
    if(num == 1) {
        return false;
    }

    for(int i = 2; i <= num / 2; ++i) {
        if(num % i == 0) {
            return false;
        }
    }

    return true;
}

bool is_palindrome(int num)
{
    string snum;
    int n = num;

    while(n) {
        snum += (n % 10) + '0';
        n /= 10;
    }

    for(int i = 0, j = snum.size() - 1; i < j; ++i, --j) {
        if(snum[i] != snum[j]) {
            return false;
        }
    }

    return true;
}

bool is_palindrome_prime(int num)
{
    if(is_prime(num) && is_palindrome(num)) {
        return true;
    }

    return false;
}
```

2 求100~999中能够被4整除，可以开方，有两位数相同。

如果直接按照上面的思路，可以依次对100~999的每个整数判断：(1)被4整除，(2)可以开方，(3)有两个数字相等。

但是，如果直接考虑开方，可以发现，100的开方是10，1000的开方大约是31多，因此，我们只需要判断从10~31的平方是否满足条件(1)(3)。

``` C++
bool is_two_same(int num)
{
    set<int> hash;

    while(num) {
        if(hash.count(num % 10) == 1) {
            return true;
        }
        hash.insert(num % 10);
        num /= 10;
    }

    return false;
}

int main(int argc, char const *argv[])
{
    int num = 0;

    for(int i = 10; i < 32; ++i) {
        num =  i * i;
        if(num % 4 == 0 && is_two_same(num)) {
            cout << num << endl;
        }
    }

	return 0;
}
```

3 给定m和n，从1~n中选择若干个整数，使得它们的和为m，求出所有的组合。

``` C++
vector<vector<int> > mnfind(int m, int n)
{
    if(n == 1 && m == 1) {
        return vector<vector<int> >(1, vector<int>(1, 1));
    }

    if((n == 1 && m != 1) || (m < 0)) {
        return vector<vector<int> >();
    }

    vector<vector<int> > vec1 = mnfind(m - n, n - 1);
    vector<vector<int> > vec2 = mnfind(m, n - 1);

    for(vector<vector<int> >::iterator iter = vec1.begin();
                                       iter != vec1.end(); ++iter) {
        (*iter).push_back(n);
    }

    for(vector<vector<int> >::iterator iter = vec2.begin();
                                       iter != vec2.end(); ++iter) {
        vec1.push_back(*iter);
    }

    return vec1;
}
```