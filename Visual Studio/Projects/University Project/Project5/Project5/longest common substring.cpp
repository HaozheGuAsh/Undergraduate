#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int main4()
{
	string str1 = "cabccb";
	string str2 = "babcba";

	int m = str1.length();
	int n = str2.length();

	int c[6][6];
	int s[6];
	for (int i = 0; i < m; i++)
	{

		for (int j = 0; j < n; j++)
		{
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++)
	{
		s[i] = 0;
	}

	int maxnum = 0;
	int i, j;
	for ( i = 0; i < m; ++i)
	{
		for ( j = 0; j < n; ++j)
		{
			if (str1[i] != str2[j])
			{
				c[i][j] = 0;
			}
			else
			{
				if (i == 0 || j == 0)
				{
					c[i][j] = 1;
				}
				else
				{
					c[i][j] = c[i - 1][j - 1] + 1;
				}
				if (c[i][j] > maxnum)
				{
					maxnum = c[i][j];
					s[i] = i;
				}

				
			}
		}

	}

	cin >> str1;
	return 0;
}