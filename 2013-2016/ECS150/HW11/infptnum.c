#include<stdio.h>
#include<unistd.h>
int main()
{
    int count = 0;
    while(1)
    {
	sleep(1);
	if(count>10)count=0;
	printf("%d\n",count);
	count++;
	
    }
}
