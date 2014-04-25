/*
 * author:	luo feng
 * date:	2014/4/15
 * source:	APUE
 * title:	pthread_attr_*
 * info:	修改线程属性的函数，一般可以修改下面四种属性。
 *
 * detachstate:	线程分离属性。线程与进程类似，在结束后有些资源并不释放，而是等待其它线程获取它的结束状态，
 * 但是，如果对某个线程的状态并不关注时，就可以使线程分离，那么，在线程退出时，它所使用的资源都会被回收。
 * int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
 * int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
 * 其中，detachstate可以设置的值有：PTHREAD_CREATE_DETACHED和PTHREAD_CREATE_JOINABLE。
 *
 * stack:	线程栈属性。可以修改线程栈的大小和起始（或者结束，依赖于处理器）位置。
 * int pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr, size_t *stacksize);
 * int pthread_attr_setstack(const pthread_attr_t *attr, void *stackaddr, size_t *stacksize); 这里第一个参数是否应该去除const呢？
 *
 * stacksize:	线程栈大小属性。如果希望改变栈的默认大小，但是又不想自己处理线程栈的分配问题，就可以使用这个属性设置函数。
 * int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);
 * int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
 *
 * guardsize:	线程栈大小保护属性。当线程用完了栈之后，可以用它来控制可以扩展的内存的大小，从而防止溢出。默认大小为PAGESIZE个字节。
 * int pthread_attr_getguardsize(const pthread_attr_t *attr, size_t *guardsize);
 * int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
 *
 * concurrency:	线程并发度属性。该属性并没有在pthread_attr_t中表达。pthread_setconcurrency()用于提示系统，表明希望的并发度，结果依赖于实现。
 * int pthread_getconcurrency();
 * int pthread_setconcurrency(int level);
 */

#include <pthread.h>

int makethread(void *(*fn)(void *), void *arg)
{
	int err;
	pthread_t tid;
	pthread_attr_t attr;

	err = pthread_attr_init(&attr);
	if(err != 0) {
		return err;
	}
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(err == 0) {
		pthread_create(&tid, &attr, fn, arg);
	}
	pthread_attr_destroy(&attr);
	return err;
}

int main(int argc, char const *argv[])
{


	return 0;
}
