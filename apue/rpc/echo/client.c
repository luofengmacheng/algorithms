#include "echo.h"

int main(int argc, char const *argv[])
{
	CLIENT *cl;
	hello in;
	hello_echo *outp;

	if(argc != 3) {
		fprintf(stderr, "usage: client <hostname> <integer_value>\n");
		exit(0);
	}

	cl = clnt_create(argv[1], ECHO_PROG, ECHO_VERS, "tcp");
	strncpy(in.text, argv[2], strlen(argv[2]));
	in.text[strlen(argv[2])] = 0;
	if((outp = echoproc_1(&in, cl)) == NULL) {
		fprintf(stderr, "%s\n", clnt_sperror(cl, argv[1]));
		exit(0);
	}
	printf("result: %s\n", outp->text_echo);

	return 0;
}
