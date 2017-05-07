#include <stdio.h>
#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>


using namespace std;
using namespace pqxx;
string date[14];
string date14[14];


void q3a()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q3A  " << endl;
	float percentage[20];
	float partialsum[20];		
	int i = 0;
	/*for these two array <5 is at 0  <10 is at 1 so 95 at 18 100 at 19 */
	string sql;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}

	/*total daysum*/
	sql = "SELECT SUM(D) FROM "\
		"((SELECT COUNT(HOUSEID) * 30 AS D FROM(SELECT HOUSEID "\
		"FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE)AS DAY1 "\
		"WHERE (TDAYDATE LIKE \'____04\'OR TDAYDATE LIKE \'____06\'OR TDAYDATE LIKE \'____09\'OR TDAYDATE LIKE \'____11\'))AS DAY30) " \

		"UNION " \

		"(SELECT  COUNT(HOUSEID) * 31 AS D FROM(SELECT HOUSEID "\
		"FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE)AS DAY1 " \
		"WHERE (TDAYDATE LIKE \'____01\'OR TDAYDATE LIKE \'____03\'OR TDAYDATE LIKE \'____05\'OR TDAYDATE LIKE \'____7\' " \
		"OR TDAYDATE LIKE \'____8\'OR TDAYDATE LIKE \'____10\'OR TDAYDATE LIKE \'____12\'))AS DAY31) "

		"UNION " \

		" (SELECT COUNT(HOUSEID) * 29 AS D FROM(SELECT HOUSEID " \
		" FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE) AS DAY1 " \
		" WHERE  TDAYDATE LIKE \'____02\')AS DAY29))DAY29 ";

	work W(C);
	result r = (W.exec(sql));
	W.commit();
	sql.clear();
	tuple row0 = r[0];
	field col0 = row0[0];
	int totalsum = atoi(col0.c_str());
	cout << "totaldaysum: " << totalsum << endl;
	

	while (i != 20)
	{
		char add[20];
		snprintf(add, sizeof(add), "%d", i * 5 + 5);
		string add1 = string(add);
		cout << "miles is :  " << add1 << endl;

		sql = sql + "SELECT SUM(D) FROM "\
			"((SELECT COUNT(HOUSEID) * 30 AS D FROM(SELECT HOUSEID "\
			"FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE)AS DAY1 "\
			"WHERE MILESUM <=" + " " + add1 + "  AND(TDAYDATE LIKE \'____04\'OR TDAYDATE LIKE \'____06\'OR TDAYDATE LIKE \'____09\'OR TDAYDATE LIKE \'____11\'))AS DAY30) " \

			"UNION " \

			"(SELECT  COUNT(HOUSEID) * 31 AS D FROM(SELECT HOUSEID "\
			"FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE)AS DAY1 " \
			"WHERE MILESUM<=" + " " + add1 + " AND(TDAYDATE LIKE \'____01\'OR TDAYDATE LIKE \'____03\'OR TDAYDATE LIKE \'____05\'OR TDAYDATE LIKE \'____7\' " \
			"OR TDAYDATE LIKE \'____8\'OR TDAYDATE LIKE \'____10\'OR TDAYDATE LIKE \'____12\'))AS DAY31) "

			"UNION " \

			" (SELECT COUNT(HOUSEID) * 29 AS D FROM(SELECT HOUSEID " \
			" FROM(SELECT HOUSEID, PERSONID, TDAYDATE, SUM(TRPMILES)MILESUM FROM DAY  GROUP BY HOUSEID, PERSONID, TDAYDATE) AS DAY1 " \
			" WHERE MILESUM<=" + " " + add1 + " AND  TDAYDATE LIKE \'____02\')AS DAY29))DAY29 ";
		work W1(C);
		r = (W1.exec(sql));
		W1.commit();
		sql.clear();
		row0 = r[0];
		col0 = row0[0];
		partialsum[i] = atoi(col0.c_str());
		percentage[i] = (float)partialsum[i] / (float)totalsum;
		//cout << "day sum of less than " << i * 5 + 5 << " miles: " << partialsum[i] << endl;
		cout << "percentage is: " << percentage[i]*100<<" %" << endl;
		i++;
	}
	
	
	C.disconnect();
	
	
	
	
}
void q3b()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q3B  " << endl;
	double average[20];
	double partialmd[20];
	double partialmde[20];

	int i = 0;
	/*for these two array <5 is at 0  <10 is at 1 so 95 at 18 100 at 19 */
	string sql,sql1;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}

	/*theta join DAY and VEH*/
	sql = " SELECT * INTO Q3B "\
		"FROM( "\
		"DAY "\
		"NATURAL JOIN "\
		"VEH)TOT "\
		"WHERE VEHID>=1 AND TRPMILES>0 AND DRVR_FLG=1  ";

	work W(C);
	result r = (W.exec(sql));
	W.commit();
	sql.clear();
	cout << "Q3b created successfully" << endl;

	while (i != 20)
	{
		char add[20];
		snprintf(add, sizeof(add), "%d", i * 5 + 5);
		string add1 = string(add);
		cout << "miles is :  " << add1 << endl;

		/*sum with miles and days*/
		sql = sql + "SELECT(T30.SUM30 + T31.SUM31 + T28.SUM28)AS TOL "\
			"FROM "\
			"(SELECT SUM(D)SUM30 "\
			"FROM "\
			"(SELECT TRPMILES * 30 AS D "\
			"FROM(SELECT TRPMILES FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____04'OR TDAYDATE LIKE '____06'OR TDAYDATE LIKE '____09'OR TDAYDATE LIKE '____11'))AS D30)AS DD30)AS T30, "\
			"(SELECT SUM(D)SUM31 "\
			"FROM "\
			"(SELECT TRPMILES * 31 AS D "\
			"FROM(SELECT TRPMILES FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____01'OR TDAYDATE LIKE '____03'OR TDAYDATE LIKE '____05'OR TDAYDATE LIKE '____7' "\
			"OR TDAYDATE LIKE '____8'OR TDAYDATE LIKE '____10'OR TDAYDATE LIKE '____12'))AS D31)AS DD31)AS T31, "\
			"(SELECT SUM(D)SUM28 "\
			"FROM "\
			"(SELECT TRPMILES * 28 AS D "\
			"FROM(SELECT TRPMILES FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____02'))AS D28)AS DD28)AS T28 ";

		/*sum with miles days and epatmpg*/
		sql1 = sql1 + "SELECT(T30.SUM30 + T31.SUM31 + T28.SUM28)AS TOL "\
			"FROM "\
			"(SELECT SUM(D)SUM30 "\
			"FROM "\
			"(SELECT EPATMPG*TRPMILES * 30 AS D "\
			"FROM(SELECT TRPMILES,EPATMPG FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____04'OR TDAYDATE LIKE '____06'OR TDAYDATE LIKE '____09'OR TDAYDATE LIKE '____11'))AS D30)AS DD30)AS T30, "\
			"(SELECT SUM(D)SUM31 "\
			"FROM "\
			"(SELECT EPATMPG*TRPMILES * 31 AS D "\
			"FROM(SELECT TRPMILES,EPATMPG FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____01'OR TDAYDATE LIKE '____03'OR TDAYDATE LIKE '____05'OR TDAYDATE LIKE '____7' "\
			"OR TDAYDATE LIKE '____8'OR TDAYDATE LIKE '____10'OR TDAYDATE LIKE '____12'))AS D31)AS DD31)AS T31, "\
			"(SELECT SUM(D)SUM28 "\
			"FROM "\
			"(SELECT EPATMPG*TRPMILES * 28 AS D "\
			"FROM(SELECT TRPMILES,EPATMPG FROM Q3B WHERE TRPMILES<=" + " " + add1 + "  AND(TDAYDATE LIKE '____02'))AS D28)AS DD28)AS T28 ";

		work W1(C);
		result r1 = (W1.exec(sql));
		W1.commit();
		sql.clear();

		work W2(C);
		result r2 = (W2.exec(sql1));
		W2.commit();
		sql1.clear();

		tuple row0 = r1[0];
		field col0 = row0[0];
		partialmd[i] = atof(col0.c_str());

		row0 = r2[0];
		col0 = row0[0];
		partialmde[i] = strtod(col0.c_str(),NULL);
		//cout << "string is :" << col0.c_str() << endl;
		average[i] = partialmde[i] / partialmd[i];
		//cout << "summd: " << partialmd[i] << " summde: "<<partialmde[i]<<endl;
		cout << "average is: " << average[i]  << endl;
		i++;
	}


	C.disconnect();

	
}
void q3c()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q3C  " << endl;
	double percentage[14];
	double top[14];
	double bot[14];
	string date[14];
	int i = 0;

	/*for these two array <5 is at 0  <10 is at 1 so 95 at 18 100 at 19 */
	string sql, sql1;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}

	sql = "SELECT YYYYMM, TRANSPORTATION INTO TMP "\
		"FROM T2 "\
		"WHERE MSN LIKE \'TEACEUS\'";

	work W(C);
	result r = (W.exec(sql));
	W.commit();
	sql.clear();
	cout << "TMP created successfully" << endl;


	date[0] = "200803";
	date[1] = "200804";
	date[2] = "200805";
	date[3] = "200806";
	date[4] = "200807";
	date[5] = "200808";
	date[6] = "200809";
	date[7] = "200810";
	date[8] = "200811";
	date[9] = "200812";
	date[10] = "200901";
	date[11] = "200902"; 
	date[12] = "200903";
	date[13] = "200904";

	while (i != 14)
	{
		sql1 =sql1+ "SELECT SUM(TRANSPORTATION) "+
			"FROM TMP "+
			"WHERE YYYYMM LIKE \'" + date[i] + "\'";

		work W1(C);
		result r1 = (W1.exec(sql1));
		W1.commit();
		sql1.clear();

		tuple row0 = r1[0];
		field col0 = row0[0];
		bot[i] = 1000000*strtod(col0.c_str(), NULL); /*unit in million*/
		i++;
	}
	
	/*create table Q3C*/
	sql1 = "SELECT C1.TDAYDATE, C1.C, TEMP.TOLGALLON, C1.DAYS, (TOLGALLON*DAYS /C*117538000)AS TOTCO2 INTO Q3C "\
		"FROM "\
		"(SELECT * FROM(SELECT SUM(TOLGALLON1)AS TOLGALLON, TDAYDATE FROM(SELECT TDAYDATE, HOUSEID, (SUM(TRPMILES / EPATMPG)*0.008887) AS TOLGALLON1  FROM Q3B "\
		/*"WHERE TDAYDATE LIKE \'200803\' OR TDAYDATE LIKE \'200804\' OR TDAYDATE LIKE \'200805\' OR TDAYDATE LIKE \'200806\' "\
		"OR TDAYDATE LIKE \'200807\' OR TDAYDATE LIKE \'200808\' OR TDAYDATE LIKE \'200809\' OR TDAYDATE LIKE \'200810\' "\
		"OR TDAYDATE LIKE \'200811\' OR TDAYDATE LIKE \'200812\' OR TDAYDATE LIKE \'200901\' OR TDAYDATE LIKE \'200902\' "\
		"OR TDAYDATE LIKE \'200903\' OR TDAYDATE LIKE \'200904\' "\*/
		"GROUP BY TDAYDATE, HOUSEID)AS TOT GROUP BY TDAYDATE)AS TEMP1)AS TEMP "\
		"JOIN(SELECT * FROM "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE '200803' "\
		"GROUP BY TDAYDATE)AS T803) TT803 UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200804\' "\
		"GROUP BY TDAYDATE)AS T804) UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200805\' "\
		"GROUP BY TDAYDATE)AS T805)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200806\' "\
		"GROUP BY TDAYDATE)AS T806)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200807\' "\
		"GROUP BY TDAYDATE)AS T807)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200808\' "\
		"GROUP BY TDAYDATE)AS T808)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200809\' "\
		"GROUP BY TDAYDATE)AS T809)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200810\' "\
		"GROUP BY TDAYDATE)AS T810)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200811\' "\
		"GROUP BY TDAYDATE)AS T811)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200812\' "\
		"GROUP BY TDAYDATE)AS T812)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200901\' "\
		"GROUP BY TDAYDATE)AS T901)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 28 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200902\' "\
		"GROUP BY TDAYDATE)AS T902)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200903\' "\
		"GROUP BY TDAYDATE)AS T903)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'200904\' "\
		"GROUP BY TDAYDATE)AS T904))C1 ON C1.TDAYDATE = TEMP.TDAYDATE "\
		"ORDER BY C1.TDAYDATE ";
	work W1(C);
	result r1 = (W1.exec(sql1));
	W1.commit();
	sql1.clear();
	
	cout << "Table Q3C created successfully" << endl;

	/*fetch bot data*/
	sql1 = "SELECT TOTCO2 FROM Q3C";
	work W2(C);
	result r2 = (W2.exec(sql1));
	W2.commit();
	sql1.clear();

	i = 0;
	while (i != 14)
	{
		tuple row1 = r2[i];
		field col1 = row1[0];
		top[i] = strtod(col1.c_str(), NULL);
		top[i] = top[i];
		percentage[i] = top[i] / bot[i];
		//cout << "bot is " << bot[i] << endl;
		cout << "Month: " << date[i] << " percentage : " << percentage[i] * 100 << "%" << endl;
		i++;
	}
	C.disconnect();
}
void q3d()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q3D  " << endl;
	int i = 0; /*THREE VALUE*/
	string sql, sql1;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}

	sql = "SELECT TT1.YYYYMM, (TT1.ELECTRICITY/TT2.MKWH) AS CO2PKWH INTO Q3DCO2 FROM "\
		"(SELECT YYYYMM, ELECTRICITY  FROM T1  "\
		"WHERE MSN LIKE \'TXEIEUS\' AND (YYYYMM LIKE \'200803\' OR YYYYMM LIKE \'200804\' OR YYYYMM LIKE \'200805\' OR YYYYMM LIKE \'200806\' OR YYYYMM LIKE \'200807\' OR YYYYMM LIKE \'200808\' OR YYYYMM LIKE \'200809\' OR YYYYMM LIKE \'200810\' OR YYYYMM LIKE \'200811\' OR YYYYMM LIKE \'200812\' OR YYYYMM LIKE \'200901\' OR YYYYMM LIKE \'200902\' OR YYYYMM LIKE \'200903\' OR YYYYMM LIKE \'200904\' ))AS TT1, "\
		"(SELECT YYYYMM, MKWH  FROM T3  "\
		"WHERE MSN LIKE \'ELETPUS\' AND (YYYYMM LIKE \'200803\' OR YYYYMM LIKE \'200804\' OR YYYYMM LIKE \'200805\' OR YYYYMM LIKE \'200806\' OR YYYYMM LIKE \'200807\' OR YYYYMM LIKE \'200808\' OR YYYYMM LIKE \'200809\' OR YYYYMM LIKE \'200810\' OR YYYYMM LIKE \'200811\' OR YYYYMM LIKE \'200812\' OR YYYYMM LIKE \'200901\' OR YYYYMM LIKE \'200902\' OR YYYYMM LIKE \'200903\' OR YYYYMM LIKE \'200904\' ))AS TT2 "\
		"WHERE TT1.YYYYMM = TT2.YYYYMM ";
		
	work W(C);
	result r = (W.exec(sql));
	W.commit();
	sql.clear();
	cout << "create q3dco2 successfully " << endl;
	while (i != 3)
	{
		int columnnum = 0;
		char add[20];
		snprintf(add, sizeof(add), "%d", (i+1)*20);
		string miles = string(add);
		sql = sql + " SELECT (T8.TOTCO2 - T8.TOTCO2NOW)/T8.TOTCO2 AS DIFFERENCE    FROM "\
			"(SELECT T7.TDAYDATE, (T7.GASCO2 + T7.ECO2)AS TOTCO2NOW, T7.TOTCO2    FROM "\
			"(SELECT T6.TDAYDATE, SUM(T6.CO2)AS ECO2, SUM(T6.GCO2*0.008887)AS GASCO2, T6.TOTCO2  FROM "\
			"(SELECT T5.HOUSEID, T5.VEHID, T5.TDAYDATE, (T5.ELECO2 / Q3C.C * 117538000 * Q3C.DAYS)AS CO2, (T5.GASMILE / T5.EPATMPG / Q3C.C * 117538000 * Q3C.DAYS)AS GCO2, Q3C.TOTCO2   FROM Q3C, "\
			"(SELECT T4.HOUSEID, T4.VEHID, T4.TDAYDATE, (KWH*Q3DCO2.CO2PKWH)AS ELECO2, T4.GASMILE, T4.ELEMILE, T4.EPATMPG FROM Q3DCO2, "\
			"(SELECT *  FROM "\
			"((SELECT HOUSEID,VEHID, TDAYDATE, (" + " " + miles + "/ MPKWH)AS KWH, (TOTMIL - " + " " + miles + ")AS GASMILE, " + " " + miles + " AS ELEMILE, EPATMPG FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, SUM(TRPMILES)AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1 GROUP BY HOUSEID, VEHID, TDAYDATE, MPKWH, EPATMPG)T2 "\
			"WHERE TOTMIL >= " + " " + miles + "))T3 "\
			"UNION "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, (TOTMIL / MPKWH)AS KWH, 0AS GASMILE, TOTMIL AS ELEMILE, EPATMPG  FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, SUM(TRPMILES)AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1 GROUP BY HOUSEID, VEHID, TDAYDATE, MPKWH, EPATMPG)T2 "\
			"WHERE TOTMIL <= " + " " + miles + " AND TOTMIL>0))AS T4 "\
			"WHERE Q3DCO2.YYYYMM = T4.TDAYDATE)AS T5 "\
			"WHERE T5.TDAYDATE = Q3C.TDAYDATE)AS T6 "\
			"GROUP BY TDAYDATE, TOTCO2)AS T7)AS T8 ";
		work W3(C);
		result r3 = (W3.exec(sql));
		W3.commit();
		sql.clear();
		cout << "Range is : " << miles << endl;
		while (columnnum != 14)
		{
			tuple row0 = r3[columnnum];
			field col0 = row0[0];
			cout << "For month: " << date[columnnum] << " discrepancy is : " << strtod(col0.c_str(), NULL) * 100 << "%" << endl;
			columnnum++;
		}
		i++;
	}
	C.disconnect();
}
void q5a()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q5A  " << endl;
	int mile[4] = { 84, 107, 208, 270 };
	int i = 0;
	string sql;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
	while (i != 4)
	{
		int columnnum = 0;
		char add[20];
		snprintf(add, sizeof(add), "%d", mile[i]);
		string miles = string(add);
		sql = sql + " SELECT (T8.TOTCO2 - T8.TOTCO2NOW)/T8.TOTCO2 AS DIFFERENCE   FROM "\
			"(SELECT T7.TDAYDATE, (T7.GASCO2 + T7.ECO2)AS TOTCO2NOW, T7.TOTCO2    FROM "\
			"(SELECT T6.TDAYDATE, SUM(T6.CO2)AS ECO2, SUM(T6.GCO2*0.008887)AS GASCO2, T6.TOTCO2  FROM "\
			"(SELECT T5.HOUSEID, T5.VEHID, T5.TDAYDATE, (T5.ELECO2 / Q3C.C * 117538000 * Q3C.DAYS)AS CO2, (T5.GASMILE / T5.EPATMPG / Q3C.C * 117538000 * Q3C.DAYS)AS GCO2, Q3C.TOTCO2   FROM Q3C, "\
			"(SELECT T4.HOUSEID, T4.VEHID, T4.TDAYDATE, (KWH*Q3DCO2.CO2PKWH)AS ELECO2, T4.GASMILE, T4.ELEMILE, T4.EPATMPG FROM Q3DCO2, "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, SUM(KWH)AS KWH, SUM(GASMILE)AS GASMILE, SUM(ELEMILE)AS ELEMILE, EPATMPG  FROM "\
			"(((SELECT HOUSEID, VEHID, TDAYDATE, 0 AS KWH, (TOTMIL)AS GASMILE, 0 AS ELEMILE, EPATMPG FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1)T2 "\
			"WHERE TOTMIL > " + " "+miles +")) "\
			"UNION ALL"\
			"(SELECT HOUSEID, VEHID, TDAYDATE, (TOTMIL / MPKWH)AS KWH, 0 AS GASMILE, TOTMIL AS ELEMILE, EPATMPG  FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1)T2 "\
			"WHERE TOTMIL < " + " " + miles + " AND TOTMIL>0))AS TT4 GROUP BY HOUSEID, VEHID, TDAYDATE, EPATMPG)AS T4 "\
			"WHERE Q3DCO2.YYYYMM = T4.TDAYDATE)AS T5 "\
			"WHERE T5.TDAYDATE = Q3C.TDAYDATE)AS T6 "\
			"GROUP BY TDAYDATE, TOTCO2)AS T7)AS T8 ";
		work W3(C);
		result r3 = (W3.exec(sql));
		W3.commit();
		sql.clear();
		cout << "Range is : " << mile[i] << endl;
		while (columnnum != 14)
		{
			tuple row0 = r3[columnnum];
			field col0 = row0[0];
			cout << "For month: " << date[columnnum] << " discrepancy is : " << strtod(col0.c_str(), NULL) * 100 << "%" << endl;
			columnnum++;
		}
		i++;
	}
	C.disconnect();
}
void q5b()
{
	cout << endl << endl << string(40,'-')<<endl << "BELOW IS Q5B  " << endl;
	int mile[4] = { 84, 107, 208, 270 };

	int i = 0;
	string sql,sql1;
	string nv = "Not Available";
	connection C("dbname=postgres user=haozhe26");
	if (C.is_open()) {
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else {
		cout << "Can't open database" << endl;

	}
		
	sql = "SELECT TT1.YYYYMM, (TT1.ELECTRICITY/TT2.MKWH) AS CO2PKWH INTO Q5B FROM "\
		"(SELECT YYYYMM, ELECTRICITY  FROM T1  "\
		"WHERE MSN LIKE \'NNEIEUS\' AND (YYYYMM LIKE \'201401\' OR YYYYMM LIKE \'201402\' OR YYYYMM LIKE \'201403\' OR YYYYMM LIKE \'201405\' OR YYYYMM LIKE \'201406\' OR YYYYMM LIKE \'201407\' OR YYYYMM LIKE \'201408\' OR YYYYMM LIKE \'201409\' OR YYYYMM LIKE \'201410\' OR YYYYMM LIKE \'201411\' OR YYYYMM LIKE \'201412\' OR YYYYMM LIKE \'201404\'))AS TT1, "\
		"(SELECT YYYYMM, SUM(MKWH)AS MKWH  FROM T3  "\
		"WHERE (MSN LIKE \'WYETPUS\'OR MSN LIKE \'NGETPUS\'OR  MSN LIKE \'NUETPUS\') AND (YYYYMM LIKE \'201401\' OR YYYYMM LIKE \'201402\' OR YYYYMM LIKE \'201403\' OR YYYYMM LIKE \'201405\' OR YYYYMM LIKE \'201406\' OR YYYYMM LIKE \'201407\' OR YYYYMM LIKE \'201408\' OR YYYYMM LIKE \'201409\' OR YYYYMM LIKE \'201410\' OR YYYYMM LIKE \'201411\' OR YYYYMM LIKE \'201412\' OR YYYYMM LIKE \'201404\' )GROUP BY YYYYMM )AS TT2 "\
		"WHERE TT1.YYYYMM = TT2.YYYYMM ";

	work W(C);
	result r = (W.exec(sql));
	W.commit();
	sql.clear();
	cout << "create Q5B successfully " << endl;

	/*add two row set to according 


	sql = sql+ "INSERT INTO Q5B(YYYYMM,CO2PKWH) VALUES(\'" + date14[12] + "\', (SELECT CO2PKWH FROM Q5B WHERE YYYYMM = \'201403\')); "\
		"INSERT INTO Q5B(YYYYMM,CO2PKWH) VALUES(\'" + date14[13] + "\', (SELECT CO2PKWH FROM Q5B WHERE YYYYMM = \'201404\')); ";
	work W1(C);
	result r1 = (W1.exec(sql));
	W1.commit();
	sql.clear();
	cout << "add new time successfully" << endl;*/

	while (i != 14)
	{

			sql = sql + "UPDATE Q3B "\
				"SET TDAYDATE = \'" + date14[i] + "\' "\
				"WHERE TDAYDATE = \'" + date[i] + "\';";
		work W2(C);
		result r2 = (W2.exec(sql));
		W2.commit();
		sql.clear();
		i++;
	}
	i = 0;

	sql1 = "SELECT C1.TDAYDATE, C1.C, TEMP.TOLGALLON, C1.DAYS, (TOLGALLON*DAYS /C*117538000)AS TOTCO2 INTO Q5D "\
		"FROM "\
		"(SELECT * FROM(SELECT SUM(TOLGALLON1)AS TOLGALLON, TDAYDATE FROM(SELECT TDAYDATE, HOUSEID, (SUM(TRPMILES / EPATMPG)*0.008887) AS TOLGALLON1  FROM Q3B "\
		"GROUP BY TDAYDATE, HOUSEID)AS TOT GROUP BY TDAYDATE)AS TEMP1)AS TEMP "\
		"JOIN(SELECT * FROM "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE '201403' "\
		"GROUP BY TDAYDATE)AS T803) TT803 UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201404\' "\
		"GROUP BY TDAYDATE)AS T804) UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201405\' "\
		"GROUP BY TDAYDATE)AS T805)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201406\' "\
		"GROUP BY TDAYDATE)AS T806)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201407\' "\
		"GROUP BY TDAYDATE)AS T807)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201408\' "\
		"GROUP BY TDAYDATE)AS T808)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201409\' "\
		"GROUP BY TDAYDATE)AS T809)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201410\' "\
		"GROUP BY TDAYDATE)AS T810)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 30 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201411\' "\
		"GROUP BY TDAYDATE)AS T811)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201412\' "\
		"GROUP BY TDAYDATE)AS T812)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 31 AS DAYS FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201401\' "\
		"GROUP BY TDAYDATE)AS T901)UNION "\
		"(SELECT * FROM(SELECT TDAYDATE, COUNT(DISTINCT HOUSEID)AS C, 28 AS DAYS  FROM Q3B "\
		"WHERE TDAYDATE LIKE \'201402\' "\
		"GROUP BY TDAYDATE)AS T902))C1 ON C1.TDAYDATE = TEMP.TDAYDATE "\
		"ORDER BY C1.TDAYDATE ";
	work W1(C);
	result r1 = (W1.exec(sql1));
	W1.commit();
	sql1.clear();
	cout << "Change month number successfully" << endl;

	/*change 3c to 5c*/
	
	while (i != 4)
	{
		int columnnum = 0;
		char add[20];
		snprintf(add, sizeof(add), "%d", mile[i]);
		string miles = string(add);
		sql = sql + "SELECT (T8.TOTCO2 - T8.TOTCO2NOW)/T8.TOTCO2 AS DIFFERENCE  FROM "\
			"(SELECT T7.TDAYDATE, (T7.GASCO2 + T7.ECO2)AS TOTCO2NOW, T7.TOTCO2    FROM "\
			"(SELECT T6.TDAYDATE, SUM(T6.CO2)AS ECO2, SUM(T6.GCO2*0.008887)AS GASCO2, T6.TOTCO2  FROM "\
			"(SELECT T5.HOUSEID, T5.VEHID, T5.TDAYDATE, (T5.ELECO2 / Q5D.C * 117538000 * Q5D.DAYS)AS CO2, (T5.GASMILE / T5.EPATMPG / Q5D.C * 117538000 * Q5D.DAYS)AS GCO2, Q5D.TOTCO2   FROM Q5D, "\
			"(SELECT T4.HOUSEID, T4.VEHID, T4.TDAYDATE, (KWH*Q5B.CO2PKWH)AS ELECO2, T4.GASMILE, T4.ELEMILE, T4.EPATMPG FROM Q5B, "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, SUM(KWH)AS KWH, SUM(GASMILE)AS GASMILE, SUM(ELEMILE)AS ELEMILE, EPATMPG  FROM "\
			"(((SELECT HOUSEID, VEHID, TDAYDATE, 0 AS KWH, (TOTMIL)AS GASMILE, 0 AS ELEMILE, EPATMPG FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1)T2 "\
			"WHERE TOTMIL > " + " " + miles + ")) "\
			"UNION ALL"\
			"(SELECT HOUSEID, VEHID, TDAYDATE, (TOTMIL / MPKWH)AS KWH, 0 AS GASMILE, TOTMIL AS ELEMILE, EPATMPG  FROM "\
			"(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES AS TOTMIL, MPKWH, EPATMPG "\
			"FROM(SELECT HOUSEID, VEHID, TDAYDATE, TRPMILES, (3 / 33.1*EPATMPG)AS MPKWH, EPATMPG FROM Q3B)T1)T2 "\
			"WHERE TOTMIL < " + " " + miles + " AND TOTMIL>0))AS TT4 GROUP BY HOUSEID, VEHID, TDAYDATE, EPATMPG)AS T4 "\
			"WHERE Q5B.YYYYMM = T4.TDAYDATE)AS T5 "\
			"WHERE T5.TDAYDATE = Q5D.TDAYDATE)AS T6 "\
			"GROUP BY TDAYDATE, TOTCO2)AS T7)AS T8 ";
		work W3(C);
		result r3 = (W3.exec(sql));
		W3.commit();
		sql.clear();
		cout << "Range is : " << mile[i] << endl;
		while (columnnum != 12)
		{
			tuple row0 = r3[columnnum];
			field col0 = row0[0];
			cout << "For month: " << date14[columnnum] << " discrepancy is : " << strtod(col0.c_str(), NULL)*100<<"%" << endl;
			columnnum++;
		}
		
		i++;
	}
	C.disconnect();
}
void set_date()
{
	date[0] = "200803";
	date[1] = "200804";
	date[2] = "200805";
	date[3] = "200806";
	date[4] = "200807";
	date[5] = "200808";
	date[6] = "200809";
	date[7] = "200810";
	date[8] = "200811";
	date[9] = "200812";
	date[10] = "200901";
	date[11] = "200902";
	date[12] = "200903";
	date[13] = "200904";

	date14[0] = "201403";
	date14[1] = "201404";
	date14[2] = "201405";
	date14[3] = "201406";
	date14[4] = "201407";
	date14[5] = "201408";
	date14[6] = "201409";
	date14[7] = "201410";
	date14[8] = "201411";
	date14[9] = "201412";
	date14[10] = "201401";
	date14[11] = "201402";
	date14[12] = "201403";
	date14[13] = "201404";
}
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
		q = "Drop Table Q3B; ";
		q += "Drop Table TMP; ";
		q += "Drop Table Q3C; ";
		q += "Drop Table Q5B;";
		q += "Drop Table Q3DCO2;";
		q+="Drop Table Q5D;";
		work W(C);
		result R(W.exec(q));
		W.commit();
	}
	catch (invalid_argument &e)
	{
		cout << "NEVER GOT HERE";
	}
	cout << "TABLE dropped" << endl;
	C.disconnect();
}

int main(int argc, char* argv[])
{
	
	set_date();
	//drop_tables();
	q3a();/*Question 3 a*/
	q3b();/*Question 3 b*/
	q3c();/*Question 3 c*/
	q3d();/*Question 3 d*/
	q5a();/*Question 5 a*/
	q5b();/*Question 5 b*/
}