# include<stdio.h>
# include<fstream>
# include<string>
# include<iostream>
# include<cmath>
# include<stack>
using namespace std;

int main()
{
	int base1, base2;
	string num1;
	cout << "Please enter the number's base: ";
	cin >> base1;
	cout << "Please enter the number: ";
	cin >> num1;
	cout << "Please enter the new base: ";
	cin >> base2;
	
	int num1length = num1.length();
	int numnum = num1length;
	if (num1[0] == '-'){ numnum--; }//negative value

	//int ch[20];
	int sum10 = 0;
	int power = 0;
//	cout << num1[0] << "  " << num1[1]<< numnum<<"  "<<num1length;
	for (int cur = num1length-1; numnum > 0; numnum--)
	{
		if ((num1[cur]-'0') <= 9)
		{
			sum10 += (num1[cur]-'0') * pow(base1, power);
//			cout << sum10;
		}
		else if ((num1[cur]-'0') > 9)//case of ABCDE
		{
			sum10 += (num1[cur]-55) * pow(base1, power);
//			cout << sum10;
		}
		cur--;
		power++;
	}//set sum in base 10

	// then convert from base 10 to target
//	cout << "sum is " << sum10 << endl;
	stack<int> stack;
	while (sum10 != 0)
	{
		stack.push(sum10 % base2);
		sum10 = sum10 / base2;
	}

	cout << num1 << " " << "base " << base1 << " is ";
	if (num1[0]=='-'){ cout << "-"; }
	

	while (!stack.empty())
	{
		int ch2=stack.top();
		char ch3;
		if ( ch2 > 9)
		{
			ch3 = 55+ch2;
			cout << ch3;
		}
		else
		{
			cout << ch2;
		}
		stack.pop();
	}
/*	while (!stack.empty())
	{
		cout << stack.top();
		stack.pop();
	}
*/
	cout << " " << "base " << base2<<endl;

}
