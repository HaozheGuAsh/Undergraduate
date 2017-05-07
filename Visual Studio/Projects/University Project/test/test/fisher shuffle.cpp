#include <iostream>
#include <stdlib.h>

using namespace std;

void fisherYatesShuffling(char *arr)
{
	int n = 26;
	int a[26];
	int ind[26];
	for (int i = 0; i < n; i++)
		ind[i] = 0;
	int index;

	for (int i = 0; i < n; i++)
	{
		do
		{
			index = rand() % n;
		} while (ind[index] != 0);

		ind[index] = 1;
		a[i] = *(arr + index);
	}
	for (int i = 0; i < n; i++)
	{
		char ch = a[i];
		cout <<ch << " ";
	}
}

int main3(int argc, char **argv)
{
	/*cout << "Enter the array size: ";
	int n;
	cin >> n;
	cout << "Enter the array elements: ";
	int a[n];
	for (int i = 0; i < n; i++)
	{
	cin >> a[i];
	}*/
	char a[26];
	int j = 0;
	for (int i = 'a'; i <= 'z'; i++)
	{
		a[j] = i;
		j++;
	}
	fisherYatesShuffling(a);
	cout << endl;
	fisherYatesShuffling(a);
	cout << endl;
	fisherYatesShuffling(a);
	cout << endl;
	return 0;
}