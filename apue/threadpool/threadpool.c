/* threadpool.c */
#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

/* 创建线程，分配线程池结构，初始化结构中的各个元素，创建默认个数的线程 */
threadpool_t* threadpool_create()
{
	threadpool_t *tp = (threadpool_t *)malloc(sizeof(threadpool_t));
	if(tp == NULL) {
		fprintf(stderr, "%s: malloc failed\n", __FUNCTION__);
		return tp;
	}

	tp->finish = 0;
	tp->cur_thread_num = 0;
	tp->workers = NULL;
	tp->first = NULL;
	tp->last = NULL;

	if(pthread_cond_init(&tp->queue_nonempty, NULL) != 0) {
		fprintf(stderr, "%s: pthread_cond_init failed\n", __FUNCTION__);
		free(tp);
		return NULL;
	}

	if(pthread_mutex_init(&tp->queue_lock, NULL) != 0) {
		fprintf(stderr, "%s: pthread_mutex_init failed\n", __FUNCTION__);
		free(tp);
		return NULL;
	}

	int cnt = THREADPOOL_DEF_THREADS;
	while(cnt--) {
		threadpool_create_worker(tp);
	}
	printf("create threadpool success\n");
	printf("contain %d threads\n", THREADPOOL_DEF_THREADS);

	return tp;
}

/* 往线程池中添加工作 */
int threadpool_insert_work(threadpool_t *tp, void* (*routine)(void *), void* arg)
{
	work_queue_t *wq = malloc(sizeof(work_queue_t));
	if(wq == NULL) {
		fprintf(stderr, "%s: malloc failed\n", __FUNCTION__);
		return -1;
	}

	wq->routine = routine;
	wq->arg = arg;
	wq->next = NULL;

	pthread_mutex_lock(&tp->queue_lock);
	if(tp->first == NULL && tp->last == NULL) {
		tp->first = wq;
		tp->last = wq;
	}
	else {
		tp->last->next = wq;
		tp->last = wq;
	}
	pthread_mutex_unlock(&tp->queue_lock);
	pthread_cond_signal(&tp->queue_nonempty);

	return 0;
}

/* 工作者线程的执行函数 */
void* thread_routine(void* arg)
{
	work_queue_t *wq = NULL;
	threadpool_t *tp = (threadpool_t *)arg;

	while(1) {
		pthread_testcancel();
		pthread_mutex_lock(&tp->queue_lock);
		while(tp->finish == 0 && tp->first == NULL) {
			pthread_cond_wait(&tp->queue_nonempty, &tp->queue_lock);
		}
		if(tp->finish && tp->first == NULL) {
			pthread_mutex_unlock(&tp->queue_lock);
			pthread_exit(NULL);
		}
		
		work_queue_t *wq = NULL;
		wq = tp->first;
		tp->first = wq->next;
		if(wq->next == NULL) {
			tp->last = NULL;
		}
		pthread_mutex_unlock(&tp->queue_lock);

		wq->routine(wq->arg);
		printf("current thread: %u\n", (unsigned int)pthread_self());
		free(wq);
	}
}

/* 创建工作者，并将工作者的线程ID记录到工作者队列中 */
int threadpool_create_worker(threadpool_t *tp)
{
	pthread_t tid;
	if(pthread_create(&tid, NULL, thread_routine, tp) != 0) {
		fprintf(stderr, "%s: pthread_create failed\n", __FUNCTION__);
		return -1;
	}

	worker_queue_t *worker = (worker_queue_t *)malloc(sizeof(worker_queue_t));
	if(worker == NULL) {
		fprintf(stderr, "%s: malloc failed\n", __FUNCTION__);
		return -1;
	}
	worker->id = tid;
	worker->next = NULL;

	worker->next = tp->workers;
	tp->workers = worker;
	tp->cur_thread_num++;
	printf("create worker %u\n", (unsigned int)tid);

	return 0;
}

/* 销毁工作者 */
int threadpool_destroy_worker(threadpool_t *tp)
{
	worker_queue_t *worker = NULL;
	if(tp->workers == NULL) {
		return -1;
	}
	worker = tp->workers;
	tp->workers = worker->next;
	tp->cur_thread_num--;

	pthread_t tid = worker->id;
	free(worker);
	int err;

	/*if((err = pthread_cancel(tid)) != 0) {
		fprintf(stderr, "%s: pthread_cancel failed, %d\n", __FUNCTION__, err);
		return -1;
	}*/

	if(pthread_join(tid, NULL) != 0) {
		fprintf(stderr, "%s: pthread_join failed\n", __FUNCTION__);
		return -1;
	}
	printf("destroy %u success\n", (unsigned int)tid);

	return 0;
}

/* 销毁线程池，等待所有线程结束 */
int threadpool_destroy(threadpool_t *tp)
{
	pthread_mutex_lock(&tp->queue_lock);
	tp->finish = 1;
	pthread_mutex_unlock(&tp->queue_lock);
	pthread_cond_broadcast(&tp->queue_nonempty);
	int cnt = tp->cur_thread_num;

	printf("ready to destroy %d worker\n", cnt);

	while(cnt--) {
		threadpool_destroy_worker(tp);
	}

	free(tp);

	return 0;
}
