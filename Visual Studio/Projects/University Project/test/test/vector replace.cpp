#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>




using namespace std;

string addspace(string source, string s, string t)
{
	string::size_type n = 0;
	while ((n = source.find(s, n)) != string::npos)
	{
		source.replace(n, s.size(), t);
		n += t.size();
	}
	return source;
}
void main1()
{
	vector<string> list;
	string str;
	bool flag = 0;

	cout << endl << "Enter the command: ";

	while (!flag)
	{
		string line;
		getline(cin, line);
		line = addspace(line, ",", " , ");
		line = addspace(line, "(", " ( ");
		line = addspace(line, ")", " ) ");
		line = addspace(line, ";", " ; ");
		stringstream ss(line);
		while (getline(ss, str, ' '))
		{
			str.erase(remove(str.begin(), str.end(), '\n'), str.end());
			for (unsigned int i = 0; i < str.size(); i++)
			{
				str.at(i) = toupper(str.at(i));
			}
			if (str == "QUIT")
			{
				flag = 1;
			}
			else if (!flag && str != "")
			{
				list.push_back(str);
			}
		}
	}


	/*	for (int i = 0; i < list.size(); i++)
	{
	for (int j = 0; j < list[i].size(); j++)
	{
	list[i].at(j) = toupper(list[i].at(j));
	}
	cout << list[i]<<endl;
	}
	*/

}