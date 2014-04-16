/*
 * author:	luo feng
 * date:	2014/4/15
 * source:	APUE
 * title:	recursive mutex
 * language:	C
 *              |
 *              |
 *          mutex_lock
 *              |
 *              |
 *           timeout ---->设置需要等待的时间，填充to_info
 *              |                      |
 *              |         makethread创建线程，在线程中执行timeout_helper函数(也就是等待一段时间后执行timeout中的func函数)
 *              |                      |
 *              |<----------------------
 *              |
 *              |
 *         mutex_unlock
 *              |
 * 因此，这里的问题是：主线程中已经获得了mutex，还没有释放，然后在retry中又要获取mutex，如果主线程还没有释放，
 * 而timeout中就运行到了(*func)(arg)时，就会发生死锁。其实，这里和前面的情况有点类似，就是先获得了互斥量，然后又要获得互斥量，然后就造成了死锁。
 */

#include <pthread.h>
#include <time.h>
#include <sys/time.h>

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

struct to_info {
	void (*to_fn)(void *); /* function */
	void *to_arg; /* argument */
	struct timespec to_wait; /* time to wait */
};

#define SECTONSEC 1000000000
#define USECTONSEC 1000

// suspend to_wait, then call to_fn(to_arg)
void *timeout_helper(void *arg)
{
	struct to_info *tip;

	tip = (struct to_info *)arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);
	return 0;
}

// when要设置成未来的某个时间
void timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
	struct timespec now;
	struct timeval tv;
	struct to_info *tip;
	int err;

	gettimeofday(&tv, NULL); // get current time
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;
	if((when->tv_sec > now.tv_sec) ||
		(when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
		tip = malloc(sizeof(struct to_info));
	    if(tip != NULL) {
	    	tip->to_fn = func;
	    	tip->to_arg = arg;
	    	tip->to_wait.tv_sec = when->tv_sec - now.tv_nsec;
	    	if(when->tv_nsec >= now.tv_nsec) {
	    		tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
	    	}
	    	else {
	    		tip->to_wait.tv_sec--;
	    		tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
	    	}
	    	err = makethread(timeout_helper, (void *)tip);
	    	if(err == 0) {
	    		return;
	    	}
	    }
	}
	(*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void retry(void *arg)
{
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
	int err, condition, arg;
	struct timespec when;

	if((err = pthread_mutexatrr_init(&attr)) != 0) {
		printf("pthread_mutexattr_init failed\n");
	}
	if((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0) {
		printf("can't set recursive type\n");
	}
	if((err = pthread_mutex_init(&mutex, &attr)) != 0) {
		printf("can't create recursive mutex\n");
	}

	pthread_mutex_lock(&mutex);

	if(condition) {
		timout(&when, retry, (void *)arg);
	}

	pthread_mutex_unlock(&mutex);

	pthread_mutex_destroy(&mutex);
	pthread_mutexattr_destroy(&attr);

	return 0;
}
