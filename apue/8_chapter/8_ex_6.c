#include <stdio.h>
#include <stdlib.h>

#define PSCMD "ps -o pid,ppid,state,tty,command"

int main()
{
	pid_t pid;

	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		return EXIT_FAILURE;
	}
	else if(pid == 0) {
		exit(0);
	}

	sleep(4);
	system(PSCMD);

	exit(0);
}
