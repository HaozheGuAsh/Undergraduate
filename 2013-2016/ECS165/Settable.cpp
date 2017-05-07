

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
	try
	{
		q = "Drop Table T1; ";
		q += "Drop Table T2; ";
		q += "Drop Table T3; ";
		q += "Drop Table DAY; ";
		q += "Drop Table VEH; ";

		work W(C);
		result R(W.exec(q));
		W.commit();
	}
	catch (invalid_argument &e)
	{
		cout << "NEVER GOT HERE";
	}
	cout << "T1 T2 T3 T4 DAY VEH dropped" << endl;
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
		"MSN VARCHAR(15),"\
		"YYYYMM VARCHAR(15),"\
		"ELECTRICITY FLOAT(50));";

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
				//cout << table_3[5004] << "should be 144.746" << endl;
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
		"MSN VARCHAR(15),"\
		"YYYYMM VARCHAR(15),"\
		"TRANSPORTATION FLOAT(50));";

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
				//cout << table_3[6672] << "should be 159.074" << endl;
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
		"MSN VARCHAR(15),"\
		"YYYYMM VARCHAR(15),"\
		"MKWH FLOAT(50));";

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
				//cout << table_3[7540] << "should be 312796.858" << endl;
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
void create_table_day()
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
	sql = "CREATE TABLE DAY("\
		"HOUSEID INT,"\
		"PERSONID INT,"\
		"DRVR_FLG INT,"\
		"VEHID INT,"\
		"TDAYDATE VARCHAR(15),"\
		"TRPMILES FLOAT(50));";

	work W(C);
	result R(W.exec(sql));
	W.commit();

	fstream fs;
	string line;
	vector<string> table_1(10000);
	vector<string> table_2(10000);
	vector<string> table_3(10000);
	vector<string> table_4(10000);
	vector<string> table_5(10000);
	vector<string> table_6(10000);
	int row = 1;
	string l;
	fs.open("DAYV2PUB.CSV", fstream::in);
	if (fs.is_open())
	{
		int col = 1;
		getline(fs, line);
		while (getline(fs, l))
		{
			stringstream ss(l);

			while (getline(ss, line, ','))
			{
				if (col == 1)	/*HOUSEID*/
				{

					table_1[row] = line;

				}
				if (col == 2)	/*PERSONID*/
				{

					table_2[row] = line;

				}
				if (col == 39)	/*DRVR_FLG*/
				{

					table_6[row] = line;

				}
				if (col == 84)	/*VEHID*/
				{

					table_3[row] = line;

				}
				if (col == 94)	/*TDAYDATE*/
				{

					table_4[row] = line;

				}
				if (col == 95)	/*TRPMILES*/
				{

					table_5[row] = line;

				}
				col++;
			}

			row++;
			col = 1;
			if (row == 1001)
			{
				for (int i = 1; i <= 1000; i++)
				{
					q = q + "INSERT INTO DAY(HOUSEID,PERSONID,VEHID,DRVR_FLG,TDAYDATE,TRPMILES)" + " "
						+ "VALUES(" + table_1[i] + "," + table_2[i] + "," + table_3[i] + "," + table_6[i] + ","+
						table_4[i] + "," + table_5[i] + ");";
				}
				work W1(C);
				result Q(W1.exec(q));
				W1.commit();
				q.clear();
				row = 1;
			}
		}
		fs.close();
	}


	cout << "Table DAY created successfully" << endl;
	C.disconnect();
}
void create_table_veh()
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
	sql = "CREATE TABLE VEH("\
		"HOUSEID INT,"\
		"VEHID INT,"\
		"EPATMPG FLOAT(50));";

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
	fs.open("VEHV2PUB.CSV", fstream::in);
	if (fs.is_open())
	{
		int col = 1;
		getline(fs, line);
		while (getline(fs, l))
		{
			stringstream ss(l);

			while (getline(ss, line, ','))
			{
				if (col == 1)	/*HOUSEID*/
				{

					table_1[row] = line;

				}
				if (col == 3)	/*VEHID*/
				{

					table_2[row] = line;

				}
				if (col == 56)	/*EPATMPG*/
				{

					table_3[row] = line;

				}
				col++;
			}

			row++;
			col = 1;
			if (row == 1001)
			{
				for (int i = 1; i <= 1000; i++)
				{
					q = q + "INSERT INTO VEH(HOUSEID,VEHID,EPATMPG)" + " " + 
						"VALUES(" + table_1[i] + "," + table_2[i] + "," + table_3[i] + ");";
				}
				work W1(C);
				result Q(W1.exec(q));
				W1.commit();
				q.clear();
				row = 1;
			}
		}
		fs.close();
	}


	cout << "Table VEH created successfully" << endl;
	C.disconnect();
}
int main(int argc, char* argv[])
{
	//drop_tables();
	create_table1();	/*EIA Electricity*/
	create_table2();	/*EIA Transportation*/
	create_table3();	/*EIA MKWH*/
	
	create_table_day();	/*DAYV2PUB*/
	create_table_veh();	/*VEHV2PUB*/

}
















