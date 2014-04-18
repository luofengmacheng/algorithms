/*
 * author:	luo feng
 * date:	2014/4/17
 * source:	APUE
 * title:	12.9 thread and fork
 * language:	C
 * 下面部分语言翻译自http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_atfork.html
 * 在多线程程序中调用fork()至少有两个严重的问题。一个是互斥量保护的状态，考虑一种情况，当一个线程用互斥量加锁后，而另外一个线程调用fork()就会对互斥量产生不一致。在子线程中，互斥量处于锁定状态，由于它是被一个不存在的线程锁定的，因此该互斥量永远不会被释放。子进程重新初始化互斥量也不行，因此这种方法没有解决子进程中不一致的状态。
 * 通常建议在调用fork()后，子进程立即调用exec()，exec()会重置所有的状态，与此同时，只允许很小的一部分异步信号安全函数调用。
 * 但是，这种解决方案并没有解决多线程的需求。应用程序并不知道多线程库正在使用中，他们认为可以自由地在fork()和exec()之间调用任何库例程。但事实上，他们只使用了单线程，因此，需要遵循线程库的新的限制。
 * 另一方面，多线程库确实需要一种保护它在调用fork()时的内部状态，以防子进程之后的重入。特别是在多线程I/O库中这种问题极其重要，这通常是因为在fork()和exec()之间调用了多线程I/O库中的例程影响了I/O的重定向。解决方案可能是在调用fork()时对互斥量加锁，或者在fork()调用完成之后在子进程中重置状态。
 * pthread_atfork()提供了一种保护线程不受其它程序调用fork()的影响，它为多线程应用程序提供了一种标准的保护线程不受库例程或者程序本身调用fork()的影响。
 * pthread_atfork()的使用方法是prepare获取所有的互斥量锁，另外两个释放它们。
 * 比如，一个应用程序可以提供一个prepare函数来获取库保留的必要的互斥量，提供child和parent函数用于释放这些互斥量，因此，必须保证child能够获得库的状态的一致的快照。有时，一些库可能只提供一个child例程，它会重新初始化库中的互斥量和相关的状态。
 * 当调用fork()时，只有调用线程会拷贝到子进程中。在调用fork()时，同步变量会在子进程中保留它们在父进程中的状态。因此，可能会出现这种情况，子进程的互斥量被不存在的线程锁住了，任何相关的状态变得不一致了。父进程可以通过调用pthread_atfork()来显示地获取和释放对于子进程重要的锁。另外，任何关键的线程需要重新创建并获得合适的状态。
 */

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare()
{
	printf("preparing locks\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}

void parent()
{
	printf("parent unlocking locks\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void child()
{
	printf("child unlocking locks\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void *thr_fn(void *arg)
{
	printf("thread started\n");
	pause();
	return 0;
}

int main(int argc, char const *argv[])
{
	int err;
	pid_t pid;
	pthread_t tid;

	if((err = pthread_atfork(prepare, parent, child)) != 0) {
		printf("can't install fork handlers\n");
	}
	if((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0) {
		printf("can't create thread\n");
	}
	sleep(2);
	printf("parent about to fork\n");
	if((pid = fork()) < 0) {
		printf("fork failed\n");
	}
	else if(pid == 0) {
		printf("child returned from fork\n");
	}
	else {
		printf("parent returned from fork\n");
	}

	return 0;
}