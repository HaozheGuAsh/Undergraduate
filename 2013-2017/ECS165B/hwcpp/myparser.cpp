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
class mytable
{
public:
	vector<vector<vector<string> > > data;
	vector<string> tablename;
	vector<vector<string> > colname;
};

class data_create
{
public:
	string tablename;
	vector<string>colname;
};

class data_insert
{
public:
	string tablename;
	vector<string>values;
};

class logicnode
{
public:
	vector< expression *> left;
	vector< expression *> right;
	int type;
};
class connection_node
{
public:
	logicnode * left;
	logicnode * right;
	int type;
};

class projection_tree
{
public:
	vector<vector<expression*> > in;
	vector<expression*> out;
};
class data_select
{
public:
	string tablename;
	vector<vector<string> >data;
	vector<string>allcol;
	vector<string>outcol;
	vector<expression *> tree;
	vector<connection_node> exprtree;
	projection_tree projtree;
};



/*global*/
extern mytable tables;
extern data_create createdata;
extern char datapath[1024];
extern data_insert insertdata;
extern data_select selectdata;

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

void printdata(mytable tables)
{
	for (int i = 0; i < tables.tablename.size(); i++)	//each table
	{
		cout << string(120,'-')<<endl;
		cout << tables.tablename.at(i) << endl;
		for (int j = 0; j < tables.colname.at(i).size(); j++)
		{
			cout << setw(15) << tables.colname.at(i).at(j);
		}
		cout << endl;

		for (int j = 0; j < tables.data.at(i).at(0).size(); j++)		//each row
		{
			for (int k = 0; k < tables.colname.at(i).size();k++)			//each column
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

string define_table(int err)
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

string define_table(expr e)
{
	/*update data in memory*/
	unsigned tableindex = tables.tablename.size();
	tables.tablename.push_back(createdata.tablename);
	tables.colname.push_back(vector<string>());
	tables.data.push_back(vector<vector<string> >());

	/*create file*/
	char filename[1024];
	strcpy(filename, datapath);
	strcat(filename, "/");
	strcat(filename, createdata.tablename.c_str());
	strcat(filename, ".tbl");
	ofstream myfile(filename, ofstream::out | ofstream::app | ofstream::in);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < createdata.colname.size(); i++)
		{
			myfile << createdata.colname.at(i);
			myfile << '\t';
			tables.colname.at(tableindex).push_back(createdata.colname.at(i));
			tables.data[tableindex].push_back(vector<string>());
		}
		myfile << endl;
		myfile.close();
	}
	else { return define_table(13); }
	return "0";
}

string insert_row(int err)
{
	switch (err)
	{

	case 2:
		return "ERROR: < Invalid Command >";

	case 3:
		return "ERROR: < Invalid name syntax >";

	case 21:
		return"ERROR: < Table does not exists >";

	case 22:
		return "ERROR: < Too many values >";

	case 23:
		return "ERROR: < Too few values >";

	case 24:
		return "ERROR: < Unknown server error >";

	case 25:
		return "ERROR: < Invalid column name >";

	default:
		cout << "undefined err num: " << err << endl;
		return "Not suppose to be here";
	}
}

string insert_row(expr e)
{
	//cout << "in insert" << endl;
	vector<string>::iterator tableptr = findtable(insertdata.tablename);
	unsigned tableindex = tableptr - tables.tablename.begin();

	/*write to file*/
	char filename[1024];
	strcpy(filename, datapath);
	strcat(filename, "/");
	strcat(filename, insertdata.tablename.c_str());
	strcat(filename, ".tbl");
	ofstream myfile(filename, ofstream::out | ofstream::app);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < insertdata.values.size(); i++)
		{
			myfile << insertdata.values.at(i);
			myfile << '\t';
			tables.data.at(tableindex).at(i).push_back(insertdata.values.at(i));
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

string fetch_rows(expr e)
{
	return "0";
}

void open_directory()
{
	struct dirent *d;
	DIR *dp;
	char datapath[1024];
	
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
	//cout << "end compile" << endl;
	return e;
}

expr evalexpr(expr e)
{
	//cout << "In evalexpr" << endl;
	string err;
	expression *ep = (expression *)e;
	if (!ep) {  return e; }							//pass on null ( error ) 
	
	switch (ep->func)
	{
	case OP_CREATETABLE:
	{
		if ((err = define_table(e)) != "0") cout << err << endl;
		break;
	}
	case OP_INSERTROW:
	{
		if ((err = insert_row(e)) != "0") cout << err << endl;
		break;
	}
	case OP_PROJECTION:
	{
		if ((err = fetch_rows(e)) != "0") cout << err << endl;
		break;
	}
	default: cout << "Should not be here" << endl; break;
	}
	//cout << "evalexpr end" << endl;
	
	return e;
}

expr optimize(expr e)
{
	//cout << "In optimize" << endl;
	expression *ep = (expression *)e;
	if (!ep) {return e; }						//pass on null ( error ) 
	return e;
}

void print_relation(expr e)
{
}

string flat_tree_create(expr e)
{
	string err;
	expression *ep = (expression *)e;

	if (!ep) return"0";
	
	switch (ep->func)
	{
	case OP_TABLENAME:	createdata.tablename = ep->values[0].name; return"0";
	case OP_COLNAME:	 createdata.colname.push_back(ep->values[0].name); return"0";
	case OP_GROUP: return global_err(2);
	case OP_PRODUCT: return global_err(2);
	case OP_SORT: return global_err(2);
	default: break;
	}
	if ((err = flat_tree_create(ep->values[0].ep)) != "0") return err;
	if ((err = flat_tree_create(ep->values[1].ep)) != "0") return err;
	return err;
}

string flat_tree_insert(expr e)
{
	string err;
	//cout << "in flat tree" << endl;
	expression *ep = (expression *)e;

	if (!ep) return"0";

	switch (ep->func)
	{
	case OP_TABLENAME:	insertdata.tablename = ep->values[0].name; return"0";
	case OP_STRING:
	{
		string str = ep->values[0].name;
		str.erase(str.begin());
		str.erase(str.end()-1);
		insertdata.values.push_back(str);
		return"0";
	}
	case OP_NUMBER:
	{
		string str = to_string(ep->values[0].num);
		insertdata.values.push_back(str);
		return "0";
	}
	/*case OP_NULL:
	{
		string str = "null";
		insertdata.values.push_back(str);
		return "0";
	}*/
	case OP_GROUP: cout << "here" << endl; return global_err(2);
	case OP_PRODUCT: cout << "here1" << endl; return global_err(2);
	case OP_SORT: cout << "here2" << endl; return global_err(2);
	default: break;
	}
	if ((err = flat_tree_insert(ep->values[0].ep)) != "0") return err;
	if ((err = flat_tree_insert(ep->values[1].ep)) != "0") return err;
	return err;
}

string check_column_select(expr e)
{
	string err;
	//cout << "in flat tree select " << endl;
	expression *ep = (expression *)e;

	if (!ep) return"0";

	switch (ep->func)
	{
	case OP_TABLENAME:	selectdata.tablename = ep->values[0].name; return"0";
	case OP_STRING:		return"0";
	case OP_NUMBER:		return"0";
	case OP_COLNAME:
	{
		selectdata.allcol.push_back(ep->values[0].name);
		return "0";
	}
	case OP_OUTCOLNAME:
	{
		selectdata.outcol.push_back(ep->values[1].name);
		break;
	}

	/*case OP_NULL:
	{
		string str = "null";
		insertdata.values.push_back(str);
		return "0";
	}*/
	case OP_GROUP:  return global_err(2);
	case OP_PRODUCT:  return global_err(2);
	case OP_SORT:  return global_err(2);
	default: break;
	}
	if ((err = check_column_select(ep->values[0].ep)) != "0") return err;
	if ((err = check_column_select(ep->values[1].ep)) != "0") return err;
	return err;
}

string transform_select (expr e)
{
	string err="0";
	int flag = 0;
	expression *ep = (expression *)e;

	

	if (!ep) return"0";


	switch (ep->func)
	{
	case OP_TABLENAME:	return"0";
	case OP_STRING:		return"0";
	case OP_NUMBER:		return"0";
	case OP_COLNAME:	return"0";
	case OP_OUTCOLNAME:	selectdata.tree.push_back(ep); selectdata.tree.push_back(ep->values[1].ep); break;
	case OP_EQUAL: case OP_NOTEQ: case OP_LEQ: case OP_GEQ: case OP_LT: case OP_GT: case OP_AND: case OP_OR: case OP_NOT:
	case OP_PLUS: case OP_BMINUS: case OP_TIMES: case OP_DIVIDE: case OP_UMINUS: 
	{
		flag = 1;
		break;
	}

	case OP_GROUP: cout << "here" << endl; return global_err(2);
	case OP_PRODUCT: cout << "here1" << endl; return global_err(2);
	case OP_SORT: cout << "here2" << endl; return global_err(2);
	default: break;
	}
	if ((err = transform_select(ep->values[0].ep)) != "0") return err;
	if ((err = transform_select(ep->values[1].ep)) != "0") return err;
	if (flag == 1)
	{
		//cout << "in transform tree select,func : " << ep->func << endl;
		//cout << "in arithmetic" << endl;
		if ((ep->values[0].ep->func == 90) || (ep->values[0].ep->func == 91) || (ep->values[0].ep->func == 52))
		{
			//cout << ep->values[0].ep->func << endl;
			selectdata.tree.push_back(ep->values[0].ep);
		}
	//	cout << ep->func << endl;
		selectdata.tree.push_back(ep);
		if ((ep->values[1].ep->func == 90) || (ep->values[1].ep->func == 91) || (ep->values[1].ep->func == 52))
		{
			//cout << ep->values[1].ep->func << endl;
			selectdata.tree.push_back(ep->values[1].ep);
		}
		flag = 0;
	}
	return err;
}

void setup_tree_select()
{
	int conn_count = 0;
	int connlr = 0;
	int logiclr = 0;
	selectdata.exprtree.push_back(connection_node());
	for (int i = 0; selectdata.tree.at(i)->func != OP_OUTCOLNAME; i++)
	{
		switch (selectdata.tree.at(i)->func)
		{
		case OP_NUMBER: case OP_COLNAME: case OP_STRING:
		{
			if (connlr == 0)
			{
				//selectdata.exprtree.at(conn_count).left->left.
			}
		}
		}
	}
}
string compile_select(expr e)
{
	//cout << "in compile" << endl;
	string err;
	expression *ep = (expression *)e;
	selectdata.data.clear();
	selectdata.tablename.clear();

	/*CHECK ERROR*/
	/* CHECK COLUMN */
	if ((err = check_column_select(e)) != "0"){ return err; }
	//cout << "check finish (select)" << endl;
	
	/*transform tree*/
	transform_select(e);
	//cout << "transform finish(select)" << endl;
	/*setup mytree*/
	for (int i = 0; i < selectdata.tree.size(); i++)
	{
		//cout << selectdata.tree.at(i)->func << endl;
	}
	setup_tree_select();
	//cout << "finish setup select tree" << endl;

	/*GET DATA FROM FILE*/
	if ((findtable(selectdata.tablename) == tables.tablename.end())){ return fetch_rows(33); }
	vector<string>::iterator tableptr = findtable(selectdata.tablename);
	unsigned tableindex = tableptr - tables.tablename.begin();
	fstream fs;
	char filename[1024];
	strcpy(filename, datapath);
	strcat(filename, "/");
	strcat(filename, selectdata.tablename.c_str());
	strcat(filename, ".tbl");
	//cout << filename;
	fs.open(filename, fstream::in);
	int colcount=tables.colname.at(tableindex).size();
	if (fs.is_open())
	{
		string colnames, name, values;
		getline(fs, colnames);	//read first line
		stringstream ss(colnames);
		//cout << endl;
		for (int i = 0; i < colcount; i++) selectdata.data.push_back(vector<string>()); //push  cols

		while (getline(fs, values))//for each row
		{
			stringstream ss(values);
			for (int i = 0; i < colcount; i++)
			{
				string value;
				getline(ss, value, '\t');
				if (name != " ")
				{
					//cout << setw(10) << "value is :" << setw(10) << value << "		";
					selectdata.data.at(i).push_back(value);
				}
			}
			//cout << endl;
		}

		fs.close();
	}

	

	//cout << "return 0 in compile select" << endl;
	return "0";
}

string compile_insert(expr e)
{
	//cout << "in compile" << endl;
	string err;
	expression *ep = (expression *)e;
	insertdata.values.clear();
	insertdata.tablename.clear();

	/* GET ITEM IN TREE */
	if ((err = flat_tree_insert(e)) != "0"){ return err; }
	reverse(insertdata.values.begin(), insertdata.values.end());
	//cout << "Table name: " << insertdata.tablename << endl;
	//for (int i = 0; i < insertdata.values.size(); i++) cout << "value " << i << "  is: " << insertdata.values.at(i) << endl;

	//cout << "checking err" << endl;
	/*CHECK ERROR*/

	/*if table not exist*/
	if ((findtable(insertdata.tablename) == tables.tablename.end())){ return insert_row(21); }
	
	/*check column size*/
	vector<string>::iterator tableptr = findtable(insertdata.tablename);
	unsigned tableindex = tableptr - tables.tablename.begin();
	unsigned colsize = tables.colname.at(tableindex).size();

	if (colsize < insertdata.values.size())
	{
		return insert_row(22);
	}
	else if (colsize > insertdata.values.size())
	{
		return insert_row(23);
	}

	//cout << "return 0 in compile insert" << endl;
	return "0";
}

string compile_create(expr e)
{
	string err;
	expression *ep = (expression *)e;
	createdata.colname.clear();
	createdata.tablename.clear();

	/* GET ITEM IN TREE */
	if ((err = flat_tree_create(e)) != "0"){ return err; }
	reverse(createdata.colname.begin(), createdata.colname.end());
	//cout << "Table name: " << createdata.tablename<<endl;
	//for (int i = 0; i < createdata.colname.size(); i++) cout << "column " << i << "  is: " << createdata.colname.at(i) <<endl;


	/*CHECK ERROR*/

	/*if table already exist*/
	//cout << createdata.tablename << endl;
	//for (int i = 0; i < tables.tablename.size(); i++)cout << "has: " << tables.tablename.at(i) << endl;
	if ((findtable(createdata.tablename)) != tables.tablename.end()){ return define_table(11); }

	/*if column name duplicated*/
	vector<string> temp = createdata.colname;
	sort(temp.begin(), temp.end());
	vector<string>::iterator it;
	it = unique(temp.begin(), temp.end());
	if (it != temp.end()){ return define_table(14); }

	//cout << "return 0 in compile create"<<endl;
	return "0";
}

string do_compile(expr e)
{
	expression *ep = (expression *)e;
	print_e(e, 0);
	switch (ep->func)
	{
	case OP_CREATETABLE:
	{
		return compile_create(e);
	}
	case OP_INSERTROW:
	{
		return compile_insert(e);
	}
	case OP_PROJECTION:
	{
		return compile_select(e);
	}
	default:
		cout << "op is :"<<ep->func << endl;
		string str = "ERROR < Inalid Command >";
		return str;
	}
	string str = "ERROR < Inalid expression tree >";
	return str;
}
