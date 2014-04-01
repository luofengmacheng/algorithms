#include <stdio.h>
#include <unistd.h>

int glob = 6;
char buf[] = "a write to stdout";

int main()
{
	int var;
	pid_t pid;

	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
		printf("write error\n");
	}
	printf("before fork\n");

	if((pid = fork()) < 0) {
		printf("fork error\n");
	}
	else if(pid == 0) {
		glob++;
		var++;
		sleep(2);
	}
	else {
		//sleep(2);
	}

	printf("ppid = %d, pid = %d, glob = %d, var = %d\n", getppid(), getpid(), glob, var);
	printf("ppid = %d, pid = %d, g_a = %p, v_a = %p\n", getppid(), getpid(), &glob, &var);

	return 0;
}