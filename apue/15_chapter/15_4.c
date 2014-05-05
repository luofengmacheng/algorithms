/*
 * author:	luo feng
 * date:	2014/4/29
 * source:	APUE
 * title:	15.3 popen & pclose
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 1024

#define PAGER "${PAGER:-more}"

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if(argc != 2) {
		fprintf(stderr, "usage : ./a.out <pathname>\n");
		exit(EXIT_FAILURE);
	}

	if((fpin = popen(argv[1], "r")) == NULL) {
		perror("popen");
		exit(EXIT_FAILURE);
	}

	if((fpout = popen(PAGER, "w")) == NULL) {
		perror("popen");
		exit(EXIT_FAILURE);
	}

	while(fgets(line, MAXLINE, fpin) != NULL) {
		if(fputs(line, fpout) == EOF) {
			fprintf(stderr, "fputs error to pipe\n");
		}
	}

	if(ferror(fpin)) {
		perror("fgets");
		exit(EXIT_FAILURE);
	}
	if(pclose(fpout) == -1) {
		perror("pclose error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}