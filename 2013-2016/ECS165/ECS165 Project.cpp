//
//  ECS165 Project.cpp
//  
//
//  Created by AshGu on 16/3/8.
//
//

#include <stdio.h>
#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using namespace pqxx;


void drop_tables()
{
	string q;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	q = "Drop Table T1; ";
	q += "Drop Table T2; ";
	q += "Drop Table T3; ";
	q += "Drop Table T4; ";
	work W(C);
	result R(W.exec(q));
	W.commit();
	cout << "T1 T2 T3 T4 dropped" << endl;
	C.disconnect();
}
void create_table1()
{
	string sql, q;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	sql = "CREATE TABLE T1("\
		"MSN CHAR(15),"\
		"YYYYMM CHAR(15),"\
		"ELECTRICITY INT);";

	work W(C);
	result R(W.exec(sql));
	W.commit();

	fstream fs;
	string line;
	vector<string> table_1(10000);
	vector<string> table_2(10000);
	vector<string> table_3(10000);
	int row = 1;
	string l;
	fs.open("EIA_CO2_Electricity_2015.csv", fstream::in);
	if (fs.is_open())
	{
		int col = 1;
		getline(fs, line);
		while (getline(fs, l))
		{
			stringstream ss(l);

			while (getline(ss, line, ','))
			{
				if (col == 1)
				{

					table_1[row] = line;

				}
				if (col == 2)
				{

					table_2[row] = line;

				}
				if (col == 3)
				{
					if (line.compare(nv)) {
						table_3[row] = line;

					}
					else {
						table_3[row] = "NULL";

					}
				}
				col++;
			}

			row++;
			col = 1;
			if (row == 5005)
			{
				cout << table_3[5004] << "should be 144.746" << endl;
				break;
			}
		}
		fs.close();
	}
	for (int i = 1; i <= 5004; i++)
	{
		q = q + " " + "INSERT INTO T1(MSN,YYYYMM,ELECTRICITY)" + " " + "VALUES(\'" + table_1[i] + "\'," + table_2[i] + "," + table_3[i] + ");";



	}
	work W1(C);
	result Q(W1.exec(q));
	W1.commit();
	cout << "Table1 created successfully" << endl;
	C.disconnect();
}
void create_table2()
{
	string sql, q;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	sql = "CREATE TABLE T2("\
		"MSN CHAR(15),"\
		"YYYYMM CHAR(15),"\
		"TRANSPORTATION INT);";

	work W(C);
	result R(W.exec(sql));
	W.commit();

	fstream fs;
	string line;
	vector<string> table_1(10000);
	vector<string> table_2(10000);
	vector<string> table_3(10000);
	int row = 1;
	string l;
	fs.open("EIA_CO2_Transportation_2015.csv", fstream::in);
	if (fs.is_open())
	{
		int col = 1;
		getline(fs, line);
		while (getline(fs, l))
		{
			stringstream ss(l);

			while (getline(ss, line, ','))
			{
				if (col == 1)
				{

					table_1[row] = line;

				}
				if (col == 2)
				{

					table_2[row] = line;

				}
				if (col == 3)
				{
					if (line.compare(nv)) {
						table_3[row] = line;

					}
					else {
						table_3[row] = "NULL";

					}
				}
				col++;
			}

			row++;
			col = 1;
			if (row == 6673)
			{
				cout << table_3[6672] << "should be 159.074" << endl;
				break;
			}
		}
		fs.close();
	}
	for (int i = 1; i <= 6672; i++)
	{
		q = q + " " + "INSERT INTO T2(MSN,YYYYMM,TRANSPORTATION)" + " " + "VALUES(\'" + table_1[i] + "\'," + table_2[i] + "," + table_3[i] + ");";



	}
	work W1(C);
	result Q(W1.exec(q));
	W1.commit();
	cout << "Table2 created successfully" << endl;
	C.disconnect();
}
void create_table3()
{
	string sql, q;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	sql = "CREATE TABLE T3("\
		"MSN CHAR(15),"\
		"YYYYMM CHAR(15),"\
		"MKWH INT);";

	work W(C);
	result R(W.exec(sql));
	W.commit();

	fstream fs;
	string line;
	vector<string> table_1(10000);
	vector<string> table_2(10000);
	vector<string> table_3(10000);
	int row = 1;
	string l;
	fs.open("EIA_MkWh_2015.csv", fstream::in);
	if (fs.is_open())
	{
		int col = 1;
		getline(fs, line);
		while (getline(fs, l))
		{
			stringstream ss(l);

			while (getline(ss, line, ','))
			{
				if (col == 1)
				{

					table_1[row] = line;

				}
				if (col == 2)
				{

					table_2[row] = line;

				}
				if (col == 3)
				{
					if (line.compare(nv)) {
						table_3[row] = line;

					}
					else {
						table_3[row] = "NULL";

					}
				}
				col++;
			}

			row++;
			col = 1;
			if (row == 7541)
			{
				cout << table_3[7540] << "should be 312796.858" << endl;
				break;
			}
		}
		fs.close();
	}
	for (int i = 1; i <= 7540; i++)
	{
		q = q + " " + "INSERT INTO T3(MSN,YYYYMM,MKWH)" + " " + "VALUES(\'" + table_1[i] + "\'," + table_2[i] + "," + table_3[i] + ");";



	}
	work W1(C);
	result Q(W1.exec(q));
	W1.commit();
	cout << "Table3 created successfully" << endl;
	C.disconnect();
}
void outerjoin123()
{
	string sql;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	sql = "SELECT* INTO T4 FROM((T1 NATURAL FULL OUTER JOIN T2)AS N1 NATURAL FULL OUTER JOIN T3) AS N2 WHERE TRUE";

	work W(C);
	result R(W.exec(sql));
	W.commit();
	cout << "Table T4 created successful"<<endl;
	C.disconnect();

}
int main(int argc, char* argv[])
{
	drop_tables();
	create_table1();	/*EIA Electricity*/
	create_table2();	/*EIA Transportation*/
	create_table3();	/*EIA MKWH*/
	outerjoin123();		/*Outerjoin of all EIA*/


}















