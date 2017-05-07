#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main(void) {
 pid_t childpid,endid;
 pid_t mypid;
 pid_t myparentspid;
int status;
 mypid = getpid();
 myparentspid = getppid();
 childpid = fork();

 if (childpid == 0)
 {printf ("children ID(myPID_1): %ld, ID(myPID_2): %ld and Parent PID: %ld\n", (long int)
getpid(), (long int) getppid(), (long int) myparentspid);}

 else
 {
//waitpid(childpid,&status,0);
printf ("ID(myPID_1): %ld, ID(myPID_2): %ld and Parent PID: %ld\n", (long int )getpid(), (long int) getppid(), (long int) myparentspid);}

 return (0);
}
