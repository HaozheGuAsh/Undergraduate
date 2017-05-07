#include <unistd.h>
#include <stdio.h>
int main()
{
int i;
for(i = 0; i < 6; ++i)
{
int res;
 if (i==2){i=3;}
 res = close(i);
printf("res: %d\n", res);
 }
execl ("~/hhdhkaozhe26/ECS150/TEST/b.out","3", (char*) NULL);
perror ("something bad happened");
}
