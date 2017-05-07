#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "errno.h"
int main()
{
	char* chindex,chindex2;
	char ary[5],ary2[5];
	int i1,i2;
	for(i1=0;i1<5;i1++)
	{
		ary[i1]=0;
		ary2[i1]=0;
	}
	
	i1=50;
	i2=6;
	snprintf(ary, 10,"%d", i1);
	chindex = &ary[0];
 	snprintf(ary2, 10,"%d", i2);
	chindex2 = &ary2[0];
	printf("first is %s  second is %s \n",chindex,chindex2);
	printf("strcmp return : %d \n",strcmp(chindex,chindex2));

return 0;
}
