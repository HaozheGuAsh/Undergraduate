#include <stdio.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <fcntl.h>
using namespace std;
int main()
{
	char* chindex, *chindex2;
	char ary[5], ary2[5];
	int i1, i2;

	i1 = 50;
	i2 = 6;
	sprintf_s(ary, "%d", i1);
	chindex = &ary[0];
	sprintf_s(ary2, "%d", i2);
	chindex2 = &ary2[0];
	printf("first is %s  second is %s \n", chindex, chindex2);
	printf("strcmp return : %d \n", strcmp(chindex, chindex2));
	printf("sdf");
	return 0;
}

