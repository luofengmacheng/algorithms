/*
 * author:	luo feng
 * date:	2013/12/10
 * source:	Advanced Programming in the Unix Environment
 * info:	55页关于I/O的效率
 * language:	C
 */

#include <unistd.h>
#include <fcntl.h>

#define BUFFSIZE	4096

int main()
{
    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if(write(STDOUT_FILENO, buf, n) != n)
            write(STDERR_FILENO, "error", sizeof("error"));
    }

    
    return 0;
}
