#include<iostream>
using namespace std;
void combination( int ar[], int n,  int k)
{
	unsigned int finished = 0;
	unsigned int changed = 0;
	unsigned int i;


		for (i = k - 1; !finished && !changed; i--) 
		{
			if (ar[i] < (n - 1) - (k - 1) + i)
			{
				/* Increment this element */
				ar[i]++;
				if (i < k - 1) 
				{
					/* Turn the elements after it into a linear sequence */
					unsigned int j;
					for (j = i + 1; j < k; j++)
					{
						ar[j] = ar[j - 1] + 1;
					}
				}
				changed = 1;
			}
			if (i == 0){ finished = 0; }
			
		}
		for (int i = 0; i < k; i++)
			{
				cout << ar[i] << " ";
			}
		cout << endl;
		if (!changed)
		{
			/* Reset to first combination */
			for (i = 0; i < k; i++) {
				ar[i] = i;
			}
		}
	
	
}

int main()
{
	int arr[5] = { 0,1,2,3,4 };
	cout << "0 1 2" << endl;
	for (int i = 0; i < 9;i++)
	{ combination(arr,5,3);}
	
}

