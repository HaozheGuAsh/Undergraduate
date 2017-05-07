#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<cmath>
#include<ctgmath>
#include <map>
using namespace std;
/*global ary*/
int ary[26];					/* current permutation*/
vector<char>cipher;			/* cipher text*/
double matrix[27][27];		/* Bigram matrix*/
int normal[26];				/* a-z array */
map<int, int>mymap;			/* map of normal array and permutation*/

void printArray(int arr[])				/*helper print function */
{
	for (int i = 0; i < 26; i++)
		printf("%c ", arr[i]);
	cout << endl;
}

void swap(int *a, int *b)				/*swap helper function */
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void randomize(int arr[], int n)			/* get random array */
{
	srand(time(NULL));

	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
	}
}

void getpermutation()			/* replace ary[26] with random */
{											/* permutation*/

	int j = 0;
	for (int i = 'a'; i <= 'z'; i++)
	{
		ary[j] = i;
		j++;
	}
	int n = sizeof(ary) / sizeof(ary[0]);
	randomize(ary, n);

}

void bigram_matrix()
{
	//initialize matrix
	int count = 27 * 27;		//cout for every column once first avoid ln(0)
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			matrix[i][j] = 1;
		}
	}

	fstream myfile;
	myfile.open("war-and-peace.txt", fstream::out | fstream::app | fstream::in);
	if (myfile.is_open())
	{
		char ch1, ch2;
		int i, j;
		myfile.get(ch1);
		while (myfile.get(ch2))
		{
			i = (int)ch1 - 97;
			j = (int)ch2 - 97;
			if (ch1 == ' ')
			{
				i = 26;
			}
			if (ch2 == ' ')
			{
				j = 26;
			}
			if (i >= 0 && i <= 26 && j >= 0 && j <= 26)
			{
				matrix[i][j]++;
				count++;
			}
			/*swap*/
			ch1 = ch2;
		}
		myfile.close();
	}
	/*divided by total*/
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			matrix[i][j] /= count;
		}
	}
}

void getcipher()
{
	fstream myfile;
	myfile.open("cipher.txt", fstream::out | fstream::app | fstream::in);
	if (myfile.is_open())
	{
		char ch;
		while (myfile.get(ch))
		{
			if ((ch >= 'a'&&ch <= 'z') || (ch == ' '))
			{
				cipher.push_back(ch);
			}
			else
			{
				cipher.push_back(' ');
			}
		}
		myfile.close();
	}
}

double getsum(int array[26])				/* function to calculate lnpl*/
{
	double lnpl = 0;
	mymap.clear();
	for (int i = 0; i < 26; i++)
	{
		mymap.insert(pair<int, int>(array[i], normal[i]));
	}
	for (int i = 0; i < cipher.size() - 1; i++)
	{
		char ch1, ch2;
		int a = 0, b = 0;
		//char cipher
		ch1 = cipher.at(i);
		ch2 = cipher.at(i + 1);

		//int cipher
		if (ch1 != ' ')
		{
			a = mymap.at(ch1);
		}
		if (ch2 != ' ')
		{
			b = mymap.at(ch2);
		}


		/*fit to matrix*/
		a = a - 97;
		b = b - 97;
		if (ch1 == ' ')
		{
			a = 26;
		}
		if (ch2 == ' ')
		{
			b = 26;
		}
		lnpl += log(matrix[a][b]);
	}
	return lnpl;
}

void translate(int array[26])					/* use map to transfer cipher*/
{												/* text to message use one   */
	for (int i = 0; i < cipher.size(); i++)		/* specific permutation*/
	{
		char ch1;
		int a = 0;
		//char cipher
		ch1 = cipher.at(i);
		if (ch1 == ' ')
		{
			cout << ' ';
		}
		else if (ch1 >= 'a'&&ch1 <= 'z')
		{
			cout << (char)(mymap.at(ch1));
		}
		else
		{
			cout << ch1;
		}

	}
}
int main()
{
	srand(time(NULL));						/*make true random permutation */
	bigram_matrix();							/* set up bigram matrix*/
	getcipher();								/*read cipher text */
	int iteratenum = 3000;					/* set iteration number 3000*/


	for (int i = 0; i < 26; i++)
	{
		normal[i] = (i + 'a');				/* set  up a-z array*/
	}


	getpermutation();						/* get a random permutation*/
	double flnpl = getsum(ary);				/* as a start point*/
	while (flnpl < -2560)					/* in order to prevent stuck*/
	{										/* in certain permutation*/
		getpermutation();
		flnpl = getsum(ary);
		for (int i = 0; i < iteratenum; i++)
		{
			int f1[26];							//f'
			for (int j = 0; j < 26; j++)
			{
				f1[j] = ary[j];
			}
			int ran1 = rand() % 26;
			int ran2 = rand() % 26;
			while (ran1 == ran2)
			{
				ran1 = rand() % 26;
				ran2 = rand() % 26;
			}									/*copy ary ot f and do swap */
			swap(&f1[ran1], &f1[ran2]);					//f'

			double f1lnpl = getsum(f1);					//lnpl of f'
			if (f1lnpl > flnpl)
			{
				/*just replace*/
				for (int j = 0; j < 26; j++)
				{
					ary[j] = f1[j];
				}
				flnpl = getsum(ary);
			}
			else
			{
				/*flip coin*/
				double result = (double)rand() / RAND_MAX;

				double probability = exp(f1lnpl - flnpl);
				if (result < probability)				//do replace
				{
					for (int j = 0; j < 26; j++)
					{
						ary[j] = f1[j];
					}
					flnpl = getsum(ary);
				}
			}
			if (i % 200 == 0)				/* see if deciphered text satisfy*/
			{
				mymap.clear();
				cout << "At iteration: " << i << "flnpl is :" << flnpl << endl;
				for (int j = 0; j < 26; j++)
				{
					mymap.insert(pair<int, int>(ary[j], normal[j]));
				}
				translate(ary);
				cout << endl << "----------------------------------" << endl;
			}
		}
	}
	//cout << flnpl;

	/*creating map*/
	mymap.clear();
	for (int i = 0; i < 26; i++)
	{
		mymap.insert(pair<int, int>(ary[i], normal[i]));
	}

	for (int i = 0; i < 26; i++)
	{
		cout << (char)ary[i] << " ";
	}
	translate(ary);
	cout << endl;
}
