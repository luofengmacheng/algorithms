/*
 * author:	luo feng
 * date:	2014/4/14
 * source:	APUE 11.6
 * title:	read write lock
 * info:	读写锁维护一个队列中的作业的访问，当需要对队列进行写(也就是修改)时，就需要写模式的读写锁，当需要对队列进行读时，就需要读模式的读写锁，因此，可以允许多个线程对队列进行读(find)，只能允许一个线程对队列进行写(insert, remove, append)。
 */

#include <stdlib.h>
#include <pthread.h>

struct job {
	struct job *j_next;
	struct job *j_prev;
	pthread_t j_id;
};

struct queue {
	struct job *q_head;
	struct job *q_tail;
	pthread_rwlock_t q_lock;
};

int queue_init(struct queue *qp)
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
	jp->j_next = qp->q_head;
	jp->j_prev = NULL;
	if(qp->q_head != NULL) {
		qp->q_head->j_prev = jp;
	}
	else {
		qp->q_tail = jp;
	}
	qp->q_head = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}

void job_append(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	jp->j_next = NULL;
	jp->j_prev = qp->q_tail;
	if(qp->q_tail != NULL) {
		qp->q_tail->j_next = jp;
	}
	else {
		qp->q_head = jp;
	}
	qp->q_tail = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}

void job_remove(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	if(jp == qp->q_head) {
		qp->q_head = jp->j_next;
		if(qp->q_tail == jp) {
			qp->q_tail = NULL;
		}
	}
	else if(jp == qp->q_tail) {
		qp->q_tail = jp->j_prev;
		if(qp->q_head == jp) {
			qp->q_head = NULL;
		}
	}
	else {
		jp->j_prev->j_next = jp->j_next;
		jp->j_next->j_prev = jp->j_prev;
	}
	pthread_rwlock_unlock(&qp->q_lock);
}

struct job *job_find(struct queue *qp, pthread_t id)
{
	struct job *jp;
	if(pthread_rwlock_rdlock(&qp->q_lock) != 0) {
		return NULL;
	}

	for(jp = qp->q_head; jp != NULL; jp = jp->j_next) {
		if(pthread_equal(jp->j_id, id)) {
			break;
		}
	}

	pthread_rwlock_unlock(&qp->q_lock);
	return jp;
}
