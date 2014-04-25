#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct foo {
	int a,  b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s\n", s);
	printf("structure at 0x%x\n", (unsigned)fp);
	printf("foo.a = %d\n", fp->a);
	printf("foo.b = %d\n", fp->b);
	printf("foo.c = %d\n", fp->c);
	printf("foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo f = {1, 2, 3, 4};
	printfoo("thread 1 : \n", &f);
	pthread_exit((void*)&f);
}

void *thr_fn2(void *arg)
{
	pthread_t tid;
	tid = pthread_self();
	printf("thread 2 : ID is %u\n", (unsigned int)tid);
	pthread_exit((void*)0);
}

int main()
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0) {
		printf("can't create thread 1\n");
	}

	err = pthread_join(tid1, (void*)&fp);
	if(err != 0) {
		printf("can't join with thread 1\n");
	}

	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0) {
		printf("can't create thread 2\n");
	}

	sleep(1);
	printfoo("parent:\n", fp);

	exit(0);
}

/*
 * 首先创建一个线程，在这个线程中分配一个局部结构体并将它作为返回值返回，然后在主线程中等待这个线程结束，获取线程的返回值，然后主线程休眠1s。
 * 接着创建第二个线程，然后打印之前获取线程的结束状态，那么，此时这个指针指向的就是在之前已经结束的线程的局部空间，因此，打印的就是垃圾信息。
 */
