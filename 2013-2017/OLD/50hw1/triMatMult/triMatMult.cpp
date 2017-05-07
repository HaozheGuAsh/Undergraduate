# include<stdio.h>
# include<fstream>
# include<string>
# include<iostream>
# include<cmath>
using namespace std;
int value(int size, int i, int j, int ary[]);
int main(int argc,char* argv[])
{
	ifstream inf1(argv[1]);
	ifstream inf2(argv[2]);
	int size;
	inf1 >> size;
	inf2 >> size;
	
	int ary1[2000];
	int ary2[2000];
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
	}// read the file into two array
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int sum = 0;
			for (int k = 0; k < size; k++)
			{
				sum += value(size,i,k,ary1)*value(size,k,j,ary2);
			}
			if (i <= j){ cout << sum<<" "; }
		}
	}
	return 0;
}

int value(int size, int i, int j,int ary[])
{
	if (i > j)
	{
		return  0;
	}
	else
	{
		return ary[j + (i*size) - i*(i + 1) / 2];
	}
	
}
	


 /*   for (int r = 0; r < size; r++)
	{
		
		for (int c = 0; c < size; c++)
		{
			int sum = 0;
			for (int k = 0; k < size; k++)
			{
				sum += mat1[k][r] * mat2[c][k];
			}
			if (r<=c){ cout << sum << " "; }
		}
	}

int mat1[200][200], mat2[200][200];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mat1[i][j] = 0;
			mat2[i][j] = 0;
		}
	}//set 0 to two mat


	int arypos = 0;
	int cursize = size-1;
	for (int r = 0; r < size; r++)
	{
		for (int c = size-cursize-1;c<size; c++)
		{
			mat1[c][r] = ary1[arypos];
			mat2[c][r] = ary2[arypos];
			arypos++;
		}
		cursize--;
		for (int t = 0; t < 137; t++)
	{
		cout << "ary1  " << ary1[t] << endl;
	}
	for (int t = 0; t < 137 ; t++)
	{
		cout << "ary2  " << ary2[t] << endl;
	}
*/


/*	int curpos1 = 0, curpos2 = 0;
	while (size != 0)
	{
		for (int i=0; i < size; i++)
		{
			int sum=0;
			for (int j=0; j < size; j++)
			{
				sum += ary1[curpos1+j] * ary2[curpos2+i];
				cout << "ary1"<<ary1[curpos1+j]<<"ary2"<<ary2[curpos2+i]<<"sum" << sum<<endl;
			}
			cout << sum << " ";
			curpos2++;
		}
		curpos1 += size - 1;
		size--;
	}
	*/
