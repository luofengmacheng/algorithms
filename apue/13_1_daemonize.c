/*
 * author:	luo feng
 * date:	2014/4/23
 * source:	APUE 13.3
 * title:	守护进程
 * language:	C
 * 要点：守护进程主要的特点是在后台运行，没有控制终端。
 * 主要要修改的有：文件模式屏蔽字、文件描述符、当前工作目录。
 * 思路是：创建子进程，使子进程脱离原来的进程组，修改文件模式屏蔽字、文件描述符、当前工作目录，将标准输入、输出、出错定向到/dev/null。
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/resource.h>

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
	/*if((pid = fork()) < 0) {
		printf("%s : can't fork\n", cmd);
	}
	else if(pid != 0) {
		exit(0);
	}*/

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

int main(int argc, char const *argv[])
{
	daemonize("ls");

	return 0;
}
