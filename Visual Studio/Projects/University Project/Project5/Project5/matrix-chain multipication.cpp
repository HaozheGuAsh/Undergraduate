#include <iostream>
#include <iomanip>
using namespace std;

int main2()
{
	int p[7] = {5,6,3,7,5,3,4};
	int n = 6;
	int m[7][7];
	int s[7][7];

	int i, j,q;
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			m[i][j] =0;
			s[i][j] = 0;
		}

	}

	int d;
	for (d = 2; d <= n; d++)
	{
		for (i = 1; i <= (n - d + 1); i++)
		{
			j = i + d - 1;
			m[i][j] = 10000000;
			for (int k = i; k <= j - 1; k++)
			{
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout <<setw(8)<< m[i][j] << "   ";
		}
		cout << endl;
	}

	cout << endl << endl;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << setw(8)<< s[i][j] << "   ";
		}
		cout << endl;
	}
	cin >> n;
	return 0;
}