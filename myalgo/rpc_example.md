## RPC编程小例

RPC是Remote Procedure Call的缩写，它能够在本地以函数调用的形式调用远程过程，可以让编写网络程序的程序员集中关注业务逻辑。

下面给出一个简单的返回一个整数的平方的例子。

问题描述：客户端给出一个整数，调用一个本地函数，它就能够将这个整数发送给服务器，得到服务器返回的值，然后显示。

### 1 定义双方数据交换的格式

客户端和服务器之间要进行数据交换，因此，需要定义数据交换的格式。在本例中，客户端发送的是整数，服务器返回的也是整数。因此，可以如下定义：

``` C
// square.x
struct square_in {
	long arg1;
};

struct square_out {
	long res1;
};

program SQUARE_PROG {
	version SQUARE_VERS {
		square_out SQUAREPROC(square_in) = 1;
	} = 1;
} = 0x31230000;
```

如图所示，struct square_in是客户端发送的数据，struct square_out是服务器发送的数据，在下面定义了一个program SQUARE_PROG，这个结构体用于服务器调用程序的定位，0x31230000是这个程序的一个标识，square_out SQUAREPROC(square_in)类似于函数的声明。

对square.x进行编译：
```
rpcgen -C square.x
```

于是，就得到以下4个文件：


| 文件名        | 功能 |
| ------------- | ---- |
| square.h      | 客户端和服务器端数据交互的格式以及函数的定位，例如，当客户端调用squareproc_1时，服务器端就会调用squareproc_1_svc |
| square_xdr.c  | 对交互的数据进行编码 |
| square_clnt.c | 调用函数的本地函数定义，本例就是squareproc_1函数的定义，只是调用clnt_call |
| square_svc.c  | 服务器端调用函数的分发函数，因为可能有多个函数，因此该函数需要对收到的请求进行分析，然后调用合适的函数，本例就是，当收到SQUAREPROC命令时，就会调用squareproc_1_svc |

至此，已经有了客户端与服务器端交互的数据格式，以及客户端和服务器端调用的函数。

### 2 服务端函数定义

上面已经说过，服务器端的函数就是squareproc_1_svc，因此，只需要定义squareproc_1_svc函数即可。

``` C
// server.c
#include "square.h"

square_out *squareproc_1_svc(square_in *inp, struct svc_req *rqstp)
{
	static square_out out;
	out.res1 = inp->arg1 * inp->arg1;

	return (&out);
}
```

这里，只需要将inp中的arg1进行平方，然后返回即可。

### 3 客户端函数调用

这样之后，就可以在客户端调用squareproc_1函数了。

``` C
// client.c
#include "square.h"

int main(int argc, char const *argv[])
{
	CLIENT *cl;
	square_in in;
	square_out *outp;

	if(argc != 3) {
		fprintf(stderr, "usage: client <hostname> <integer_value>\n");
		exit(0);
	}

	cl = clnt_create(argv[1], SQUARE_PROG, SQUARE_VERS, "tcp");
	in.arg1 = atoll(argv[2]);
	if((outp = squareproc_1(&in, cl)) == NULL) { // 这里就是调用squareproc_1
		fprintf(stderr, "%s\n", clnt_sperror(cl, argv[1]));
		exit(0);
	}
	printf("result: %ld\n", outp->res1);

	return 0;
}
```

### 4 构建服务端和客户端

现在，已经有了服务端和客户端的代码，分别是：

服务端：主函数由rpcgen生成，在square_svc.c中，square.h定义交互的数据结构和函数声明，server.c定义服务端调用的函数，square_xdr.c对参数和返回值进行封装的函数。

```
gcc -c server.c
gcc -c square_svc.c
gcc -c square_xdr.c

gcc -o server square_xdr.o server.o square_svc.o
```

客户端：主函数由程序员编写，在client.c中，square.h定义交互的数据结构，square_clnt.c定义客户端本地调用的函数，square_xdr.c对参数和返回值进行封装的函数。

```
gcc -c client.c
gcc -c square_clnt.c
gcc -c square_xdr.c

gcc -o client square_xdr.o square_clnt.o client.o
```

### 5 测试

服务器端运行：

```
sudo ./server
```

客户端运行：

```
sudo ./client
```

注意：必须以root用户运行，否则会出现：

```
Cannot register service: RPC: Authentication error; why = Client credential too weak
unable to register (SQUARE_PROG, SQUARE_VERS, udp).hust@hust-ubuntu:~/test/rpc/server$ sudo ./server
```

测试结果：

![](https://github.com/luofengmacheng/algorithms/blob/master/myalgo/pics/pic1.png)

### 6 小结

RPC能够让用户更多地关注业务逻辑，而减少对网络交互的关注，这样有助于构建网络应用。
