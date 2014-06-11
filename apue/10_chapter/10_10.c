/*
 * author:	luo feng
 * date:	2014/6/11
 * source:	APUE
 * title:	10.12 10-10
 * language:	C
 */

#include <signal.h>
#include <errno.h>

void
pr_mask(const char *str)
{
	sigset_t sigset;
	int      errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0) {
		fprintf(stderr, "sigprocmask error\n");
	}

	printf("%s\n", str);

	if(sigismember(&sigset, SIGINT)) {
		printf("SIGINT\n");
	}
	if(sigismember(&sigset, SIGQUIT)) {
		printf("SIGQUIT\n");
	}
	if(sigismember(&sigset, SIGUSR1)) {
		printf("SIGUSR1\n");
	}
	if(sigismember(&sigset, SIGALRM)) {
		printf("SIGALRM\n");
	}

	printf("\n");
	errno = errno_save;
}