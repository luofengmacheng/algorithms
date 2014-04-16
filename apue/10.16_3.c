#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

static sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo)
{
	sigflag = 1;
}

void TELL_WAIT()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("signal(SIGUSR1) error\n");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("signal(SIGUSR2) error\n");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		printf("SIG_BLOCK error\n");
	}
}

void TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);
}

void WAIT_CHILD()
{
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		printf("SIG_SETMASK error\n");
	}
}

void TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void WAIT_PARENT()
{
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		printf("SIG_SETMASK error\n");
	}
}

int main(int argc, char const *argv[])
{
	pid_t pid;
	int fd;

	TELL_WAIT();

	if((fd = open("luo.txt", O_RDWR)) < 0) {
		printf("open file error\n");
	}

	int data = 0;
	if(write(fd, &data, sizeof(data)) == -1) {
		printf("write file error\n");
	}
	//fsync(fd);

	/*if((pid = fork()) < 0) {
		printf("fork error\n");
	}
	else if(pid == 0) {
		//while(1){
			WAIT_PARENT();
			int d1 = 0;
			lseek(fd, 0, SEEK_SET);
			if(read(fd, &d1, sizeof(d1)) == -1) {
				printf("read error\n");
			}
			printf("%d process read %d\n", getpid(), d1);
			++d1;
			if(write(fd, &d1, sizeof(d1)) == -1)
				printf("write error\n");
			fsync(fd);
			printf("%d process increase to %d\n", getpid(), d1);
			TELL_PARENT(getppid());
		//}
	}
	else {
		//while(1){
			int d2 = 0, read_cnt = 0;
			lseek(fd, 0, SEEK_SET);
			if((read_cnt = read(fd, &d2, sizeof(d2))) == -1) {
				printf("read error\n");
			}
			else if(read_cnt != sizeof(d2)) {
				printf("read error\n");
			}
			printf("%d process read %d\n", getpid(), d2);
			++d2;
			if(write(fd, &d2, sizeof(d2)) == -1)
				printf("write error\n");
			fsync(fd);
			printf("%d process increase to %d\n", getpid(), d2);
			TELL_CHILD(pid);
			WAIT_CHILD();
		//}
	}*/
	if(read(fd, &data, sizeof(data)) == -1)
		printf("read error\n");
	printf("%d\n", data);
	++data;
	write(fd, &data, sizeof(data));
	read(fd, &data, sizeof(data));
	printf("%d\n", data);

	close(fd);
	
	return 0;
}