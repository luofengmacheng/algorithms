/*
 * author:	luo feng
 * date:	2014/4/28
 * source:	APUE
 * title:	14.8 readn & writen
 * language:	C
 */

#include <stdio.h>

ssize_t readn(int fd, void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nread;

	nleft = n;
	while(nleft > 0) {
		if((nread = read(fd, ptr, nleft)) < 0) {
			if(nleft == n) {
				return -1;
			}
			else {
				break;
			}
		}
		else if(nread == 0) {
			break;
		}
		nleft -= nread;
		ptr += nread;
	}

	return n - nleft;
}

ssize_t writen(int fd, const void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;

	nleft = n;
	while(nleft > 0) {
		if((nwritten = write(fd, ptr, nleft)) < 0) {
			if(nleft == n) {
				return -1;
			}
			else {
				break;
			}
		}
		else if(nwritten == 0) {
			break;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return n - nleft;
}

int main(int argc, char const *argv[])
{


	return 0;
}