## diff与patch命令的使用

在linux中，我们经常需要比较两个文件，找到两个文件的差异，最常用的就是diff命令了，diff命令的输出称为补丁。

### 1 diff

diff命令用于比较两个文件的差异。

```
$ cat wo1.c
#include <stdio.h>

int main()
{
	int a = 0;

	printf("%d\n", a);

	printf("hello\n");

	return 0;
}
```

```
$ cat wo2.c
#include <stdio.h>

int main()
{
	int a = 0, b = 0;

	printf("%d\n", a);
	printf("%d\n", b);

	return 0;
}
```

上面有两个程序wo1.c和wo2.c，wo2.c对wo1.c进行了修改，添加了b的定义和打印，并且删除了hello的打印。

对wo1.c和wo2.c调用diff命令有：

```
$ diff wo1.c wo2.c
5c5
< 	int a = 0;
---
> 	int a = 0, b = 0;
8,9c8
< 
< 	printf("hello\n");
---
> 	printf("%d\n", b);
```

输出可以看到两个文件的不同之处：

* 5c5表示wo1.c的第5行和wo2.c的第5行有所改变。
* 8,9c8表示wo1.c的8、9两行和wo2.c的第8行有所改变。

在diff中，有三种变化情况：

* a: add
* c: change
* d: delete

通过diff的输出，就可以将wo1.c变成wo2.c：

* 将第5行替换成int a = 0, b = 0;
* 将第8行和第9行替换成printf("%d\n", b);

diff命令有许多选项，常常使用的选项有：

1 -c 上下文输出格式

该选项可以将有所变化的行的附近行也输出，默认是附近三行，也就是上面三行，下面三行，使用-C LINES可以指定显示的行数。

```
$ diff -c wo1.c wo2.c
*** wo1.c	2015-01-20 16:54:41.674398193 +0800
--- wo2.c	2015-01-20 17:02:49.346389351 +0800
***************
*** 2,12 ****
  
  int main()
  {
! 	int a = 0;
  
  	printf("%d\n", a);
! 
! 	printf("hello\n");
  
  	return 0;
  }
--- 2,11 ----
  
  int main()
  {
! 	int a = 0, b = 0;
  
  	printf("%d\n", a);
! 	printf("%d\n", b);
  
  	return 0;
  }
```

该选项的输出上主要有两个变化：

* 在改变的行的前面有个表示变化的符号，这里是!，表示改变。如果是+，表示wo2.c比wo1.c多一行，如果是-，表示wo2.c比wo1.c少一行。
* 显示有所变化的附近的三行，这里由于代码较短，因此，中间的部分全部显示了。但是，从开头可以看出，确实了显示了行前和行后三行。

2 -i 忽略大小写，也就是说，大小写不同的作为相同。

3 -r 递归，当比较两个文件夹时，会递归比较两个文件夹中文件名相同的文件。另外加--ignore-file-name-case选项，可以忽略文件名的大小写。

4 --from-file=FILE 将FILE与每个参数代表的文件进行比较

5 --to-file=FILE 将参数代表的文件与FILE进行比较

6 -X FILE 当比较文件夹时，忽略某文件

### 2 patch

diff的输出称为补丁(patch)，可以使用patch程序对from-file打补丁，从而得到to-file。

```
$ diff wo1.c wo2.c > wo.patch
```

于是，就得到补丁wo.patch。

然后对wo1.c打补丁：

```
$ patch wo1.c wo.patch
patching file wo1.c
```

然后再运行diff，发现什么也没有输出，说明wo1.c通过打补丁，跟wo2.c一样。

### 3 小结

diff比较文件或者文件夹的差异，然后生成补丁文件。patch对文件打补丁，可以对文件进行修复。也就是说，diff的输出是patch的输入。
