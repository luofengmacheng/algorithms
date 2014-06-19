/*
 * author:	luo feng
 * date:	2014/6/13
 * source:	APUE
 * title:	poll
 * language:	C
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <errno.h>
#include <netinet/in.h>

int            server_max_pollfd;
int            sock_fd;
struct pollfd *server_pollfd;

int server_init(int init_fd)
{
	server_max_pollfd = 1;

	if((server_pollfd = malloc(sizeof(struct pollfd) * server_max_pollfd)) == NULL) {
		fprintf(stderr, "server_init : out of memory\n");
		return -1;
	}
	server_pollfd[0].fd = init_fd;
	server_pollfd[0].events = POLLIN;
	server_pollfd[0].revents = 0;

	return 0;
}

int poll_add(int fd)
{
	int            max_pollfd = 0;
	struct pollfd *my_pollfd = NULL;

	max_pollfd = server_max_pollfd + 1;
	my_pollfd = server_pollfd;
	my_pollfd = realloc(my_pollfd, sizeof(struct pollfd) * max_pollfd);
	if(my_pollfd == NULL) {
		fprintf(stderr, "poll_add : out of memory\n");
		return -1;
	}

	my_pollfd[max_pollfd-1].fd = fd;
	my_pollfd[max_pollfd-1].events = POLLIN;
	my_pollfd[max_pollfd-1].revents = 0;
	server_max_pollfd = max_pollfd;
	server_pollfd = my_pollfd;
}

void poll_remove(int index)
{
	int i;

	for(i = index+1; i < server_max_pollfd; ++i) {
		server_pollfd[i-1] = server_pollfd[i];
	}
	memset(&server_pollfd[server_max_pollfd-1], 0, sizeof(struct pollfd));
	server_max_pollfd--;
}

void server_exit()
{
	free(server_pollfd);
	server_pollfd = NULL;
	server_max_pollfd = 0;
}

void server_process(struct pollfd *fds, int num)
{
	int i = 0;

	for(i = 0; i < server_max_pollfd; ++i) {
		if(fds[i].revents == 0) {
			continue;
		}
		if(fds[i].fd == sock_fd) {
			if(fds[i].revents & POLLIN) {
				int data_fd;
				struct sockaddr_in clnt;
				int clnt_len = sizeof(clnt);
				memset(&clnt, 0, sizeof(clnt));
				if((data_fd = accept(sock_fd, (struct sockaddr*)&clnt, &clnt_len)) < 0) {
					perror("accept");
				}
				char clnt_addr[16] = "";
				inet_ntop(AF_INET, &clnt.sin_addr, clnt_addr, sizeof(clnt_addr));
				printf("[%s] connected\n", clnt_addr);
				poll_add(data_fd);
			}
			if(fds[i].revents & POLLERR) {
				printf("error occured\n");
			}
			if(fds[i].revents & POLLNVAL) {
				printf("invalid request\n");
			}
		}
		else {
			if(fds[i].revents & POLLIN) {
				char clnt_addr[16] = "";
				struct sockaddr_in clnt;
				int clnt_len = sizeof(clnt);
				if(getpeername(fds[i].fd, (struct sockaddr*)&clnt, &clnt_len) < 0) {
					perror("getpeername");
				}
				inet_ntop(AF_INET, &clnt.sin_addr, clnt_addr, sizeof(clnt_addr));
				int recv_data = 0;
				int recv_cnt = 0;
				recv_cnt = recv(fds[i].fd, &recv_data, sizeof(recv_data), 0);
				if(recv_cnt > 0) {
					printf("receive [%d] from [%s]\n", recv_data, clnt_addr);
				}
				else if(recv_cnt == 0) {
					printf("[%s] disconnected\n\n", clnt_addr);
					close(fds[i].fd);
					poll_remove(i);
				}
				else if(recv_cnt == -1) {
					perror("recv");
				}
			}
			if(fds[i].revents & POLLOUT) {
				printf("ready to write data\n");
			}
			if(fds[i].revents & POLLERR) {
				printf("error occured\n");
			}
			if(fds[i].revents & POLLNVAL) {
				printf("invalid request\n");
			}
			if(fds[i].revents & POLLHUP) {
				printf("pollhup\n");
			}
			if(fds[i].revents & POLLRDHUP) {
				printf("pollrdhup\n");
			}
		}
	}
}

void server_run()
{
	int            i;
	int            last_max_pollfd = 0;
	struct pollfd *my_pollfd = NULL;

	for( ; ; ) {
		int max_pollfd = server_max_pollfd;
		if(max_pollfd == 0 && server_pollfd == NULL) {
			break;
		}

		if(last_max_pollfd != max_pollfd) {
			struct pollfd *new_pollfd = realloc(my_pollfd, sizeof(struct pollfd) * max_pollfd);
			if(new_pollfd == NULL) {
				fprintf(stderr, "server_run : out of memory\n");
				break;
			}

			my_pollfd = new_pollfd;
			last_max_pollfd = max_pollfd;
		}

		for(i = 0; i < max_pollfd; ++i) {
			my_pollfd[i].fd = server_pollfd[i].fd;
			my_pollfd[i].events = server_pollfd[i].events;
			my_pollfd[i].revents = 0;
		}

		switch(i = poll(my_pollfd, max_pollfd, -1)) {
		case -1:
			if(errno = EINTR) {
				continue;
			}
			fprintf(stderr, "server_run : poll failed\n");
			break;
		case 0:
			continue;
		default:
			server_process(my_pollfd, i);
			continue;
		}

		free(my_pollfd);
	}
}

void server_quit(int signo)
{
	printf("server is shuting down\n");
	server_exit();
	exit(0);
}

int main(int argc, char const *argv[])
{
	struct sockaddr_in server_addr;
	struct sigaction          act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	if(sigaction(SIGINT, &act, NULL) < 0) {
		perror("sigaction");
	}

	sigemptyset(&act.sa_mask);
	act.sa_handler = server_quit;
	if(sigaction(SIGQUIT, &act, NULL) < 0) {
		perror("sigaction");
	}

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9003);
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	if(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(listen(sock_fd, 0) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("server is listening...\n");

	server_init(sock_fd);
	server_run();

	return 0;
}