/* threadpool.h */
#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <pthread.h>

#define	THREADPOOL_MAX_THREADS	8 /* 最大线程数 */
#define	THREADPOOL_MIN_THREADS	1 /* 最小线程数 */
#define	THREADPOOL_DEF_THREADS	4 /* 默认线程数 */

struct work_queue_s {
	void* (*routine)(void *); /* 工作例程 */
	void *arg; /* 工作例程参数 */
	struct work_queue_s *next;
};

typedef struct work_queue_s work_queue_t; /* 工作队列 */

struct worker_queue_s {
	pthread_t id; /* 线程ID */
	struct worker_queue_s *next;
};

typedef struct worker_queue_s worker_queue_t; /* 工作者队列 */

struct threadpool_s {
	int finish; /* 是否结束 */
	int cur_thread_num; /* 当前线程数 */
	worker_queue_t *workers; /* 工作者队列 */
	work_queue_t *first; /* 工作队列首指针 */
	work_queue_t *last; /* 工作队列尾指针 */
	pthread_cond_t queue_nonempty; /* 工作队列是否为空的条件变量 */
	pthread_mutex_t queue_lock; /* 工作队列锁 */
};

typedef struct threadpool_s threadpool_t; /* 线程池结构 */

/* 创建线程池 */
threadpool_t* threadpool_create();

/* 向线程池中添加工作 */
int threadpool_insert_work(threadpool_t*, void* (*)(void *), void*);

/* 创建工作者 */
int threadpool_create_worker(threadpool_t*);

/* 销毁工作者 */
int threadpool_destroy_worker(threadpool_t*);

/* 销毁线程池 */
int threadpool_destroy(threadpool_t*);

#endif
