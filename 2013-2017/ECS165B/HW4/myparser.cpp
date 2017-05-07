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

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "HW4-expr.h"
using namespace std;

/*Function Prototype*/
string do_compile(expr e);

class mytable
{
public:
	vector<vector<vector<string> > > data;
	vector<string> tablename;
	vector<vector<string> > colname;
};

typedef
struct expression {
	int func;
	int count;
	union values {
		char *name;
		char *data;
		int num;
		struct expression *ep;
	} values[2];
} expression;

void printdata(mytable tables)
{
	for (int i = 0; i < tables.tablename.size(); i++)	//each table
	{
		cout << string(120,'-')<<endl;
		cout << tables.tablename.at(i) << endl;
		for (int j = 0; j < tables.colname.size(); j++)
		{
			cout << setw(15) << tables.colname.at(i).at(j);
		}
		cout << endl;

		for (int j = 0; j < tables.data.at(i).at(0).size(); j++)		//each row
		{
			for (int k = 0; k < tables.colname.size();k++)			//each column
			{
				cout << setw(15) << tables.data.at(i).at(k).at(j);
			}
			cout << endl;
		}
	}
}

string  global_err(int err)
{
	switch (err)
	{

	case 2:
		return "ERROR: < Not yet implemented >";

	case 3:
		return "ERROR: < Cannot get current path Exit program >";
	
	case 4:
		return "ERROR: < Cannot create directory Exit program >";
	
	case 5:
		return "ERROR: < Cannot open file >";
	default:
		cout << "undefined err num: " << err << endl;
		return "Not suppose to be here";
	}
}

string  define_table(int err)
{
	switch (err)
	{

	case 2:
		return "ERROR: < Invalid Command >";

	case 3:
		return "ERROR: < Invalid name syntax >";

	case 11:
		return "ERROR: < Table already exists >";

	case 12:
		return "ERROR: < Cannot create database directory >";

	case 13:
		return "ERROR: < Cannot create table >";

	case 14:
		return "ERROR: < Invalid column name >";

	case 15:
		return "ERROR: < Unknown server error >";

	default:
		cout << "undefined err num: " << err << endl;
		return "Not suppose to be here";
	}
}

mytable open_directory()
{
	struct dirent *d;
	DIR *dp;
	char datapath[1024];
	mytable tables;
	/*get current path*/
	if (getcwd(datapath, sizeof(datapath)) == NULL){ perror("error is:"); cout << global_err(3) << endl; exit(-1); }

	/*open dir*/
	strcat(datapath, "/database");
	if ((dp = opendir(datapath)) == NULL)
	{
		if (mkdir(datapath, 0777) == -1)
		{
			perror("error is:");
			cout << global_err(4) << endl ;
			exit(-1);
		}
		cout << "Creating Directory ~/database" << endl;
		dp = opendir(datapath);
	}

	/*Get table and set up data vector*/

	int tablecount = 0;

	//int rowcount = 0;
	cout << "Reading data ......" << endl;
	while ((d = readdir(dp)))
	{
		if (d->d_type == DT_REG)
		{

			int columncount = 0;
			string str = d->d_name;
			str.erase(str.find_last_of("."), string::npos);
			tables.tablename.push_back(str);
			tables.colname.push_back(vector<string>());
			tables.data.push_back(vector<vector<string> >());



			fstream fs;
			char filename[1024];
			strcpy(filename, datapath);
			strcat(filename, "/");
			strcat(filename, d->d_name);


			fs.open(filename, fstream::in);


			if (fs.is_open())
			{
				string colnames, name, values;
				getline(fs, colnames);	//read first line
				stringstream ss(colnames);
				while (getline(ss, name, '\t'))
				{
					if (name != " ")
					{
						tables.colname.at(tablecount).push_back(name);
						tables.data[tablecount].push_back(vector<string>());
						columncount++;

					}
				}
				cout << endl;

				while (getline(fs, values))
				{
					stringstream ss(values);
					for (int i = 0; i < columncount; i++)
					{
						string value;
						getline(ss, value, '\t');
						if (name != " ")
						{

							tables.data.at(tablecount).at(i).push_back(value);
						}
					}


				}

				fs.close();
				tablecount++;
			}
			else	{ perror("error is:"); cout << global_err(5) << endl << "  file name: " << d->d_name << " , Exit program" << endl; exit(-1); }	//cannot open file


		}
	}
	printdata(tables);
	cout << string(120, '-') << endl;
	cout << endl << "< " << tablecount << " tables > Readed" << endl;
	return tables;
}

expr compile(expr e)
{
	string returnstr;
	if ((returnstr = do_compile(e)) != "0")
	{
		cout << returnstr << endl;				//output error message
		e = NULL;
		return e;
	}
	return e;
}

expr evalexpr(expr e)
{
	expression *ep = (expression *)e;
	if (!ep) return e;							//pass on null ( error ) 


	print_e(e, 0);
	return e;
}

expr optimize(expr e)
{
	expression *ep = (expression *)e;
	if (!ep) return e;							//pass on null ( error ) 

		return e;

}

void print_relation(expr e)
{
}

string compile_create(expr e)
{
	//vector 
	//getparsetree(e);
	return "0";
}

string do_compile(expr e)
{
	expression *ep = (expression *)e;
	switch (ep->func)
	{
	case OP_CREATETABLE:
	{
		return compile_create(e);
	}
	default:
		string str = "ERROR < Inalid Command >";
		return str;
	}
	string str = "ERROR < Inalid expression tree >";
	return str;
}
