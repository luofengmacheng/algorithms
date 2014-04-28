/*
 * author:	luo feng
 * date:	2014/4/28
 * source:	APUE
 * title:	exercise 14.8
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void set_fl(int fd, int flags)
{
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0) {
		perror("fcntl F_GETFL");
	}

	val |= flags;

	if(fcntl(fd, F_SETFL, val) < 0) {
		perror("fcntl F_SETFL");
	}
}

int main(int argc, char const *argv[])
{
	int i, n;
	int fd[2];

	if(pipe(fd) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	set_fl(fd[1], O_NONBLOCK);

	for(n = 0; ; n++) {
		if((i = write(fd[1], "a", 1)) != 1) {
			printf("write ret %d\n", i);
			break;
		}
	}
	printf("pipe capacity = %d\n", n);

	return 0;
}