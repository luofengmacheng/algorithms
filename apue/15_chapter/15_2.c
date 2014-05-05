/*
 * author:	luo feng
 * date:	2014/4/29
 * source:	APUE
 * title:	15.2 pipe
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define DEF_PAGER "/bin/more"

int main(int argc, char const *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char *pager, *argv0;
	char line[MAXLINE];
	FILE *fp;

	if(argc != 2) {
		perror("bad parameters");
		exit(EXIT_FAILURE);
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		perror("open file");
		exit(EXIT_FAILURE);
	}

	/* 创建管道 */
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

		/* 从文件中逐行读取数据，然后写到管道中 */
		while(fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if(write(fd[1], line, n) != n) {
				printf("write error to pipe\n");
			}
		}

		if(ferror(fp)) {
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		close(fd[1]);

		if(waitpid(pid, NULL, 0) < 0) {
			perror("waitpid error");
		}
		exit(EXIT_SUCCESS);
	}
	else {
		close(fd[1]);
		if(fd[0] != STDIN_FILENO) {
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
				perror("dup2 to stdin");
			}
			close(fd[0]);
		}

		if((pager = getenv("PAGER")) == NULL) {
			pager = DEF_PAGER;
		}
		if((argv0 = strrchr(pager, '/')) != NULL) {
			argv0++;
		}
		else {
			argv0 = pager;
		}

		if(excel(pager, argv0, (char*)0) < 0) {
			perror("excel");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
