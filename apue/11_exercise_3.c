/*
 * author:	luo feng
 * date:	2014/4/14
 * source:	APUE
 * title:	工作队列的实现
 * description:	这是一个多线程的例子。主线程获取任务，并将任务放到工作队列中，在主线程放置工作时会设置一个线程的编号，指定哪个线程处理该工作。线程在处理任务时，只能获取编号跟自己对应的工作。
 * master的工作：构造一个job对象，其中的data就是worker要处理的数据，然后将job对象插入到job_queue队列中。当所有的工作都处理完了以后，设置结束变量，然后等待所有的worker线程退出。
 * worker的工作：如果结束变量未设置，就在job_queue中查找该worker要处理的工作，如果找到了，就取出该job，然后进行处理。如果设置了结束变量，就退出。
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADS 100

int finish = 0; // 结束变量，用于通知worker线程，工作已经分发完毕
pthread_rwlock_t finish_lock = PTHREAD_RWLOCK_INITIALIZER; // 结束变量的读写锁

pthread_cond_t qready = PTHREAD_COND_INITIALIZER; // 队列是否为空的条件变量
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER; // 保护条件变量的互斥锁

struct job {
	struct job *j_prev;
	struct job *j_next;
	pthread_t j_id;

	int data;
};

struct job_queue {
	pthread_rwlock_t q_lock;
	struct job *q_head;
	struct job *q_tail;
};

int queue_init(struct job_queue *qp)
{
	int err;

	qp->q_head = NULL;
	qp->q_tail = NULL;
	err = pthread_rwlock_init(&qp->q_lock, NULL);
	if(err != 0) {
		return err;
	}

	return 0;
}

void job_insert(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	if(qp->q_tail == NULL) {
		q_head = jp;
	}
	else {
		q_tail->j_next = jp;
	}
	qp->q_tail = jp;
	pthread_rwlock_unlock(&qp->q_lock);
	if(qp->q_head == qp->q_tail) {
		pthread_mutex_lock(&qlock);
		pthread_cond_signal(&qready);
		pthread_mutex_unlock(&qlock);
	}
}

void job_remove(struct queue *qp, struct job *jp)
{
	
}

void worker(void *arg);
void master(void *arg);

int main(int argc, char const *argv[])
{
	//int nworkers;
	pthread_t master_id, worker_id;
	//pthread_t worker_id[MAXTHREADS];

	//nworkers = atoi(argv[1]);
	//if(nworkers > MAXTHREADS) {
	//	printf("too many worker threads\n");
	//	exit(0);
	//}
	pthread_create(&master_id, NULL, master, NULL);
	//int i = 0;
	//for(i = 0; i < nworkers; ++i) {
		//pthread_create(&worker_id[i], NULL, worker, NULL);
	pthread_create(&worker_id, NULL, worker, NULL);
	//}
	pthread_join(master_id, NULL);
	//for(i = 0; i < nworkers; ++i) {
		//pthread_join(worker_id[i], NULL);
	//}

	return 0;
}

void worker(void *arg)
{

}

void master(void *arg)
{

}
