/*
 * author:	luo feng
 * date:	2014/4/17
 * source:	APUE
 * title:	12.8 thread and signal
 * language:	C
 * 在主线程中利用pthread_sigmask()修改信号屏蔽字，阻塞SIGINT和SIGQUIT，然后创建线程，等待quitflag变量的改变。
 * 在thr_fn线程中，首先调用sigwait()等待信号的递送，由于sigwait会解除信号的阻塞
 * 因此，此时如果有未决的信号，就会进行信号的处理。
 * 采用pthread_sigmask()修改屏蔽字，创建的子线程会继承主线程的信号屏蔽字。
 * 为了使sigwait()能够捕获到信号，在调用sigwait()之前必须阻塞它等待的信号，
 * 然后使用sigwait()等待信号时，sigwait()会自动修改信号集的阻塞状态，只会接收之前设置的阻塞的信号。
 * sigwait()在返回前将回复线程的信号屏蔽字。
 * sigwait()的行为：对信号屏蔽字取反--->等待信号的递送--->接收到信号--->对信号屏蔽字取反
 * pthread_sigmask()：类似于sigprocmask()，不过它是针对线程的，而sigprocmask()是针对进程的，
 * pthread_sigmask()用于设置线程的信号屏蔽字，可以屏蔽某些信号，不让某些信号打断线程的执行。
 * sigwait()：等待信号，类似于sigsuspend()，用于休眠等待信号的递送。
 * pthread_kill()：发送信号，类似于kill()，用于给某个线程发送信号。如果信号的默认动作是终止该进程，那么把信号传递给某个线程仍然会杀掉整个进程。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
	int err, signo;

	for(;;) {
		err = sigwait(&mask, &signo);
		if(err != 0) {
			printf("sigwait error\n");
		}
		switch(signo) {
			case SIGINT:
			    printf("interrupt\n");
			    break;
			case SIGQUIT:
			    pthread_mutex_lock(&lock);
			    quitflag = 1;
			    pthread_mutex_unlock(&lock);
			    pthread_cond_signal(&wait);
			    return 0;
			default:
			    printf("unexpected signal %d\n", signo);
			    exit(1);
		}
	}
}

int main(int argc, char const *argv[])
{
	int err;
	sigset_t oldmask;
	pthread_t tid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	if((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0) {
		printf("SIG_BLOCK error\n");
	}
	if((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0) {
		printf("can't create thread\n");
	}

	pthread_mutex_lock(&lock);
	while(quitflag == 0) {
		pthread_cond_wait(&wait, &lock);
	}
	pthread_mutex_unlock(&lock);

	quitflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		printf("SIG_SETMASK error\n");
	}

	return 0;
}
