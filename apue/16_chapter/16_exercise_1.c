/*
 * author:	luo feng
 * date:	2014/5/9
 * source:	APUE
 * title:	exercise 1 of chapter 16
 * language:	C
 */

#include <stdio.h>

int main(int argc, char const *argv[])
{
	unsigned int x = 0x04030201;
	unsigned char *p = (unsigned char*)&x;
	unsigned char c = *p;
	if(c == 0x04) {
		printf("Big Endian\n");
	}
	else if(c == 0x01) {
		printf("Little Endian\n");
	}
	else {
		printf("unknown Endian\n");
	}

	return 0;
}