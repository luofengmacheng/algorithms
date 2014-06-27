struct hello {
	char text[256];
};

struct hello_echo {
	char text_echo[256];
};

program ECHO_PROG {
	version ECHO_VERS {
		hello_echo ECHOPROC(hello) = 1;
	} = 1;
} = 0x31230000;
