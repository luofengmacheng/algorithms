/*
 * author:	luo feng
 * date:	2014/5/5
 * source:	APUE
 * title:	15.3 popen
 * language:	C
 */

#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
	int c;

	while((c = getchar()) != EOF) {
		if(isupper(c)) {
			c = tolower(c);
		}

		if(putchar(c) == EOF) {
			fprintf(stderr, "output error\n");
		}

		if(c == '\n') {
			fflush(stdout);
		}
	}

	return 0;
}