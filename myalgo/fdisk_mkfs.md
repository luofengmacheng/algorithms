## fdisk与mkfs

当有了一个新磁盘之后，如何才能使用它呢？

fdisk用于对磁盘进行分区，此时分区的磁盘里面是没有东西的，只是对磁盘进行划分，并在分区表中保存磁盘的划分格局。mkfs用于在分区上创建文件系统，其实就是保存文件系统的一些数据结构。从另一个方面来说，fdisk操作的对象是整个磁盘，而mkfs操作的对象则是分区。

### 1 fdisk

fdisk命令用于对磁盘进行分区，常用的命令有：

* d 删除分区
* l 列出已知的分区类型
* m 列出菜单
* n 添加分区
* p 列出分区表
* q 不保存退出
* t 改变分区类型
* w 把分区表写入硬盘并退出

例如，在我的系统上运行：

![](https://github.com/luofengmacheng/algorithms/blob/master/myalgo/pics/fdisk_p.png)

结果显示：我的磁盘是500GB。该磁盘有255个盘面(head)，每个盘面有60801个磁道(cylinder)，每个磁道有63个扇区，总共有976773168个扇区(255 * 60801 * 63 = 976768065)，有一些存放元数据。扇区大小和I/O大小都是512B。

sda硬盘有三个分区，1个主分区(sda1)、1个扩展分区(sda2)以及一个逻辑分区(sda5，1~4用于主分区)，sda1分区的起始扇区是2048，终止扇区是968454143，Blocks表示的是容量，单位是KB，则sda1有484226048KB=461.79GB(也即是(End-Start)*512/1024/1024/1024)，sda2分区的起始扇区是968456190，终止扇区是976771071，容量是4157441KB=3.96GB，大约是4GB，其中Id与System是对应的，可以只看System。在sda1的Boot列有个*，表明sda1是活动分区。用a命令可以开启和关闭活动分区标志。

### 2 mkfs

mkfs命令对分区进行格式化。

一般有两种方式：

* mkfs -t [fstype] [partition]
* mkfs.[fstype] [partition]

另外还有mke2fs，该命令支持ext2文件系统。

例如，将sda6格式化为ext3：

```
mkfs.ext3 /dev/sda6
```

然后，挂载该分区。

```
// 创建挂载的目录
mkdir /mnt/sda6

// 将该硬盘挂载到该目录
mount /dev/sda6 /mnt/sda6
```

参考资料：

1 [Linux磁盘分区与格式化](http://blog.chinaunix.net/uid-23354495-id-1740679.html)

2 [Linux下fdisk命令操作磁盘详解--添加、删除、转换分区等](http://www.linuxidc.com/Linux/2012-06/61873.htm)
