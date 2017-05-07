#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include<signal.h>
#include <sys/wait.h>
int flag=0;
int loop=0;
int main()
{
	int num;
	pid_t pid1, pid2;
	void c_action(int);
	static struct sigaction cact,oact;

	pid1 = fork();
	if (pid1 == 0)
	{
		//printf("my id is %d", getpid());
		/*first children*/
		/*set SIGALRM action for children & save previous action*/
		cact.sa_handler = c_action;
		sigaction(SIGALRM, &cact, &oact);
		int ccount = 0;
		

		//for (ccount;ccount<5;ccount++)
		while (1)
		{
			ccount++;
			
			//if (ccount % 10000 == 0){ printf("child 1: %d\n", ccount); };
			if (flag == -1)
			{ 
				printf("Count is %d, my pid is %d\n", ccount, getpid());
				ccount = 0; 
				flag = 0; 
				//printf("1loop %d \n", loop); 
			}
			if (loop == 5)
			{ 
				//sleep(2);
				//printf("1finish\n");
				exit(0);
			}
		}
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		//printf("my id is %d", getpid());
		/*first children*/
		/*set SIGALRM action for children & save previous action*/
		cact.sa_handler = c_action;
		sigaction(SIGALRM, &cact, &oact);
		int ccount = 0;
		
		//for (ccount; ccount<5; ccount++)
		while (1)
		{
			ccount++;

			//if (ccount % 10000 == 0){ printf("child 2: %d\n", ccount); };
			if (flag == -1)
			{ 
				printf("Count is %d, my pid is %d\n", ccount,getpid());
				ccount = 0; 
				flag = 0;
				//printf("2loop %d \n", loop); 
			}
			if (loop == 5)
			{ 
				//sleep(2);
				//printf("2finish\n");
				exit(0);
			}
		}
	}
	/*parent sending SIGALRM*/
	//printf("pids are %d   %d", pid1, pid2);
	
	for (num = 0; num < 5; num++)
	{
		
		sleep(1);
		//printf("in loop %d\n",num);
		kill(pid1,SIGALRM);
		kill(pid2,SIGALRM);
	}
	wait(NULL);
	wait(NULL);
	/*restore SIGALRM action---terminate process*/
	//sigaction(SIGALRM, &oact, NULL);
	/*parent sending SIGALRM to terminate children*/
	//kill(pid1, SIGALRM);
	//kill(pid2, SIGALRM);
	//printf("end!!\n");

}	
/*child action to SIGALRM*/
void c_action(int sig)
{
	//printf("in c_action");
	//printf("Count is %d, my pid is %d\n",count, getpid());
	loop++;
	flag = -1;
}