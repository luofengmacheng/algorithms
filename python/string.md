## python中的字符串

编写各类程序时，字符串是比不可少的。在python中，字符串又有它独有的特性。

### 1 字符串字面值

字符串字面值就是程序中的字符串常量。

#### 1.1 python中的字符串表示方法

在python中，可以使用单引号或者双引号表示字符串。因此，C语言中的字符串"hello world"可以写成'hello world'和"hello world"。另外，python还引入了三引号(三个单引号或者三个双引号)。三引号的特点在于：可以包含多行。而单引号和双引号是不能够包含多行的，但是，单引号和双引号可以通过在行末添加\表示多行。

#### 1.2 自然字符串

python中有个独特的自然字符串，它的效果是`所见即所得`，即字符串中所有的转义都失效。自然字符串是在字符串前面添加r或者R。自然字符串通常用来处理`正则表达式`。

例如，字符串"first\n"和自然字符串r"second\n"。

``` python
#!/usr/bin/python
s1 = "first\n"
s2 = r"second\n"
print s1
print s2
```

输出：

```
first

second\n
```

也就是说，自然字符串中写的什么，打印的就是什么。

那么，问题来了，如果字符串是r"c:\data\"(windows使用的目录结构)，打印什么呢？

按照上面的理解，自然字符串是所见即所得的，应该打印c:\data\。

请看下面的代码：

```
$ cat helloworld.py
#!/usr/bin/python
# filename: helloworld.py
s = r"c:\data\"
print s
$ File "./helloworld.py", line 3
    s = r"c:\data\"
                  ^
SyntaxError: EOL while scanning string literal
```

情况出乎我们的意料，问题出在最后一个字符\，在最后它还是将"转义了，那么，解释器就会继续寻找字符串的结尾，没有找到，因此，就出错了。

于是，要想得到字符串c:\data\，还是使用"c:\data\\"。

#### 1.3 Unicode字符串

Unicode字符串主要用来处理非英语的字符串。Unicode字符串的表示方法是，在字符串前面添加u或者U。

#### 1.4 字符串的连接

在python中，如果两个字符串字面值相邻放着，它们就会被自动连接。

例如："hello""world"，会自动转换成"helloworld"。


