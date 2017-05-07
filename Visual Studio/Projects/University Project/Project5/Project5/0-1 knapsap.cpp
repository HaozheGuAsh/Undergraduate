#include <iostream>
#include<iomanip>

using namespace std;

void finditem(int[], int[], int, int,int [][101]);

int main111()
{
	int n = 6;
	int v[7] = { 0, 40, 35, 18, 4, 10, 2 };
	int w[7] = { 0, 100, 50, 45, 20, 10, 5 };
	int W = 100;
	int j;
	int c[7][101];
	for (int i = 0; i <= W; i++)
	{
		c[0][i] = 0;
	}
	for (int i = 0; i <= n; i++)
	{
		c[i][0] = 0;
	}

	for (int i = 1; i <= n; i++)
	{
		for (j = 1; j <= W; j++)
		{
			if (w[i] <= j)
			{
				if ((v[i] + c[i - 1][j - w[i]]) > c[i - 1][j])
				{
					c[i][j] = v[i] + c[i - 1][j - w[i]];
				}
				else
				{
					c[i][j] = c[i - 1][j];
				}
			}
			else
			{
				c[i][j] = c[i - 1][j];
			}
		}
	}
	cout << "value is " << c[6][100] << endl<<"item involved are:";
	finditem(v, w, n, W,c);
	return 0;
}
void finditem(int v[], int w[], int n, int W,int c[][101])
{
	if (n==0)
	{
		return;
	}
	if (c[n][W] == c[n - 1][W])
	{
		finditem(v, w, n - 1, W, c);
	}
	else
	{
		cout << setw(4) << n;
		finditem(v, w, n - 1, W - w[n], c);
	}
}