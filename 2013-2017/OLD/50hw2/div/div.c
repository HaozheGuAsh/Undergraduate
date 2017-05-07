#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	unsigned int dividend = (unsigned int)atoll(argv[1]);
	unsigned int divisor = (unsigned int)atoll (argv[2]);

	unsigned int quotient = 0;
	unsigned int remainder = 0;

	
//	printf("test  %u %u", dividend, divisor);
	
	int bit;
	for (bit=31; bit >= 0;bit--)
	{
		remainder  = remainder << 1;  // R<<1


		if ( ( ( dividend >> bit ) & 1) == 1)
		{
			remainder |= 1;//set LSB to 1
		}
		else if ( ( ( dividend >> bit ) & 1) == 0)
		{
			remainder &= ~1;//set LSB to 0
		}
		// R[0] = D[i]

		
		if (remainder >= divisor)
		{
			remainder -= divisor; //R -D
			quotient |= 1 << bit; //set quotient's current bit to 1
		}

	}
	printf(" %u / ", dividend);
	printf("%u ", divisor);
	printf(" =  %u ", quotient);
	printf(" R %u \n", remainder);
	return 0;
}