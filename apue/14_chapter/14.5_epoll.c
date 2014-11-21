/*
 * author:	luo feng
 * date:	2014/4/28
 * source:	APUE
 * title:	epoll
 * language:	C
 */

#include <stdio.h>

#define MAX_EVENTS 10

struct epoll_event ev, events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;

int main(int argc, char const *argv[])
{
	socket();
	bind();
	listen();

	epollfd = epoll_create(10);
	if(epollfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		perror("epoll_ctl : listen_sock");
		exit(EXIT_FAILURE);
	}

	for(;;) {
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if(nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for(n = 0; n < nfds; ++n) {
			if(events[n].data.fd == listen_sock) {
				conn_sock = accept(listen_sock, 
					(struct sockaddr *)&local, &addrlen);
				if(conn_sock == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}
				setnonblocking(conn_sock);
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if(epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					perror("epoll_ctl : conn_sock");
					exit(EXIT_FAILURE);
				}
			}
			else {
				do_use_fd(events[n].data.fd);/* read or write */
			}
		}
	}

	return 0;
}