#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
	int ret;
	int fd_size, i;
	fd_set fset;
	struct timeval interval;
	char buf[5];
	int nbytes;

	FD_ZERO(&fset);
	FD_SET(STDIN_FILENO, &fset);
	fd_size = 1;
	interval.tv_sec = 5;
	interval.tv_usec = 0;

	ret = select(fd_size, &fset, NULL, NULL, &interval);
	if(ret > 0) {
		if(FD_ISSET(STDIN_FILENO, &fset)) {
			if(nbytes = read(STDIN_FILENO, buf, 5)) {
				printf("read %d bytes\n", nbytes);
			}
		}
	}
	else if(ret == 0) {
		printf("no fd is ready\n");
	}
	else if(ret == -1) {
		printf("something is error\n");
	}

	return 0;
}