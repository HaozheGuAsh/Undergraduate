#include <iostream>
#include <iomanip>

using namespace std;

void printLCS (char[][6],char[],int,int);
int main3()
{
	char x[7] = { '0', 'B', 'C', 'A', 'A', 'B', 'A' };
	char y[6] = { '0','A','B','A','C','B' };
	
	int m = 6;//xlength
	int n = 5;//ylength

	char b[7][6];
	int c[7][6];

	int i, j;

	for (i = 0; i <= m; i++)
	{
		c[i][0] = 0;
	}

	for (j = 0; j <= n; j++)
	{
		c[0][j] = 0;
	}

	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][ j - 1] + 1;
				b[i][j] = 'D';	// go to up diagonal
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 'U'; // go up
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 'L'; // go left
			}

		}
	}


	printLCS(b, x, m, n);

	cin >> n;
	return 0;
}
void printLCS(char b[][6], char x[], int i, int j)
{
	if ((i == 0) || (j == 0))
	{
		return;
	}
	if (b[i][j] == 'D')
	{
		printLCS(b, x, i - 1, j - 1);
		cout << x[i] << " ";
	}
	else if (b[i][j] == 'U')
	{
		printLCS(b, x, i - 1, j);
	}
	else if (b[i][j]=='L')
	{
		printLCS(b, x, i, j - 1);
	}
}