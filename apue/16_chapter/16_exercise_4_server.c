/*
 * author:	luo feng
 * date:	2014/5/9
 * source:	APUE
 * title:	exercise 4(UDP server) of chapter 16
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	unsigned int cnt = 0;
	FILE *pf = NULL;
	struct sockaddr_in addr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* 此题要求得到下面的命令的结果，但是用popen有得到的是错误的结果，不知为何*/
	/* 不过这里的通信是正确的 */
	if((pf = popen("ps aux | wc -l", "r")) == NULL) {
		perror("popen");
		exit(EXIT_FAILURE);
	}

	fread((void*)&cnt, sizeof(cnt), 1, pf);
	printf("%d\n", cnt);

	if(pclose(pf) < 0) {
		perror("pclose");
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9003);
	inet_pton(AF_INET, "127.0.0.1", (void*)&(addr.sin_addr));
	if(sendto(sockfd, &cnt, sizeof(cnt), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0) {
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	if(close(sockfd) < 0) {
		perror("close socket");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
