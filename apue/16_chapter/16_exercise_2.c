/*
 * author:	luo feng
 * date:	2014/5/9
 * source:	APUE
 * title:	exercise 2 of chapter 16
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <time.h>

void print_stat(struct stat *st)
{
	printf("%x\n", st->st_dev);
	printf("%x\n", st->st_ino);
	printf("%x\n", st->st_mode);
	printf("%x\n", st->st_nlink);
	printf("%x\n", st->st_uid);
	printf("%x\n", st->st_gid);
	printf("%x\n", st->st_rdev);
	printf("%x\n", st->st_size);
	printf("%x\n", st->st_blksize);
	printf("%x\n", st->st_blocks);
	printf("%s", ctime(&(st->st_atime)));
	printf("%s", ctime(&(st->st_mtime)));
	printf("%s", ctime(&(st->st_ctime)));
}

int main(int argc, char const *argv[])
{
	int sockfd1, sockfd2;
	struct stat st1, st2;

	if((sockfd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket error\n");
		return EXIT_FAILURE;
	}

	if((sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket error\n");
		return EXIT_FAILURE;
	}

	if(fstat(sockfd1, &st1) < 0) {
		printf("fstat error\n");
		return EXIT_FAILURE;
	}

	if(fstat(sockfd2, &st2) < 0) {
		printf("fstat error\n");
		return EXIT_FAILURE;
	}

	print_stat(&st1);
	print_stat(&st2);

	if(close(sockfd1) < 0) {
		printf("close socket fd error\n");
		return EXIT_FAILURE;
	}

	if(close(sockfd2) < 0) {
		printf("close socket fd error\n");
		return EXIT_FAILURE;
	}

	return 0;
}