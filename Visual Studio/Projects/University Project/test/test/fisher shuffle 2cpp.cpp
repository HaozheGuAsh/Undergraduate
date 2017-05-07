// C Program to shuffle a given array

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
/*global ary*/
char ary[26];
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void randomize(int arr[], int n)
{
	srand(time(NULL));

	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
	}
}

void getpermutation()
{
	int arr[26];
	int j = 0;
	for (int i = 'a'; i <= 'z'; i++)
	{
		arr[j] = i;
		j++;
	}
	int n = sizeof(arr) / sizeof(arr[0]);
	randomize(arr, n);
	for (int i = 0; i < 26; i++)
	{
		ary[i] = (char)arr[i];
	}
}

int main()
{

	getpermutation();
	for (int i = 0; i < 26; i++)
	{
		cout << ary[i];
	}


	cout << endl;
}