/*
 * author:	luofeng
 * date:	2014/6/6
 * source:	APUE
 * title:	
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	char c;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork failed\n");
	}
	else if(pid > 0) {
		exit(0);
	}
	else {
		pid_t sid = setsid();
		/* pid:进程ID，pgid:进程组ID，sid:会话首进程的进程ID */
		printf("pid = %d, pgid = %d, sid = %d\n", getpid(), getpgid(getpid()), sid);
		if(read(STDOUT_FILENO, &c, 1) == -1) {
			fprintf(stderr, "%s\n", strerror(errno));
		}
		exit(0);
	}

	return 0;
}
