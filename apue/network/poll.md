## poll

poll相比于select的优点：

* 可以监听的描述符个数没有限制，可以用数组存储也可以用malloc动态分配，而select中fd_set的大小是有限制的

poll与select共同的缺点：

* 需要在用户态和内核态之间拷贝描述符集合，且当描述符数量很多时，开销很大
* 调用时返回的是激活的描述符的个数，但是依然需要对所有监听的套接字进行遍历

``` C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <poll.h>

#define MAX_FD 1024

int stop = 0;
int current_fd_len = 0;
char buf[1024];

struct pollfd watch_read_fds[MAX_FD];
struct pollfd read_fds[MAX_FD];

void net_watch(int fd) {
    int i = 0;
    for(i = 0; i != current_fd_len; ++i) {
        if(watch_read_fds[i].fd < 0) {
            watch_read_fds[i].fd = fd;
            watch_read_fds[i].events = POLLIN;
            watch_read_fds[i].revents = 0;
            break;
        }
    }

    if(i >= current_fd_len) {
        watch_read_fds[i].fd = fd;
        watch_read_fds[i].events = POLLIN;
        watch_read_fds[i].revents = 0;
        ++current_fd_len;
    }
}

void server_run(int listen_sock) {
    for(int i = 0; i != MAX_FD; ++i) {
        watch_read_fds[i].fd = -1;
        read_fds[i].fd = -1;
    }

    /**
     * 将最开始创建的socket加入到监听的集合
     */
    watch_read_fds[0].fd = listen_sock;
    watch_read_fds[0].events = POLLIN;
    ++current_fd_len;
    while(! stop) {
        memcpy(read_fds, watch_read_fds, MAX_FD * sizeof(struct pollfd));
        printf("waiting for connections\n");
        int ready_fd_len = poll(read_fds, current_fd_len, -1);
        if(ready_fd_len < 0) {
            printf("poll error: %s(errno: %d)\n", strerror(errno), errno);
            continue;
        }
        else if(ready_fd_len == 0) {
            printf("poll timeout\n");
            continue;
        }

        /**
         * poll()返回的只是监听集合中激活的fd的个数，但是依然需要遍历所有的套接字
         */
        for(int i = 0; i != current_fd_len; ++i) {
            int read_fd = read_fds[i].fd;
            if(read_fd < 0) {
                continue;
            }

            if(read_fds[i].revents & POLLIN) {
                if(read_fd == listen_sock) {
                    struct sockaddr_in client_addr;
                    int sock_len = sizeof(client_addr);
                    memset(&client_addr, 0, sizeof(client_addr));
                    int accept_fd = accept(listen_sock, (struct sockaddr *)&client_addr, &sock_len);
                    if(accept_fd < 0) {
                        printf("accept error: %s(errno: %d)\n", strerror(errno), errno);
                        continue;
                    }
                    else {
                        char client_ip[16] = "";
                        inet_ntop(AF_INET, &(client_addr.sin_addr.s_addr), client_ip, sizeof(client_ip));
                        printf("%s connected\n", client_ip);
                        net_watch(accept_fd);
                    }
                }
                else {
                    int recv_len = recv(read_fd, buf, sizeof(buf), 0);
                    if(recv_len < 0) {
                        printf("recv error: %s(errno: %d)\n", strerror(errno), errno);
                        continue;
                    }
                    else if(recv_len == 0) {
                    	/**
                    	 * 读取的长度为0，表示对方调用了close函数，
                    	 * 此时需要关闭服务端这边的套接字并将监听集合中对应的套接字置为-1
                    	 */
                        printf("client leave\n");
                        close(read_fd);
                        watch_read_fds[i].fd = -1;
                    }
                    else {
                        printf("recv data: %s\n", buf);
                    }
                }

                --ready_fd_len;
                if(ready_fd_len <= 0) {
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int listen_sock;
    char server_ip[16] = "127.0.0.1";
    short server_port = 6666;
    struct sockaddr_in server_addr;
    int ret;

    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock < 0) {
        printf("socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = server_port;
    inet_pton(AF_INET, server_ip, &(server_addr.sin_addr.s_addr));

    ret = bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret < 0) {
        printf("bind error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    ret = listen(listen_sock, 10);
    if(ret < 0) {
        printf("listen error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    server_run(listen_sock);
}
```