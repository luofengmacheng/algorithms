/*
 * author:	luo feng
 * date:	2013/12/10
 * source:	APUE
 * info:	第三章习题第二题
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define	MAXN	4096
#define	EXIT_SUCC	0
#define EXIT_FAIL	-1

int dup2_func(int filedes, int filedes2)
{
    int i = 0;
    int n = 0;
    int top = 0;
    int stack[MAXN];

    if((filedes2 > MAXN) || (filedes2 < 0)) {
        printf("invalid filedes2!\n");
        return EXIT_FAIL;
    }

    if(filedes == filedes2) {
        return filedes2;
    }

    while((n = dup(filedes)) < filedes2) {
        if(n == -1) {
            printf("System can not make a filedes!\n");
            return EXIT_FAIL;
        }
        stack[top++] = n;
    }

    close(filedes2);

    if(dup(filedes) == -1) {
        printf("dup function error!\n");
        return EXIT_FAIL;
    }

    for(i = 0; i < top; ++i) {
        close(stack[i]);
    }

    return filedes2;
}

int main(int argc, char *argv[])
{
    int filedes, filedes2;

    if(argc != 3) {
        printf("Parameter error!\n");
        return EXIT_FAIL;
    }

    filedes = open(argv[1], O_RDWR);
    if(filedes == -1) {
        printf("Error! System cannot open %s\n", argv[1]);
        return EXIT_FAIL;
    }

    filedes2 = atoi(argv[2]);
    if(dup2_func(filedes, filedes2) != EXIT_FAIL) {
        write(filedes2, "test", sizeof("test"));
    }

    return 0;
}
