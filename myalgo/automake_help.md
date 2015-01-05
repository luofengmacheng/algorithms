## Automake使用帮助

linux下当源文件很多时，可以使用automake工具来构建Makefile文件。

[下载M4](http://ftp.gnu.org/gnu/m4/)

[下载Autoconf](https://ftp.gnu.org/gnu/autoconf/)

[下载Automake](http://ftp.gnu.org/gnu/automake/)

### 1 一个小示例

#### 1.1 创建源代码

在源代码目录下，只有一个文件src/main.c:

``` C
#include <stdio.h>

int main(int argc, char** argv)
{
	printf("Hello, Auto Makefile!\n");

	return 0;
}
```

#### 1.2 构建configure.ac

然后在src目录下执行autoscan生成configure.scan和autoscan.log，将configure.scan重命名为configure.ac，并修改AC_INIT，添加AM_INIT_AUTOMAKE，在最后添加输出文件Makefile。

修改后为：
```
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
# 初始化，定义软件的基本信息：包的名称、版本号、报告BUG的邮箱地址
AC_INIT(main, 1.0, luofenghust@hust.edu.cn)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])
# 表明将用automake生成Makefile
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# 创建输出文件，输出文件名为Makefile
AC_OUTPUT(Makefile)
```

#### 1.3 构建Makefile

在src目录下运行以下命令：

```
# 生成aclocal.m4和autom4te.cache目录
aclocal
# 生成configure文件
autoconf
# 生成config.h.in
autoheader
```

创建Makefile.am文件：

```
AUTOMAKE_OPTIONS=foreign

# 定义要产生的可执行文件名，可能要产生多个可执行文件，这些文件名用空格隔开
bin_PROGRAMS=main

# 定义main这个可执行程序所需要的源文件
main_SOURCES=main.c
```

在src下执行automake：

```
# 生成Makefile.in，并添加一些必要的脚本文件
automake --add-missing
automake
```

#### 1.4 生成可执行文件

```
# 将Makefile.in变成最终的Makefile
./configure
# 执行Makefile，生成可执行文件
make
```

于是，就得到可执行文件main。

#### 1.5 小结

以上一步一步介绍了从源代码生成可执行程序的过程。下面做个小结，并给出更为方便的方法：

在生成可执行程序过程中需要创建两个文件configure.ac和Makefile.am，configure.ac指定可执行程序的程序名和版本，并声明要用automake生成Makefile，Makefile.am说明要生成的可执行程序，以及这些可执行程序依赖的源文件。还可以编辑第三个文件autogen.sh用于包含上面执行的一些命令。

autogen.sh的内容：

``` shell
#!/bin/sh

aclocal

autoconf

autoheader

automake --add-missing
automake
```

因此，总共需要创建configure.ac、Makefile.am和autogen.sh。

然后直接运行autogen.sh之后，就可以直接调用configure和make生成可执行程序了。

参考资料：

1 [例解 autoconf 和 automake 生成 Makefile 文件](http://www.ibm.com/developerworks/cn/linux/l-makefile/)
