#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum,count;
    char c;
    sum=0;
    count=0;
    printf("enter number");
    
    while(1)
    {
        while(1)
        {
	    scanf("%c",&c);
	    if(c==10) {break;}
            count++;
	    sum=sum+c;	
        }
        if(count==0)
        { return 0;
        }  
        else
        {
            printf("%c",sum%64+32);
	    count=0;
	    sum=0;
            printf("\nenter number");
        }
  }
    return 0;
}
