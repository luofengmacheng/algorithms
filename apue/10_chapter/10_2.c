/*
 * author:	luo feng
 * date:	2014/6/9
 * source:	APUE
 * title:	10.6 10-2
 * language:	C
 */

#include <stdio.h>
#include <signal.h>
#include <pwd.h>

static void
my_alarm(int signo)
{
	struct passwd *rootptr;

	printf("in signal handler\n");
	if((rootptr = getpwnam("root")) == NULL) {
		fprintf(stderr, "getpwnam(root) error %d\n", __LINE__);
	}
	alarm(1);
}

int main(int argc, char const *argv[])
{
	struct passwd *ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);

	for( ; ; ) {
		if((ptr = getpwnam("root")) == NULL) {
			fprintf(stderr, "getpwnam error %d\n", __LINE__);
		}
		printf("pw_name = %s\n", ptr->pw_name);
	}

	return 0;
}