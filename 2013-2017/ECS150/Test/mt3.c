#include <signal.h>
#include <stdio.h>
#include <unistd.h>
static void sig_alarm (int signo)
{
return;
}
unsigned int sleep1 (unsigned int nsecs)
{
if(signal(SIGALRM,sig_alarm) == SIG_ERR)
return (nsecs);
//alarm(nsecs);
pause();
return (alarm(0));
}
int main()
{
int res = sleep1(5);
printf("res: %d\n", res);
}
