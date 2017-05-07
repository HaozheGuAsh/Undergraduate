#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<math.h>

void create_tree(int number,int level,int depth)
{
    pid_t pid;
    pid = fork();
    if(pid==0)
    {
	printf("I am process %d; my process pid is %d\nmy parent's pid is %d\n",number,getpid(),getppid());
	if(level<depth)
	{
     	    create_tree(2*number,level+1,depth);
	    create_tree(2*number+1,level+1,depth);
	}
//	pause();
	exit(0);	
    }
    else if(pid==-1){printf("error around id%d\n",getpid());}
    else
    {
	int status;
	waitpid(pid,&status,0);
    } 
}
int main(int argc,char** argv)
{
    if(argc!=2)
    {
	printf("Invalid Parameters");
    }
    int depth;
    depth = atoi(argv[1]);
   //` printf("depth %d\n",depth);
   // int branch = (int)pow(2,depth);
   // pid_t pids[branch][depth]; 
   create_tree(1,0,depth);
}

