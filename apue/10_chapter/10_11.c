/*
 * author:	luo feng
 * date:	2014/6/11
 * source:	APUE
 * title:	10.13 10-11
 * language:	C
 */

#include <stdio.h>
#include <signal.h>

/*
 * 首先设置SIGQUIT的信号处理函数，然后阻塞SIGQUIT。接着休眠5秒钟。
 * 如果在这5秒钟之内产生了SIGQUIT信号，该信号就会被阻塞，并不递送至进程。
 * 5秒钟之后，检查阻塞的信号中是否有SIGQUIT。
 * 然后调用sigprocmask对信号屏蔽字进行复位，因此，SIGQUIT变成了非阻塞的，
 * 在sigporcmask返回之前，如果有未决信号，该信号就会被递送至接收进程，
 * 即在sigporcmask返回之前，会将之前在sleep(5)过程中的产生的未决信号递送至进程，
 * 然后就会调用SIGQUIT的信号处理程序。
 */

static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if(signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "cannot reset SIGQUIT\n");
	}
}

int main(int argc, char const *argv[])
{
	sigset_t newmask, oldmask, pendmask;

	/* 设置SIGQUIT的捕获函数 */
	if(signal(SIGQUIT, sig_quit) == SIG_ERR) {
		fprintf(stderr, "cannot catch SIGQUIT\n");
	}

	/* 阻塞SIGQUIT */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		fprintf(stderr, "SIG_BLOCK error\n");
	}

	sleep(5);


	if(sigpending(&pendmask) < 0) {
		fprintf(stderr, "sigpending error\n");
	}
	if(sigismember(&pendmask, SIGQUIT)) {
		printf("SIGQUIT pending\n");
	}

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		fprintf(stderr, "SIG_SETMASK error\n");
	}
	printf("SIGQUIT unblocked\n");

	sleep(5);

	return 0;
}
