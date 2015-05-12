## linux命令行下执行java程序

运行java程序之前要安装jdk和jre，一般jdk中包含了jre。

### 1 没有包结构的情形

没有包结构的情况比较简单，比较适合小的工程。

编写代码hello.java：

``` java
public class hello {

	
	public static void main(String[] args) {
		System.out.println("hello");
	}
}
```

然后就可以直接在命令行下运行：

```
javac hello.java

java hello
```

### 2 有包结构的情形

当代码前面有package语句时，package后面的包名必须是当前代码所在的目录名。

例如：

``` java
package luo;

public class hello {

	
	public static void main(String[] args) {
		System.out.println("hello");
	}
}
```

把它编译为字节码：

```
javac hello.java
```

执行时要注意两点：

* 1 必须在包的目录的上层目录中执行，例如，这里是luo这个包，就必须在luo这个目录的上层目录中执行。
* 2 执行的主类必须带有主类的包结构，例如，这里的主类hello位于luo这个包中，执行时就必须用luo.hello。

因此，在luo这个文件夹所在的文件夹中执行java luo.hello。

### 3 引用其它的jar包

如果代码中引用了其它的jar包，则需要在编译和运行时能够找到那些类。

http://blog.sina.com.cn/s/blog_637800000100r904.html
