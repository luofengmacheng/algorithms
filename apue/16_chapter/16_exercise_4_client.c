/*
 * author:	luo feng
 * date:	2014/5/9
 * source:	APUE
 * title:	exercise 4(UDP client) of chapter 16
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	unsigned int cnt = 0;
	struct sockaddr_in addr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(9003);
	inet_pton(AF_INET, "127.0.0.1", (void*)&(addr.sin_addr));
	if(bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(recvfrom(sockfd, &cnt, sizeof(cnt), 0, NULL, NULL) < 0) {
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", cnt);

	if(close(sockfd) < 0) {
		perror("close socket");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}