/* test_threadpool.c */
#include <stdio.h>
#include "threadpool.h"

void *routine(void *arg)
{
	printf("%d\n", (int)arg);
	return NULL;
}

int main(int argc, char const *argv[])
{
	threadpool_t *tp = threadpool_create();

	int i = 0;
	while(i < 10) {
		threadpool_insert_work(tp, routine, (void*)i);
		++i;
	}

	threadpool_destroy(tp);

	return 0;
}
