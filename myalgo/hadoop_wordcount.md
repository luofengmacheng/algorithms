## hadoop运行WordCount程序

使用hadoop standalone模式运行WordCount程序。

### 1 安装JDK

从[Java Downloads](http://www.oracle.com/technetwork/java/javase/downloads/index.html)上下载JDK。

把下载的压缩包解压到要安装的目录，笔者一般安装到/usr/local/目录下，因此，把压缩包解压到/usr/local/下。

然后添加环境变量，可以在/etc/profile和~/.bashrc中添加，前者使得所有用户有效，后者只修改当前用户，这里修改~/.bashrc，在该文件末尾添加下列环境变量：

```
export JAVA_HOME=/usr/local/jdk1.7.0_75
export JAVA_BIN=$JAVA_HOME/bin
export PATH=$PATH:$JAVA_BIN
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export JAVA_HOME JAVA_BIN PATH CLASSPATH
```

然后运行下列命令使bashrc立即生效：

```
source .bashrc
```

接着就可以运行javac和java了。

### 2 安装hadoop

从[hadoop Download](http://www.apache.org/dyn/closer.cgi/hadoop/common/)下载hadoop。同样，将它解压到/usr/local/目录下。

然后就可以运行hadoop目录下的bin目录中的hadoop。

### 3 运行WordCount

从网上下载一个WordCount.java程序。

#### 3.1 编译

``` java
javac -classpath /usr/local/hadoop-2.6.0/share/hadoop/common/*:/usr/local/hadoop-2.6.0/share/hadoop/mapreduce/*:/usr/local/hadoop-2.6.0/share/hadoop/tools/lib/* ./WordCount.java
```

为了编译的简便，直接加入了common、mapreduce、tools下的jar包。再将生成的3个class文件打包：

```
jar -cvf WordCount.jar *.class
```

#### 3.2 运行

现在，就可以启动hadoop运行了。

该程序的输入和输出都是文件夹。创建input目录，其中放置要统计的文件。

执行hadoop：

```
/usr/local/hadoop-2.6.0/bin/hadoop jar WordCount.jar WordCount input output
```

其中WordCount.jar就是程序的jar包，WordCount是程序的主类，后面两个参数分别是输入和输出。

运行之后，会生成output目录，其中存放统计的结果。结果的文件夹名为：part-r-0000。可以直接用vi或者gedit查看。
