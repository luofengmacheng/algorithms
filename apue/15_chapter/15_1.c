/*
 * author:	luo feng
 * date:	2014/4/29
 * source:	APUE
 * title:	pipe
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char const *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(pipe(fd) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if((pid = fork()) < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0) {
		close(fd[0]);
		write(fd[1], "hello world\n", 12);
	}
	else {
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}

	exit(EXIT_SUCCESS);
}