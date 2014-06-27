#include "echo.h"

hello_echo *echoproc_1_svc(hello *inp, struct svc_req *rqstp)
{
	static hello_echo out;
	strncpy(out.text_echo, inp->text, strlen(inp->text));
	out.text_echo[strlen(inp->text)] = 0;

	return (&out);
}
