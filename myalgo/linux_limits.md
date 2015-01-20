## 修改linux的各种限制及ulimit命令的使用

### 1 引言

在linux下有各种限制，用ulimit命令可以显示这些限制：

```
$ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 31912
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 31912
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

### 2 修改限制

最常见要修改的限制是open files，默认是1024，这对于一般的应用是足够的，但是，对于大规模的文件处理时，就需要修改。

修改方式如下：

1 在/etc/security/limits.conf结尾添加

```
* - nofile 40960
```

2 在/etc/pam.d/login添加

session required /lib/security/pam_limit.so

然后重启系统即可，然后用ulimit命令查看。

注意：网上使用ulimit命令修改，在ubuntu上没有效果。
