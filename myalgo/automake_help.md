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
