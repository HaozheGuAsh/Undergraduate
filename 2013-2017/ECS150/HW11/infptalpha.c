#include<stdio.h>
#include<unistd.h>
int main()
{
    char alpha = 'a';
    while(1)
    {
	sleep(1);
	if(alpha>'z')alpha='a';
	printf("%c\n",alpha);
	alpha++;
	
    }
}
