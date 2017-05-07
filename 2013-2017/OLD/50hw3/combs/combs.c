#include "combs.h"
#include <stdio.h>
#include <stdlib.h>

/*int* comb(int* items, int* data, int start, int end, int index, int k);

int** get_combs(int* items, int k, int len)
{
	int num, i;
	num = num_combs(len, k);
	int** arr = (int**)malloc(num * sizeof(int*));
	for (i = 0; i < num; i++)
	{
		arr[i] = (int*)malloc(k * sizeof(int));
		arr[i] = comb(items, arr[i], 0, len-1, 0, k);

	}
	return arr;
}

int* comb(int* items, int* data, int start, int end, int index, int k)
{
	int i;
	if (index == k)
	{
		return data;
	}

	for (i = start; i <= end && end-i+1 >= k - index; i++)
	{
		data[index] = items[i];
		data = comb(items, data, i+1, end, index+1, k);
	}
}

*/

//---------------------------------------------------------------------
// version 2
// failed
/*
int** get_combs(int* items, int k, int len)
{
	int i, j, z, temp, skip, start, count = 0, num;
	int** row = (int**)malloc(num_combs(len, k) * sizeof(int*));

	num = num_combs(len, k);
	printf("num = %d\n", num);

	for (i = 0; i < len; i++)
	{
		start = i;
		if (start + k > len)
		{
			break;
		}
		else
		{

			for (j = 0; j < (len-(k-1)-start) && count < num_combs(len, k);j++, count++) 
			{
				skip = j;
				//int* row = (int*)malloc(k * sizeof(int));
				for (z = 0; z < len-1; z++)
				{
					//row[count][z] = items[start+z];
					row[z] = items[start+z];
				}
				row[count][k-1] = items[start+(k-1)+skip];

				for (temp = 0; temp < k; temp++)
				{
					printf("%d ", row[count][temp]);
				}
				printf("\n");
				printf("count = %d\n", count);
			}
		}
	}
	return row;
}

*/

/* ------------------------------------------------------------------
	version 3
*/
int comb(int* items, int** ass, int* row, int start, int n, int k, int maxk, int count);


int** get_combs(int* items, int k, int len)
{
	int i;
	int** shit = (int**)malloc(num_combs(len, k) * sizeof(int*));
	for (i = 0; i < num_combs(len, k); i++)
	{
		shit[i] = (int*)malloc(k * sizeof(int));
	}
	int* row = (int*)malloc(k*sizeof(int));
	comb(items, shit, row, 0, len, 0, k, 0);
	return shit;
}

int comb(int* items, int** ass, int* row, int start, int n, int k, int maxk, int count)
{
	int i;
	if (k + 1 > maxk)
	{

		for (i = 0; i < maxk; i++)
		{
			//printf("%d", row[i]);
			ass[count][i] = row[i];
		}
		//printf("\n");

		//printf("count = %d\n", count);
		count++;
		return count;
	}

	for (i = start; i < n; i++)
	{
		row[k] = items[i];
		count = comb(items, ass, row, i+1, n, k+1, maxk, count);
	}
	return count;
}

















