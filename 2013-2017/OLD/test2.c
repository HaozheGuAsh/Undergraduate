#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t childpid = 0;
	int count=0;
	if(childpid == fork())
	{
		sleep(5);
		while(1)
		{
			printf("Child: %d\n",count);
			sleep(1);
			count++;
		}
	}
	else
	{
		while(1)
		{
			printf("parent: %d \n",count);
			sleep(1);
			count++;
		}
	}
	return 0;

}
