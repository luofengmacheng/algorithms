/*
 * author:	luo feng
 * date:	2014/4/16
 * source:	APUE
 * title:	重入
 * language:	C++
 * 这里实现了一个getenv函数的非可重入版本和可重入版本。用mutex来保护environ只能被一个getenv函数使用，其它使用getenv的函数都会被阻塞。
 */

#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>

static char envbuf[ARG_MAX];

extern char **environ;

char *getenv(const char *name)
{
	int i, len;

	len = strlen(name);
	for(i = 0; environ[i] != NULL; i++) {
		if((strncmp(name, environ[i], len) == 0) &&
			environ[i][len] == '=') {
			strcpy(envbuf, &environ[i][len+1]);
		    return envbuf;
		}
	}
	return NULL;
}

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init()
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
	int i, len, olen;

	pthread_once(&init_done, thread_init);
	len = strlen(name);
	pthread_mutex_lock(&env_mutex);
	for(i = 0; environ[i] != NULL; i++) {
		if((strncmp(name, environ[i], len) == 0) &&
			environ[i][len] == '=') {
			olen = strlen(&&environ[i][len+1]);
		    if(olen >= buflen) {
		    	pthread_mutex_unlock(&env_mutex);
		    	return ENOSPC;
		    }
		    strcpy(buf, &environ[i][len+1]);
		    pthread_mutex_unlock(&env_mutex);
		    return 0;
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return ENOENT;
}
