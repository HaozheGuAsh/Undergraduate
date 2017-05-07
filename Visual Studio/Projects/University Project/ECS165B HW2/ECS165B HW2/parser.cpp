/*Haozhe Gu 999200555*/

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



using namespace std;

/*prototype*/
void parse();
int invalid_command();
bool valid_identifier(string str);
void open_directory();

class mytable
{
public:
	vector<vector<vector<string> > > data;
	vector<string> tablename;
	vector<vector<string> > colname;
};
/*global*/
vector<string> list;
vector<string> lower;
mytable tables;
char datapath[1024];

/*void alarm_handler(int sig)
{
	cout << "End input after 10 seconds idle" << endl;
	streambuf* orig = std::cin.rdbuf();
	istringstream input("QUIT");
	flag = 1;
	cin.rdbuf(input.rdbuf());

}*/

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
string addallspace(string line)
{
	line = addspace(line, ",", " , ");
	line = addspace(line, "(", " ( ");
	line = addspace(line, ")", " ) ");
	line = addspace(line, ";", " ; ");
	line = addspace(line, "=", " = ");
	return line;
}
void scan()
{
	string str;
	bool flag = 0;
	//list.clear();
//	cout << list.size();
	cout <<endl<< "------------------------------------------------------" << endl<< "Enter the command: ";
	
	while (!flag)
	{
		string line;
		getline(cin, line);
		line = addallspace(line);
		stringstream ss(line);
		while (getline(ss, str, ' '))
		{
			str.erase(remove(str.begin(), str.end(), '\n'), str.end());
			if (!flag && str != "")
			{
				lower.push_back(str);
				for (unsigned int i = 0; i < str.size(); i++)
				{
					str.at(i) = toupper(str.at(i));
				}
				list.push_back(str);
				//cout << str << "  ";
				if (str == ";")
				{
					flag = 1;
				}
			}
		}
	}
	parse();

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

void advance()
{
	if (list.size()!=0)
	{
		if (list.size() > 1)
		{
			list.erase(list.begin());
			lower.erase(lower.begin());
		}
		else
		{
			list.clear();
			lower.clear();
		}
	}
	else
	{
		cout << "List is empty while advancing" << endl;
		exit(-1);
	}
}

int invalid_command(int err)
{
	/*always return err:2  get back to parse() for further operation*/
	//cout << "Invalid Command! " << endl;
	if (list.size()!=0)
	{
		while (list.front() != ";")//find next ; for invalid command
		{
			advance();
			if (list.size() == 0)
			{
				cout << "Exception: no semicolon found" << endl;
				return err;
			}
			
		}
		advance();		//pop ;
	}

	return err;
}

int mustbe(string str,int err)
{
	if (list.empty()) return invalid_command(2);
	if (list.front() != str)
	{
		return invalid_command(err);
	}
	else
	{
		advance();
		return 0;
	}
}

bool isdigit(string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str.at(i))){ return 0; }
	}
	return 1;
}

int  mustbevar()
{
	if (list.empty()) return invalid_command(2);
	if (!valid_identifier(list.front())) return invalid_command(3);
	return 0;
}

int  mustbeval()
{
	string str;
	if (list.empty()) return invalid_command(2);

	if ((!valid_identifier(list.front())) && (!isdigit(list.front()))){ return invalid_command(3); }
	return 0;
}

bool valid_identifier(string str)
{
	for (unsigned i = 0; i < str.size(); i++)
	{
		if (i == 0)
		{
			if (!((str.at(i) >= 64 && str.at(i) <= 90) || str.at(i) == 95 || str.at(i) == 35))
			{

				return 0;
			}
		}
		else
		{
			if (!((str.at(i) >= 64 && str.at(i) <= 90) || (str.at(i) >= 48 && str.at(i) <= 57) || str.at(i) == 95 || str.at(i) == 35 || str.at(i) == 36))
			{

				return 0;
			}
		}
	}
	return 1;
}

vector<string>::iterator findtable(string tablename)
{
	vector<string>::iterator it;
	it = find(tables.tablename.begin(), tables.tablename.end(), tablename);
	return it;
}

vector<string>::iterator findcolumn(int tableindex, string colname)
{
	vector<string>::iterator it;
	it = find(tables.colname.at(tableindex).begin(), tables.colname.at(tableindex).end(), colname);
	return it;
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

string  define_table(string tablename, unsigned size, vector<string> columnname)
{
	/*if table already exist*/
	if ((findtable(tablename)) != tables.tablename.end()){ return define_table(11); }

	/*update data in memory*/
	unsigned tableindex = tables.tablename.size();
	tables.tablename.push_back(tablename);
	tables.colname.push_back(vector<string>());
	tables.data.push_back(vector<vector<string> >());

	/*if column name duplicated*/
	sort(columnname.begin(), columnname.end());
	vector<string>::iterator it;
	it = unique(columnname.begin(), columnname.end());
	if (it != columnname.end()){ return define_table(14); }

	/*create file*/
	char filename[1024];
	strcpy(filename, datapath);
	strcat(filename, "/");
	strcat(filename, tablename.c_str());
	strcat(filename, ".tbl");
	ofstream myfile(filename, ofstream::out | ofstream::app|ofstream::in);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < size; i++)
		{
			myfile << columnname.at(i);
			myfile << '\t';
			tables.colname.at(tableindex).push_back(columnname.at(i));
			tables.data[tableindex].push_back(vector<string>());
		}
		myfile << endl;
		myfile.close();
	}
	else { return define_table(13); }
	return "0";
}

string  insert_row(int err)
{
	switch (err)
	{

	case 2:
		return "ERROR: < Invalid Command >" ;

	case 3:
		return "ERROR: < Invalid name syntax >";

	case 21:
		return"ERROR: < Table does not exists >";

	case 22:
		return "ERROR: < Too many values >" ;

	case 23:
		return "ERROR: < Too few values >" ;

	case 24:
		return "ERROR: < Unknown server error >" ;

	case 25:
		return "ERROR: < Invalid column name >";

	default:
		cout << "undefined err num: " << err << endl;
		return "Not suppose to be here" ;
	}
}

string insert_row(string tablename, unsigned size, vector<string> values)
{
	/*if table not exist*/
	if ((findtable(tablename)) == tables.tablename.end()){ return insert_row(21); }

	/*check column size*/
	vector<string>::iterator tableptr = findtable(tablename);
	unsigned tableindex = tableptr - tables.tablename.begin();
	unsigned colsize = tables.colname.at(tableindex).size();

	if (colsize < size)
	{
		return insert_row(22);
	}
	else if (colsize > size)
	{
		return insert_row(23);
	}

	/*write to file*/
	char filename[1024];
	strcpy(filename, datapath);
	strcat(filename, "/");
	strcat(filename, tablename.c_str());
	strcat(filename, ".tbl");
	ofstream myfile(filename,ofstream::out|ofstream::app);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < size; i++)
		{
			myfile << values.at(i);
			myfile << '\t';
			tables.data.at(tableindex).at(i).push_back(values.at(i));
		}
		myfile << endl;
		myfile.close();
	}
	else { return insert_row(24); }
	return "0";
}

string fetch_rows(int err)
{
	{
		switch (err)
		{

		case 2:
			return "ERROR: < Invalid Command >";

		case 3:
			return "ERROR: < Invalid name syntax >";

		case 31:
			return"ERROR: < Output column does not exists >";

		case 32:
			return "ERROR: < Column used in WHERE clause does not exist >";

		case 33:
			return "ERROR: < Table does not exist >";

		case 34:
			return "ERROR: < Unknown server error >";

		case 35:
			return "ERROR: < Invalid column name >";

		default:
			cout << "undefined err num: " << err << endl;
			return "Not suppose to be here";
		}
	}
}

string fetch_rows(string tablename, vector<string> projection, vector<string> condition)
{
	/*if table not exist*/
	if ((findtable(tablename)) == tables.tablename.end()){ return fetch_rows(33); }
	
	/*setup projection */
	vector<string>::iterator tableptr = findtable(tablename);
	unsigned tableindex = tableptr - tables.tablename.begin();
	vector<string> outcol;
	vector<int>outcolindex;
	for (unsigned i = 0; i < projection.size(); i++)
	{
		vector<string>::iterator colptr = findcolumn(tableindex, projection.at(i));
		if (colptr != tables.colname.at(tableindex).end())
		{
			unsigned colindex = colptr - tables.colname.at(tableindex).begin();
			outcol.push_back(*colptr);
			outcolindex.push_back(colindex);
		}
		else{ return fetch_rows(31); }
	}
    

	/*setup rows*/
	vector<vector<string> > cols;
	for (unsigned i = 0; i < outcol.size(); i++)
	{
		cols.push_back(tables.data.at(tableindex).at(outcolindex.at(i)));
	}

	/*set up where condition */
	vector<string>variable; 
	vector<string>values;
	for (unsigned i = 0; i < condition.size(); i++)
	{
		vector<string>::iterator colptr = findcolumn(tableindex, condition.at(i));
		if (colptr == tables.colname.at(tableindex).end()){ return fetch_rows(32); }

		variable.push_back(condition.at(i));
		
		i++;

		values.push_back(condition.at(i));
		
	}
	/*doing where condition*/
	cout << endl << endl;
	for (unsigned i = 0; i < projection.size(); i++)		//project column
	{
		cout << setw(8) << projection.at(i) << "	";
	}
	cout << endl;

	int rowfetch = 0;
	int differflag = 0;
	
	for (unsigned i = 0;i< tables.data.at(tableindex).at(0).size(); i++)				//	i is each row
	{
		//cout << "here1";
		for (unsigned j = 0; j < tables.colname.at(tableindex).size(); j++)			// j is each column
		{
			//cout << "here2";
			for (unsigned k = 0; k < variable.size(); k++)	//compare with each constraint
			{
				if ((variable.at(k) == tables.colname.at(tableindex).at(j)) && (tables.data.at(tableindex).at(j).at(i) != values.at(k)))		// var in where but different value, dont print
				{
					differflag = 1;
				}
			}
		}

		if (differflag == 0)
		{
			for (unsigned l = 0; l < cols.size(); l++)			// l is each column
			{
				cout << setw(8) << cols.at(l).at(i) << "	";
			}
			cout << endl;
			rowfetch++;
		}
		else
		{
			differflag = 0;
		}
		
	}
	cout << endl << endl;
	cout << "< " << rowfetch << " rows > Fetched" << endl;

	
	return "0";
}

string parse_create()
{
	string tablename;
	vector<string> columnname;
	int err;

	if ((err = mustbe("CREATE", 2)) != 0){ return define_table(err); }
	if ((err = mustbe("TABLE", 2)) != 0){ return define_table(err); }

	
	if ((err = mustbevar()) != 0){ return define_table(err); }
	tablename = list.front();
	advance();

	if ((err = mustbe("(", 2)) != 0){ return define_table(err); }


	if ((err = mustbevar()) != 0){ return define_table(err); }
	while (list.front() != ")")
	{
		if ((err = mustbevar()) != 0){ return define_table(err); }
		columnname.push_back(list.front());
		advance();

		if (list.front() != ")" && list.at(1)!=")")			//not the last column
		{
			if ((err = mustbe(",", 2)) != 0){ return define_table(err); }
		}
	}

	if ((err = mustbe(")", 2)) != 0){ return define_table(err); }
	if ((err = mustbe(";", 2)) != 0){ return define_table(err); }

	return define_table(tablename, columnname.size(), columnname);

}

string parse_insert()
{
	string tablename;
	vector<string> columnname;
	int err;

	if ((err = mustbe("INSERT", 2)) != 0){ return insert_row(err); }
	if ((err = mustbe("INTO", 2)) != 0){ return insert_row(err); }

	if ((err = mustbevar()) != 0){ return insert_row(err); }
	tablename = list.front();
	advance();

	if ((err = mustbe("VALUES", 2)) != 0){ return insert_row(err); }
	if ((err = mustbe("(", 2)) != 0){ return insert_row(err); }


	if ((err = mustbeval()) != 0){ return insert_row(err); }
	while (list.front() != ")")
	{
		if ((err = mustbeval()) != 0){ return insert_row(err); }
		columnname.push_back(lower.front());
		advance();

		if (list.front() != ")" && list.at(1) != ")")			//not the last column
		{
			if ((err = mustbe(",", 2)) != 0){ return insert_row(err); }
		}
	}

	if ((err = mustbe(")", 2)) != 0){ return insert_row(err); }
	if ((err = mustbe(";", 2)) != 0){ return insert_row(err); }

	return insert_row(tablename, columnname.size(), columnname);
}

string parse_select()
{
	vector<string> projection, condition;
	string tablename;
	int err;

	if ((err = mustbe("SELECT", 2)) != 0){ return fetch_rows(err); }

	
	if ((err = mustbevar()) != 0){ return fetch_rows(err); }
	while (list.front() != "FROM")
	{
		if ((err = mustbevar()) != 0){ return fetch_rows(err); }
		projection.push_back(list.front());
		advance();

		if (list.front() != "FROM" && list.at(1) != "FROM")			//not the last column
		{
			if ((err = mustbe(",", 2)) != 0){ return fetch_rows(err); }
		}
	}


	if ((err = mustbe("FROM", 2)) != 0){ return fetch_rows(err); }
	if ((err = mustbevar()) != 0){ return fetch_rows(err); }
	tablename = list.front();
	advance();

	if ((err = mustbe("WHERE", 2)) != 0){ return fetch_rows(err); }

	if ((err = mustbevar()) != 0){ return fetch_rows(err); }
	while (list.front() != ";")
	{
		if ((err = mustbevar()) != 0){ return fetch_rows(err); }
		condition.push_back(list.front());
		advance();

		if ((err = mustbe("=", 2)) != 0){ return fetch_rows(err); }

		if ((err = mustbeval()) != 0){ return fetch_rows(err); }
		condition.push_back(lower.front());
		//cout << "condition" << lower.front();
		advance();

		if (list.front() != ";" && list.at(1) != ";")			//not the last column
		{
			if ((err = mustbe("AND", 2)) != 0){ return fetch_rows(err); }
		}
	}

//	cout << "From parse, condition :" << condition.size() << endl;
	if ((err = mustbe(";", 2)) != 0){ return fetch_rows(err); }

	return fetch_rows(tablename, projection, condition);



}

void open_directory()
{
	struct dirent *d;
	DIR *dp;

	/*get current path*/
	if (getcwd(datapath, sizeof(datapath)) == NULL){ perror("error is:"); cout << define_table(15) << endl << "Cannot get current path Exit program" << endl; exit(-1); }

	/*open dir*/
	strcat(datapath, "/database");
	if ((dp = opendir(datapath)) == NULL)
	{
		if (mkdir(datapath, 0777) == -1)
		{
			perror("error is:");
			cout << define_table(12) << endl << "Cannot create directory Exit program" << endl;
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
		if (d -> d_type == DT_REG)
		{
			cout << endl << endl << endl;
			int columncount = 0;
			string str = d->d_name;
			str.erase(str.find_last_of("."), string::npos);
			tables.tablename.push_back(str);
			tables.colname.push_back(vector<string>());
			tables.data.push_back(vector<vector<string> >());
			cout << "tablename: " << str << endl;


			fstream fs;
			char filename[1024];
			strcpy(filename,datapath);
			strcat(filename, "/");
			strcat(filename, d->d_name);


			fs.open(filename, fstream::in);
			

			if (fs.is_open())
			{
				string colnames, name,values;
				getline(fs, colnames);	//read first line
				stringstream ss(colnames);
				while (getline(ss, name, '\t'))
				{
					if (name != " ")
					{
						tables.colname.at(tablecount).push_back(name);
						tables.data[tablecount].push_back(vector<string>());
						columncount++;
						cout << setw(10) << "columnname: " << setw(10) << name << "		";
					}
				}
				cout << endl;

				while (getline(fs,values))
				{
					stringstream ss(values);
					for ( int i = 0; i < columncount; i++)
					{
						string value;
						getline(ss, value, '\t');
						if (name != " ")
						{
							cout << setw(10) << "value is :" << setw(10) << value << "		";
							tables.data.at(tablecount).at(i).push_back(value);
						}
					}
					cout << endl;

				}
					
				fs.close();
				tablecount++;
			}
			else	{ perror("error is:"); cout << define_table(15) << endl << "Cannot open file: " <<  d->d_name << " , Exit program" << endl; exit(-1); }	//cannot open file
			
			
		}
	}
	cout << endl << "< " << tablecount << " tables > Readed" << endl;

}

void parse()
{
//	char ch;

		if (list.front() == "CREATE")
		{
			string returnstr=parse_create();
			if (returnstr != "0"){ cout << returnstr << endl; }
			scan();
		}
		else if (list.front() == "INSERT")
		{
			string returnstr=parse_insert();
			if (returnstr != "0"){ cout << returnstr << endl; }
			scan();
		}
		else if (list.front() == "SELECT")
		{
			string returnstr = parse_select();
			if (returnstr != "0"){ cout << returnstr << endl; }
			scan();
		}
		else if (list.front() == "QUIT")
		{
			advance();
			if (mustbe(";", 2) != 0)
			{
				cout << "ERROR: < Invalid Command >" << endl;
				scan();
			}
			else
			{
				cout << "No more input, terminate the program" << endl;
			}
		}
		else
		{
			invalid_command(2);	// begin with wrong keyword
			cout << "ERROR: < Invalid Command >" << endl;
			scan();
		}
	

/*	cout <<endl<<"Enter ; to stop,other char to continue."<<endl<<"Make sure input buffer is clear"<<endl<<
		 "Do you have more input?";
	cin >> ch;
	if (ch != ';')
	{
        cout << endl << "Entered: " << ch << "   Continue..." << endl;
		cout << "------------------------------------------------------" << endl;
        scan();
	}
	else
	{
		cout << endl << "Entered: " << ch << "   No more input, terminate the program" << endl;
		exit(0);
	}*/
}

int main()
{

	open_directory();
	scan();
	
}


	