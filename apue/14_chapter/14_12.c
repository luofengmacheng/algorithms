/*
 * author:	luo feng
 * date:	2014/4/28
 * source:	APUE
 * title:	14.9 mmap
 * language:	C
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fdin, fdout;
	void *src, *dst;
	struct stat statbuf;

	if(argc != 3) {
		perror("usage : programname <fromfile> <tofile>");
		exit(EXIT_FAILURE);
	}

	if((fdin = open(argv[1], O_RDONLY)) < 0) {
		perror("open file for reading failed");
		exit(EXIT_FAILURE);
	}

	if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC)) < 0) {
		perror("open file for writing failed");
		exit(EXIT_FAILURE);
	}

	if(fstat(fdin, &statbuf) < 0) {
		perror("fstat failed");
		exit(EXIT_FAILURE);
	}

	if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1) {
		perror("lseek failed");
		exit(EXIT_FAILURE);
	}

	if(write(fdout, "", 1) == -1) {
		perror("write failed");
		exit(EXIT_FAILURE);
	}

	if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, 
		fdin, 0)) == MAP_FAILED) {
		perror("mmap error for input");
	    exit(EXIT_FAILURE);
	}

	if((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fdout, 0)) == MAP_FAILED) {
		perror("mmap error for output");
	    exit(EXIT_FAILURE);
	}

	

	close(fdin);
	close(fdout);
	memcpy(dst, src, statbuf.st_size);

	exit(EXIT_SUCCESS);
}