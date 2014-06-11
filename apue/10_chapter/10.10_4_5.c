/*
 * author:	luo feng
 * date:	2014/6/11
 * source:	APUE
 * title:	10.10 10_4
 * language:	C
 */

#include <unistd.h>
#include <signal.h>

/*
 * problem1:如果调用这先调用了alarm()，那么在调用sleep1()后会擦除用户调用的alarm()。
 * solution:检查sleep1()中第一次调用alarm的返回值，如果返回值小于本次的参数nsecs，则忽略。
 * 如果返回值大于nsecs，则在sleep1()返回之前，复位此闹钟，使其在上次闹钟的设定时间再次发生超时。
 * problem2:sleep1()中修改了SIGALRM的配置。
 * solution:调用signal函数时保存返回值，然后在sleep1()返回之前再次修改SIGALRM的配置。
 * problem3:sleep1()中alarm()与pause()产生了竞争，有可能alarm在pause()之前就超时了，之后再调用pause()，则程序永远休眠。
 * solution:见sleep2()。
 */

static void
sig_alrm(int signo)
{
}

unsigned int
sleep1(unsigned int nsecs)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR) {
		return nsecs;
	}

	alarm(nsecs);
	pause();

	return alarm(0);
}

static jmp_buf env_alarm;

static void
sig_alrm(int signo)
{
	longjmp(env_alarm, 1);
}

unsigned int
sleep2(unsigned int nsecs)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR) {
		return nsecs;
	}

	if(setjmp(env_alarm) == 0) {
		alarm(nsecs);
		pause();
	}

	return alarm(0);
}