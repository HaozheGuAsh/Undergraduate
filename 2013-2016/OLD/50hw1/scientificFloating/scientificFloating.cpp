# include<stdio.h>
# include<fstream>
# include<string>
# include<iostream>
# include<cmath>
# include<stdlib.h>
using namespace std;

int main()
{
	float f;
	char ch[32];
	cout << "Please enter a float:"<<" ";
	cin >> f;
	unsigned int flo = *((unsigned int*)&f);
//	cout << flo << endl;
	unsigned int flo1=flo;

	for (int i = 31; i != -1; i--)
	{
		ch[i] = (flo1 % 2)+48;
	//	cout << ch[i];
		flo1 = int(flo1 / 2);
	}

	int power = 0;
	int sum = 0;
	for (int i =8 ; i!=0 ; i--)
	{
		sum += (ch[i] - 48)*pow(2, power);
		power++;
	}
	int e = sum - 127;
//	cout << "   " << e<<endl;
	char manti[23];
	for (int i = 9,j=0; i < 32; i++)
	{
		manti[j] = ch[i];
	//	cout  << manti[j];
		j++;
	}
	
	int length = 23;
	while (manti[length-1] == '0' && manti[length - 2] == '0')
	{
		length--;
	}
	if (manti[length-1] == '0'){ length--; }
	if (length <= 0){ cout << "0E0"; }
	else
	{
		if (f < 0){ cout << "-"; }
		cout << "1.";
		for (int i = 0; i < length; i++)
		{
			cout << manti[i];
		}
		cout << "E" << e;
	}
/*	int power2 = 0;
	for (int i = 22; i !=-1; i--)
	{
		mantis += (manti[i] - 48)*pow(2, power2);
	}
	int length = 30;
	while (ch[length] == '0' && ch[length - 1] == '0')
	{
		length--;
	}
	if (ch[length] == '0'){ length--; }

	if (f < 0){ cout << "-"; }
	cout << "1.";
	for (int i = 8; i < length+1; i++)
	{
		cout << ch[i];
	}
	cout << "E" << e;
*/
	/* 






	for (int i = 0; i < 31;i++)
	{
		cout << "  "<<ch[i];
	}
	while (flo1 >= 1)
	{
		flo1 /= 10;
		length++;
	}

	flo1 = flo;
	for (int i = length-1; i!=-1; i--)
	{
		ch[i] = (flo1 % 10) +48 ;
		flo1 /= 10;
	}
	for (int i = 0; i <= length; i++)
	{
		cout << ch[i] << "  ";
	}

	
	int sum10 = 0;
	int power = 0;
	for (int cur = num1length - 1; numnum > 0; numnum--)
	{
		if ((num1[cur] - '0') <= 9)
		{
			sum10 += (num1[cur] - '0') * pow(base1, power);
			//			cout << sum10;
		}
		else if ((num1[cur] - '0') > 9)//case of ABCDE
		{
			sum10 += (num1[cur] - 55) * pow(base1, power);
			//			cout << sum10;
		}
		cur--;
		power++;
	}//set sum in base 10

*/

	return 0;
}