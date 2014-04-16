#include <stdio.h>
#include <stdlib.h>

void test()
{
	pid_t pid;

	printf("before vfork");
	if((pid = vfork()) < 0) {
		printf("vfork error\n");
	}
	else if(pid == 0) {
		printf("child\n");
		fclose(stdout);
		exit(0);
	}
	printf("parent\n");
	exit(0);
}

void zom()
{
	pid_t pid;

	if((pid = fork()) < 0) {
		printf("fork error\n");
	}
}

int main()
{
	zom();

	return 0;
}