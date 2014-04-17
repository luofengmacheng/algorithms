/*
 * author:	luo feng
 * date:	2014/4/16
 * source:	APUE
 * title:	线程私有数据
 * language:	C
 * 对于线程私有数据需要了解的是：
 * 1 使用场合：有时线程需要拥有自己的数据，特别是对于不可重入函数来说，它们有时会使用全局变量，然而，当多个线程同时访问全局变量时会出现问题，因此，有必要提供一种保存变量的一个副本，使得一个线程的改变不影响另一个线程。
 * 2 如何使用： int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *)); 创建一个键
 *             int pthread_key_delete(pthread_key_t *key); 删除一个键
 *             void *pthread_getspecific(pthread_key_t key); 获得这个键所对应的数据
 *             int pthread_setspecific(pthread_key_t key, const void *value); 将键和用malloc分配的内存关联
 *             int pthread_once(pthread_once_t *initflag, void (*initfn)(void)); 在多线程只执行一次的机制
 *             键只创建一次，因此会调用pthread_once用于创建键，但是，线程可以将键与不同的内存空间绑定，因此，通过该键就只能访问当时绑定的内存空间。
 *             当线程第一次调用pthread_getspecific()获取本线程的私有数据时，还没有跟内存空间关联，返回NULL，
 *             于是，需要调用malloc分配内存空间，然后将分配的内存空间与键绑定。
 */

#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PHTREAD_MUTEX_INITIALLIZER;

extern char **environ;

static void thread_init()
{
	pthread_key_create(&key, free);
}

char *getenv(const char *name)
{
	int i, len;
	char *envbuf;

	pthread_once(&init_done, thread_init); /* 防止多个线程进行初始化时造成竞争，使用pthread_once可以保证该thread_init只调用一次 */
	/* 首先加锁，然后试图获得线程私有数据，如果没有获得，说明还没有创建线程私有数据，因此，调用malloc为私有数据分配内存空间，*/
	/* 如果分配失败就释放锁，如果分配成功，就将线程私有数据与分配的内存关联，然后查询环境变量表，*/
	/* 将需要的数据拷贝到线程私有数据内存中，随后释放锁，返回私有数据 */
	pthread_mutex_lock(&env_mutex);
	envbuf = (char *)pthread_getspecific(key);
	if(envbuf == NULL) {
		envbuf = malloc(ARG_MAX);
		if(envbuf == NULL) {
			pthread_mutex_unlock(&env_mutex);
			return NULL;
		}
		pthread_setspecific(key, envbuf);
	}
	len = strlen(name);
	for(i = 0; environ[i] != NULL; i++) {
		if((strncmp(name, environ[i], len) == 0) &&
			environ[i][len] == '=') {
		    strcpy(envbuf, &environ[i][len+1]);
		    pthread_mutex_unlock(&env_mutex);
		    return envbuf;
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return NULL;
}
