/*
 * author:	luo feng
 * date:	2014/4/23
 * source:	APUE 13.5 & 13.6
 * title:	
 * language:	C
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <signal.h>
#include <sys/resource.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

sigset_t mask;

int lockfile(int fd)
{
	return 1;
}

void reread()
{

}

int already_running()
{
	int fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
	if(fd < 0) {
		syslog(LOG_ERR, "can't open %s : %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	if(lockfile(fd) < 0) {
		if(errno == EACCES | errno == EAGAIN) {
			close(fd);
			return 1;
		}
		syslog(LOG_ERR, "can't lock %s : %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);

	return 0;
}

void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	/* clear file creation mask 清除文件模式创建屏蔽字 */
	umask(0);

	/* get maximum number of file descriptors 获取文件描述符的最大个数 */
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0) {
		printf("%s : can't get file limit\n", cmd);
	}

	/* become a session leader to lose controlling TTY 使得子进程成为一个会话的首进程，并且不能获取控制终端 */
	if((pid = fork()) < 0) {
		printf("%s : can't fork\n", cmd);
	}
	else if(pid != 0) {
		exit(0);
	}
	/* 调用setsid()成功后，当前进程成为新的会话组长和新的进程组长，*/
	/* 并与原来的登录会话和进程组脱离。 */
	setsid();

	/* ensure future opens won't allocate controlling TTYs */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0) {
		printf("can't ignore SIGHUP\n");
	}
	if((pid = fork()) < 0) {
		printf("%s : can't fork\n", cmd);
	}
	else if(pid != 0) {
		exit(0);
	}

	/* change the current working directory to the root */
	/* so we won't prevent file systems from being unmounted */
	/* 将当前工作目录更改为根目录，因为当前工作目录是从父进程继承过来的，*/
	/* 如果继承过来的当前工作目录是挂载上去的，那么就不允许卸载当前工作目录 */
	if(chdir("/") < 0) {
		printf("%s : can't change directory to /\n", cmd);
	}

	/* close all open file descriptors 关闭所有的打开文件描述符 */
	if(rl.rlim_max == RLIM_INFINITY) {
		rl.rlim_max = 1024;
	}
	for(i = 0; i < rl.rlim_max; ++i) {
		close(i);
	}

	/* attach file descriptors 0, 1 and 2 to /dev/null 将0, 1, 2文件描述符定向到/dev/null */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/* initiallize the log file 初始化日志文件 */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexcepted file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
	sleep(10);
}

void *thr_fn(void *arg)
{
	int err, signo;

	for(;;) {
		err = sigwait(&mask, &signo) ;
		if(err != 0) {
			syslog(LOG_ERR, "sigwait failed");
			exit(1);
		}

		switch(signo) {
		case SIGHUP:
		    syslog(LOG_INFO, "Re_reading configuration file");
		    reread();
		    break;
		case SIGTERM:
		    syslog(LOG_INFO, "got SIGTERM; exiting");
		    exit(0);
		default:
		    syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}
}

int main(int argc, char const *argv[])
{
	int err;
	pthread_t tid;
	const char *cmd;
	struct sigaction sa;

	if((cmd == strrchr(argv[0], '/')) == NULL) {
		cmd = argv[0];
	}
	else {
		cmd++;
	}

	daemonize(cmd);

	if(already_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0) {
		printf("can't restore SIGHUP default\n");
	}
	sigfillset(&mask);
	if((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0) {
		printf("SIG_BLOCK error\n");
	}

	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0) {
		printf("can't create thread\n");
	}
	sleep(10);

	return 0;
}