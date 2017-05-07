#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>

int main()
{
	pid_t pid[3];
	/* create pipes */
	int atob[2],btoc[2],ctoa[2],n;
	if(pipe(atob)==-1) 
	{
	perror("pipe1 fail");
	exit(1);
	}
	if (pipe(btoc) == -1)
	{
		perror("pipe2 fail");
		exit(1);
	}
	if (pipe(ctoa) == -1)
	{
		perror("pipe3 fail");
		exit(1);
	}

	/* process p1*/
	pid[0] = fork();
	if (pid[0] == 0)
	{
		char str1[20],str2[20],dummy[20];
		printf("I am Process P1 \nMy Pid is %ld \nPlease enter a string: ", getpid());  // introduce  
		scanf("%s", &str1);																// get string
		write(atob[1], str1, 20);														// write to pipe atob
		read(ctoa[0], str2, 20);														// read from pipe ctoa
		printf("I am Process P1 \nMy Pid is %ld \nI just received uppercase %s\n", getpid(),str2);	//send finished string to terminal
		write(atob[1], dummy, 1);														// tell p2 you can terminate
		for (n = 0; n != 2; n++)
		{
			close(atob[n]);
			close(btoc[n]);
			close(ctoa[n]);
		}
		exit(0);
	}

	/* process p2*/
	pid[1] = fork();
	if (pid[1] == 0)
	{
		//printf("process2\n");
		char str2[20],str3[20],dummy[20];
		int i,c,a;
		read(atob[0], str2, 20);									// read from atob
		printf("I am Process P2 \nMy Pid is %ld \n", getpid());  // introduce  
		printf("I just received the string %s\n", str2);			
		for (i = 0; str2[i] != '\0'; i++);						// reverse the string
		str3[i] = '\0';
		a = 0;
		for (c=i-1; c >= 0; c--)
		{
			str3[c] = str2[a];
			a++;
		}
		printf("I am sending %s to P3\n", str3);
		write(btoc[1], str3, 20);
		
		read(atob[0], dummy, 1);								// receive info to end
		write(btoc[1], dummy, 1);								// tell p3 you can end
		for (n = 0; n != 2; n++)
		{
			close(atob[n]);
			close(btoc[n]);
			close(ctoa[n]);
		}
		exit(0);
	}

	/* process p3*/
	pid[2] = fork();
	if (pid[2] == 0)
	{
		char str3[20],dummy[20];
		int i;
		read(btoc[0], str3, 20);									// read from btoc
		printf("I am Process P3 \nMy Pid is %ld \n", getpid());  // introduce  
		printf("I just received the string %s\n", str3);		
		for (i = 0; str3[i] != '\0'; i++)						// change to uppercase
		{
			str3[i] = str3[i] - 32;
		}
		printf("I am sending uppercase %s back to P1 \n", str3);
//		sleep(10);
		write(ctoa[1], str3, 20);								//write to pipe ctoa
		read(btoc[0], dummy, 1);								// receive into to end
		for (n = 0; n != 2; n++)
		{
			close(atob[n]);
			close(btoc[n]);
			close(ctoa[n]);
		}
		exit(0);
	}
	for (n = 0; n != 2; n++)
	{
		close(atob[n]);
		close(btoc[n]);
		close(ctoa[n]);
	}


	for (n = 0; n<3; n++)
	{
		int status;
		waitpid(pid[n], &status, 0);
		printf("I am Process %d\nMy Pid is %d\nI am about to die\n", n+1,pid[n]);
	}
}
