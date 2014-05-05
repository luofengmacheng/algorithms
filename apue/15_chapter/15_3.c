/*
 * author:	luo feng
 * date:	2014/4/29
 * source:	APUE
 * title:	15.2 pipe TELL & WAIT
 * language:	C
 */

static int pfd1[2], pfd2[2];

void TELL_WAIT()
{
	if(pipe(pfd1) < 0 || pipe(pfd2) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void TELL_PARENT(pid_t pid)
{
	if(write(pfd2[1], "c", 1) != 1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
}

void WAIT_PARENT()
{
	char c;

	if(read(pfd1[0], &c, 1) != 1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	if(c != 'p') {
		printf("WAIT_PARENT : incorrect data\n");
	}
}

void TELL_CHILD(pid_t pid)
{
	if(write(pfd1[1], "p", 1) != 1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
}

void WAIT_CHILD()
{
	char c;

	if(read(pfd2[0], &c, 1) != 1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	if(c != 'c') {
		printf("WAIT_CHILD : incorrect data\n");
	}
}