# include<stdio.h>
# include<fstream>
# include<string>
# include<iostream>
# include<cmath>
using namespace std;

int main(int argc,char* argv[])
{
	ifstream inf1(argv[1]);
	ifstream inf2(argv[2]);
	int size;
	inf1 >> size;
	inf2 >> size;
	
	int ary1[100];
	int ary2[100];
	int num;
	int pos1 = 0, pos2 = 0;

	while (inf1 >> num)
	{
		ary1[pos1] = num;
		pos1++;
	}

	while (inf2 >> num)
	{
		ary2[pos2] = num;
		pos2++;
	}
	int curpos1 = 0, curpos2 = 0;
	while (size != 0)
	{
		for (int i=0; i < size; i++)
		{
			int sum=0;
			for (int j=0; j < size; j++)
			{
				sum += ary1[curpos1+j] * ary2[curpos2+i];
			}
			curpos2++;
		}
		curpos1 += size - 1;
		size--;
	}
	return 0;
}
