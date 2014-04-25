/*
 * 为了保护多个线程对foo结构变量的安全访问，在修改结构体中的数据时需要对结构体加锁，访问完成后解锁
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

 #define NHASH 29
 #define HASH(fp) (((unsigned long)fp) % NHASH)
 struct foo *fh[NHASH];

 pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int f_count;
	pthread_mutex_t f_lock;
	struct foo *f_next;
	int f_id;
};

struct foo *foo_alloc()
{
	struct foo *fp;
	int idx;

	if((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return NULL;
		}
		idx = HASH(fp);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = fp; // fh[idx] = fp->f_next; (on APUE)
		// 在解锁hashlock之前，对foo其它字段加锁。如果不这样做，此时其它线程就可以访问这个新的结构体。
		// 因此，这里的作用是在未完成初始化之前，禁止其它线程访问这个新的结构体。
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
		/* continue initialization */
		pthread_mutex_unlock(&fp->f_lock);
	}
	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

struct foo *foo_find(int id)
{
	struct foo *fp;
	int idx;

	idx = NHASH(fp);
	pthread_mutex_lock(&hashlock);
	for(fp = fh[idx]; fp != NULL; fp = fp->f_next) {
		if(fp->f_id == id) {
			foo_hold(fp);
			break;
		}
	}
	pthread_mutex_lock(&hashlock);
	return (fp);
}

void foo_rele(struct foo *fp)
{
	struct foo *tfp;
	int idx;

	pthread_mutex_lock(&fp->f_lock);
	if(fp->f_count == 1) {
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		if(fp->f_count != 1) {
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		idx = HASH(fp);
		tfp = fh[idx];
		if(tfp == fp) {
			fh[idx] = fp->f_next;
		}
		else {
			while(tfp->f_next != fp) {
				tfp = tfp->f_next;
			}
			tfp->f_next = fp->f_next;
		}
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else {
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}
