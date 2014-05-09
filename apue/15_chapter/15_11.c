/*
 * author:	luo feng
 * date:	2014/5/7
 * source:	APUE
 * title:	15.9 shared memory
 * language:	C
 */

#include <stdio.h>
#include <malloc.h>
#include <sys/shm.h>

#define ARRAY_SIZE 4000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600

char array[ARRAY_SIZE];

int main(int argc, char const *argv[])
{
	int shmid;
	char *ptr, *shmptr;

	printf("array[] from %lx to %lx\n", (unsigned long)&array[0],
		(unsigned long)&array[ARRAY_SIZE]);
	printf("stack around %lx\n", (unsigned long)&shmid);

	if((ptr = malloc(MALLOC_SIZE)) == NULL) {
		printf("malloc error\n");
	}
	printf("malloced from %lx to %lx\n", (unsigned long)ptr,
		(unsigned long)ptr+MALLOC_SIZE);

	if((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
		printf("shmget error\n");
	}
	if((shmptr = shmat(shmid, 0, 0)) == (void *)-1) {
		printf("shmat error\n");
	}
	printf("shared memory attached from %lx to %lx\n", 
		(unsigned long)shmptr, (unsigned long)shmptr+SHM_SIZE);
	if(shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("shmctl error\n");
	}

	return 0;
}