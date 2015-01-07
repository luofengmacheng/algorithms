## 解决ubuntu 13.04中fopen打开大于2GB文件失败的问题

### 1 问题的由来

在ubuntu中运行别人的一个程序，这个程序打开一个文件，读取数据，进行处理。

``` C
FILE *fin;

fin = fopen(train_file, "rb");
if (fin == NULL) {
	printf("ERROR: training data file not found!\n");
	exit(1);
}

/* read data and process it */
```

但是，程序打印ERROR: training data file not found!就退出了。

### 2 分析问题

也就是说打开文件失败了，个人觉得，可能的原因有以下几个：

* 路径错误
* 权限问题

路径错误是不可能的，因为笔者是直接将处理文件拷贝到可执行文件所在目录下。

考虑权限问题，于是，将权限修改为777，问题依旧，因此，也不可能是权限问题。

想到有个perror可以打印错误信息，于是，就在printf下面添加了perror("error");，错误信息为：

```
error: Value too large for defined data type
```

想到，可能是处理的文件太大了，处理的文件有2.1GB，很有可能。

在网上搜索，发现确实有这个问题。

### 3 解决问题

在编译选项中添加 -D_FILE_OFFSET_BITS=64 即可。

### 4 小结

从以上知道，在编程时，一定要给出确切的错误信息。在这里，文件打开失败一定是文件不存在吗，当然不一定，有可能还有别的原因。

在这里，由于有源代码，可以进入查看，然后修改，如果没有源代码，那给出的错误信息就对用户有一定的误导。

因此，尽量用系统的错误信息打印语句，像perror、strerror都可以。

参考文档：

1 [linux环境下读写超过2G的大文件](http://blog.163.com/b__v/blog/static/70977362011315103653804/)
