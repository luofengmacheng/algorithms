本文件夹包含6个源文件，其中有三个是通过rpcgen生成的。
用户编写的程序有：
square.x client.c server.c

对square.x运行以下命令：
```
rpcgen -C square.x
```
就会生成三个文件：square.h square_clnt.c square_svc.c

square.x中定义了远程过程调用中传递的参数以及过程的定位信息(程序名，版本号，过程号)，也就是客户机和服务器通信的信息。

square.h中定义了客户端和服务器调用的对应的函数，比如：

在square.x中定义了一个过程：square_out SQUAREPROC(square_in)，那么在square.h中就会生成
```
extern  square_out * squareproc_1(square_in *, CLIENT *);
extern  square_out * squareproc_1_svc(square_in *, struct svc_req *);
```
squareproc_1()是客户端上执行的函数，squareproc_1_svc是()是服务器上执行的函数。

square_clnt.c客户端上执行的函数squareproc_1()的定义。

square_svc.c是服务器的主要两个函数，一个是main函数，其中包含了RPC的一些初始化操作，另一个是square_proc_1()，它对收到的请求进行响应，并调用合适的函数。

client.c是用户编写的客户端主程序，它可以创建CLIENT，并调用squareproc_1()。

server.c是用户编写的远程过程squareproc_1_svc()的实际代码。

小结：
* square.x 定义了客户端与服务器通信时传递的参数和过程的定位信息。
* client.c 客户端可以自己决定调用本地函数。
* server.c 定义服务器的远程过程。
