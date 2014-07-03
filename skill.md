1 远程重启计算机
```
echo b > /proc/sysrq-trigger
```

2 查看内存使用情况
```
free -m //以MB为单位查看内存使用情况
```

3 修改计算机的可用内存

对于Redhat系(包括Fedora)

修改/etc/grub.conf，在kernel一行最后添加mem=1G就能够将可用内存修改为1GB
```
title Red Hat Enterprise Linux Server (2.6.27)
        root (hd0,1)
        kernel /vmlinuz-2.6.27 ro root=/dev/VolGroup00/LogVol00 rhgb quiet acpi=ht mem=1G
        initrd /initrd-2.6.27.img
```

4 查看系统的IO统计信息
```
iostat -k 3 //以KB打印结果，3秒显示一次
```

5 将一个进程放入后台，并使它不受前台的影响，特别是用于远程连接时
```
./test //运行程序
^Z //ctrl+z使程序暂停
bg %(jobid) //将程序放入后台运行
disown -h %(jobid)
```
