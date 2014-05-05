/*
 * author:	luo feng
 * date:	2014/5/5
 * source:	APUE
 * title:	15.3 popen
 * language:	C
 */

#include <stdio.h>
#include <sys/wait.h>

#define MAXLINE 64

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	FILE *fpin;

	if((fpin = popen("./my", "r")) == NULL) {
		fprintf(stderr, "popen error\n");
	}

	for(;;) {
		fputs("prompt> ", stdout);
		fflush(stdout);
		if(fgets(line, MAXLINE, fpin) == NULL) {
			break;
		}
		if(fputs(line, stdout) == EOF) {
			fprintf(stderr, "fputs error to pipe\n");
			break;
		}
	}

	if(pclose(fpin) == -1) {
		fprintf(stderr, "pclose error\n");
	}
	putchar('\n');

	return 0;
}