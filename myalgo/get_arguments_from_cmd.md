## 从命令行获取参数的技巧

在编写程序时，我们时常要从命令行获取用户的参数，从而来设置运行时的一些信息。

### 1 需求

使用linux的命令时，我们时常会提供一些选项或者参数，例如：

```
ls -a
```

上面的命令使用-a选项，从而显示当前目录的所有文件和目录，包括隐藏的文件或者目录。

那么，我们在编程时如何实现这样的功能呢？

### 2 命令行参数简介

``` C
/* hello.c */
#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

	for(i = 0; i < argc; ++i) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	return 0;
}
```

了解C语言的人一定不会对上面的代码陌生，我们这里主要看main的参数：

* argc: 命令行参数的个数
* argv: 命令行参数的字符串数组

上面的代码的执行结果为：

```
arg 0: ./hello
arg 1: i
arg 2: love
arg 3: you
```

在执行时，我们给定了三个参数，分别是i、love、you。程序获得了参数之后，argc = 4，argv就是一个有4个字符串的数组。

* argv[0] = ./hello
* argv[1] = i
* argv[2] = love
* argv[3] = you

### 3 编程获取命令行参数

如1中所说的，假设我们的程序有一个计数器，我们要通过命令行参数来设定它的起始值和最大值，分别是:int cnt和int max_cnt。

程序大致如下：

``` C
int main(int argc, char *argv[])
{
	int cnt = 0;
	int max_cnt = 0;

	/* get arguments from cmd */

	/* some code */

	return 0;
}
```

我们有两种方式实现。

第一：要求参数是有顺序的，即先设置cnt，再设置max_cnt: ./hello 5 10，这里将计数器的初始值设置为5，并且最大值为10。

第二：不要求参数有顺序: ./hello -c 5 -m 10。

我想大多数人都倾向于采用第二种方式，而且当参数较多时，第一种方式不直观，用户乍一看去，根本不知道参数设置的是什么，而且用户还要费心记住参数的顺序。

因此，这里给出第二种方式的一种实现：

``` C
/*
 * str: 要查找的参数，比如这里的"-c"和"-m"
 * has_value: 是否需要值，有的参数只是一个开关，并不需要值
 * argc: 命令行参数个数
 * argv: 命令行参数数组
 */
int arg_pos(const char *str, bool has_value, int argc, char **argv)
{
	int i = 0;

	/* 由于第0个元素是程序名，因此不予考虑 */
	for(i = 1; i < argc; ++i) {
		if(!strcmp(argv[i], str)) {
			if(i == argc-1 && has_value) {
				/* 如果这是最后一个元素，并且该选项需要值 */
				/* 说明缺少了选项值                      */
				printf("argument missing for %s\n", str);
				exit(1);
			}
			return i;
		}
	}

	return -1;
}

int main(int argc, char *argv[])
{
	int cnt = 0;
	int max_cnt = 0;

	/* get arguments from cmd */
	int i = 0;
	if((i = arg_pos("-c", true, argc, argv)) > 0) cnt = atoi(argv[i+1]);
	if((i = arg_pos("-m", true, argc, argv)) > 0) max_cnt = atoi(argv[i+1]);

	/* some code */
	printf("%d %d\n", cnt, max_cnt);

	return 0;
}
```

这种实现方式很简单，只是遍历命令行参数数组，进行匹配，但是代码还是比较简洁的。

不知道大家还有没有更加优美的实现方式？

### 4 小结

本文简单介绍了命令行参数，并且给出了获取命令行参数的一种方法。
