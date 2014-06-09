/*
 * author:	luo feng
 * date:	2014/6/9
 * source:	APUE
 * title:	10.3 10-1
 * language:	C
 */

#include <stdio.h>
#include <signal.h>

static void
sig_usr(int signo)
{
	if(signo == SIGUSR1) {
		printf("recevied SIGUSR1  %d\n", signo);
	}
	else if(signo == SIGUSR2) {
		printf("recevied SIGUSR2 %d\n", signo);
	}
	else if(signo == SIGCLD) {
		printf("recevied SIGTERM %d\n", signo);
	}
	else {
		printf("recevied signal %d\n", signo);
	}
}

int main(int argc, char const *argv[])
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR) {
		fprintf(stderr, "can't catch SIGUSR1 %d\n", __LINE__);
	}
	if(signal(SIGUSR2, sig_usr) == SIG_ERR) {
		fprintf(stderr, "can't catch SIGUSR2 %d\n", __LINE__);
	}
	if(signal(SIGCLD, sig_usr) == SIG_ERR) {
		fprintf(stderr, "can't catch SIGTERM %d\n", __LINE__);
	}
	for( ; ; ) {
		pause();
	}

	return 0;
}