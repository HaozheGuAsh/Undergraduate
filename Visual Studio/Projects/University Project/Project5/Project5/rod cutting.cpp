#include <iostream>
using namespace std;

int main()
{
	int p[11] = {0,1,4,5,9,10,12,15,18,19,20};
	int r[11];
	int s[11];
	r[0] = 0;
	int n = 10;
	int q;
	int c = 1;


	for (int j = 1; j <= n; j++)
	{
		q = 0;

		for (int i = 1; i <= j; i++)
		{
			if (i == j)
			{
				c = 0;
			}
			else
			{
				c = 1;
			}
			if (q < (p[i] + r[j - i]-c))
			{
				q = p[i] + r[j - i]-c;
				s[j] = i;
			}
		}

		r[j] = q;
	}

	for (int i = 1; i <= n; i++)
	{
		cout << " " << r[i];
	}
	cout << endl;
	for (int j = 1; j <= n; j++)
	{
		cout << " " << s[j];
	}


	cin>>n;
	return 0;
}
