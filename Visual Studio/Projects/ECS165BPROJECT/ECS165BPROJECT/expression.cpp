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
#include "errno.h"
#include <inttypes.h>
#include <fcntl.h>
//int linenum;

#include "HW6-expr.h"
//#include "HW4-expression.h"
#define MAXROWS	1000
#define PINROW	1000

/* CSIF machines refuse to accept a proper initialization, so only do it partly here */
exprnode ERROR_OUTOFNODES = { OP_ERROR, 1, 0, 0 };
void
subprint_relation(expr e);
/*****************************************************************************************************************/
/* Row Cache                                                                                  ********************/
/* NOTE:	The turnover is huge, so dont rely on automated garbage collection algorithms ********************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*global*/
int debug = 0;
extern struct mytable vectortables;
extern  char filepath[1024];
extern struct table tables[MAXTABLES];
row rowbuf[MAXROWS];
int rowexp = 0;
int rowseq = 1;
int delid = -1;

row *
rowalloc(expr x)
{
	/* nth chance clock algorithm */
	int rid, loopcnt = 0;
	do {
		rid = rowexp = (rowexp + 1) % 1000;
		if (!rid) { rid = rowexp++; loopcnt++; }
		if (rowbuf[rid].tableid == 0) {
			rowbuf[rid].rowexp = 1000;
			rowbuf[rid].tableid = MAXTABLES;
			rowbuf[rid].diskaddr = 0;
			rowbuf[rid].rowid = rowseq++;
			return rowbuf + rid;
		}
		if (rowbuf[rid].rowexp-- <= 0) {
			rowbuf[rid].rowexp = 1000;
			rowbuf[rid].tableid = MAXTABLES;
			rowbuf[rid].diskaddr = 0;
			rowbuf[rid].rowid = rowseq++;
			return rowbuf + rid;
		}
		if (rowbuf[rid].rowexp > 500)
			rowbuf[rid].rowexp = 1000;
	} while (loopcnt < 3);
	return 0;
}

void rowfree(row *rowp)
{
	rowp->rowexp = 2;
}

exprnode *getnext(exprnode*);


/******************************************************************************************************/
/* Make different kinds of expression *****************************************************************/
/******************************************************************************************************/
exprnode *
makeexprnode(int op, int cnt, exprnode *arg1, exprnode *arg2)
{
	exprnode *ep = (exprnode *)malloc(sizeof(exprnode));
	int i, size;

	ep->func = op;
	ep->count = cnt;
	ep->values[0].ep = arg1;
	ep->values[1].ep = arg2;

	return ep;
}

/* For parser */
int
makeexpr(int op, int cnt, int arg1, int arg2)
{
	return (intptr_t)makeexprnode(op, cnt, (exprnode *)arg1, (exprnode *)arg2);
}

/* Literals */
exprnode *
makenulllit()
{
	exprnode *ep = makeexprnode(OP_NULL, 0, 0, 0);
	return ep;
}

exprnode *
makenumlit(int num)
{
	exprnode *ep = makeexprnode(OP_NUMBER, 1, 0, 0);
	ep->values[0].num = num;
	return ep;
}

exprnode *
makestrlit(const char *str)
{
	exprnode *ep = makeexprnode(OP_STRING, 1, 0, 0);
	ep->values[0].data = (char *)str;
	return ep;
}

exprnode *
makeerrlit(const char *errmsg)
{
	exprnode *ep = makeexprnode(OP_ERROR, 1, 0, 0);
	ep->values[0].data = (char *)errmsg;
	return ep;
}

exprnode *
makerow(int tid)
{
	row *rowp = rowalloc(0);
	exprnode *ep = makeexprnode(OP_ROW, 1, 0, 0);
	ep->values[0].rowp = rowp;
	rowp->tableid = tid;

	return ep;
}
vector<string>::iterator findtable(string tablename)
{
	vector<string>::iterator it;
	it = find(vectortables.tablename.begin(), vectortables.tablename.end(), tablename);
	return it;
}

vector<string>::iterator findcolumn(int tableindex, string colname)
{
	vector<string>::iterator it;
	it = find(vectortables.colname.at(tableindex).begin(), vectortables.colname.at(tableindex).end(), colname);
	return it;
}

void
readcsvhdr(struct table *tp)
{
	int col, j, n, i, rn;
	char ibuf[MAXCOLS*(MAXDATA + 1)];
	char row[MAXCOLS][MAXDATA + 1];
	char filename[MAXDATA];
	int fid;

	lseek(tp->fid, 0, SEEK_SET);
	col = 0; j = 0; rn = 0;

	//printf("Init table %s...\n", tp->t_name);
	while ((i = read(tp->fid, ibuf, MAXCOLS*(MAXDATA + 1))) > 0) {
		for (n = 0; n<i; n++) {
			if (ibuf[n] == '\n') {
				if (rn == 0) {
					row[col][j] = 0;
					//printf("has last column %s...\n", row[col]);
					/* We have the header row */
					tp->colcount = col + 1;
					tp->cp = (column*)malloc((col + 1)*(MAXDATA + 1));
					if (!tp->cp) {
						printf("::readcsvhdr: Out of memory, should never happen\n");
						exit(-1);
					}
					memcpy(tp->cp, row, (col + 1)*(MAXDATA + 1));
				}
				/* Do next row */
				col = 0; j = 0; rn++;
				continue;
			}
			if (rn == 0) {
				if (ibuf[n] == '\t') {
					/* We are done with a column */
					row[col][j] = 0;
					row[col][MAXDATA] = 0;
					row[col][MAXDATA - 1] = 0;
					//printf("has column %s...\n", row[col]);
					col++; j = 0;
					continue;
				}
				row[col][j++] = ibuf[n];
			} /* We are just counting the data rows, so we dont do anything here */
		}
	}
	tp->rowcount = rn;

	/* Now that all is set up, we can mark the columns that have an index */
	strcpy(filename, filepath);
	strcat(filename, "/");
	for (i = 0; i<tp->colcount; i++) {
		strcat(filename, tp->t_name);
		strcat(filename, ".");
		strcat(filename, tp->cp[i].col_name);
		strcat(filename, ".idx");
		fid = open(filename, O_RDWR);
		if (fid > 0) {
			close(fid);
			filename[strlen(filename) - 4] = 0;
			if (debug) printf("DEBUG: %s has a B-Tree index\n", filename + 5);
			tp->cp[i].col_name[MAXDATA] = 'I';
		}
	}
}
int
opentbl(char *table_name)
{
	register int  i, j, fid = -1;
	char c;
	char fname[MAXDATA + 1];

	//printf("::opentbl: %s\n", table_name);
	/* Find the table ********************************************************************/
	strcpy(fname, filepath);
	strcat(fname, "/");
	strcat(fname, table_name);
	strcat(fname, ".tbl");
	j = MAXTABLES;
	for (i = 1; i<MAXTABLES; i++) {
		if (tables[i].t_name[0] == 0 && (j == MAXTABLES)) j = i;
		if (!strcmp(table_name, tables[i].t_name)) break;
	}
	if (i >= MAXTABLES) {
		fid = open(fname, O_RDWR);
		if (fid < 0) {
			printf("ERROR: Table does not exist\n");
			return 0;
		}
		strcpy(tables[j].t_name, table_name);
		tables[j].fid = fid;
		i = j;
		readcsvhdr(&tables[j]);
	}
	else fid = open(fname, O_RDWR);

	/* Get a file handle ****************************************************************/
	if (fid <= 0) {
		perror("error is:");
		printf("ERROR1: Unknown server error\n");
		cout << "file is :" << fname << endl;
		return 0;
	}
	else {
		/* skip first line */
		lseek(fid, 0, SEEK_SET);
		while (((i = read(fid, &c, 1)) == 1) && (c != '\n'));
	}
	return fid;
}
int
tblwidth(int tid)
{
	if (tid>MAXTABLES) return 0;
	return tables[tid].colcount;
}
char *
colname(int tid, int colpos)
{
	return tables[tid].cp[colpos].col_name;
}
exprnode *
getnextrow(int fid, int tid)
{
	int rv, j = 0, i, k;
	int numcol = tables[tid].colcount;
	int rowid;
	row* rowp;
	char c;
	exprnode *ep;
	char linebuf[MAXCOLS*(MAXDATA + 1)];

	//printf("::getnextrow: fid=%d, tid=%d\n", fid, tid);
	rowid = lseek(fid, 0, SEEK_CUR);
	while ((rv = read(fid, &c, 1)) == 1 && (c != '\n')) linebuf[j++] = c;
	linebuf[j] = 0;

	if (j>0) {
		/* Check for deleted line */
		if (linebuf[0] == 0) return 0;			/* Deleted line */
		for (i = 0; i<numcol; i++) if (linebuf[i] != '\t') break;
		if (i >= numcol) return 0;			/* Deleted line style 2 */

		ep = (exprnode *)makerow(tid);
		if (!ep) return &ERROR_OUTOFNODES;
		rowp = ep->values[0].rowp;
		rowp->rowid = rowid;
		//printf("line is %s alloc=%x\n", linebuf, ep);
		j = 0; k = 0;
		for (i = 0;; i++) {
			if (linebuf[i] == 0) {
				//printf("Found end\n");
				rowp->data[j++][k] = 0;
				for (i = j; i<MAXCOLS; i++) rowp->data[i][0] = 0;
				//printf("::getnextrow done %x\n", ep); for(i=0;i<j; i++) printf("%s\t",rowp->data[i]); printf("\n");
				return ep;
			}
			if (linebuf[i] == '\t') {
				rowp->data[j++][k] = 0;
				k = 0;
				//putchar('|');
				continue;
			}
			// Ignore excess data in column.
			if (k<MAXDATA) {
				rowp->data[j][k++] = linebuf[i];
			}
		}
	}
	//printf("::getnextrow: EOF\n");
	return (exprnode *)makeexpr(OP_EOF, 1, 0, 0);
}
void
closetbl(int fid)
{
	close(fid);
}
int
findpipetab(expr x)
{
	int i;
	char table_name[MAXDATA + 1];

	sprintf(table_name, " %x", x);

	for (i = 1; i<MAXTABLES; i++) {
		//printf("::findpipetab %s vs %s\n", table_name, tables[i].t_name);
		if (!strcmp(table_name, tables[i].t_name)) return i;
	}
	return 0;
}
int
findtab(char *table_name)
{
	int i;

	for (i = 1; i<MAXTABLES; i++) {
		//printf("::findtab %s vs %s\n", table_name, tables[i].t_name);
		if (!strcmp(table_name, tables[i].t_name)) return i;
	}
	return 0;
}

int
getpipetab(expr x, int number_columns, char *coldata)
{
	int i;
	char table_name[MAXDATA + 1];

	sprintf(table_name, " %x", x);

	for (i = 1; i<MAXTABLES; i++) {
		if (!tables[i].t_name[0]) {
			/* Found an empty slot */
			strcpy(tables[i].t_name, table_name);
			tables[i].colcount = 0;
			tables[i].rowcount = 0;
			tables[i].fid = -1;
			tables[i].cp = (struct column *)coldata;
			tables[i].colcount = number_columns;
			tables[i].engine = "PIPELINE";
			return i;
		}
	}
	return 0;
}
int is_identifier(char *str)
{
	register int i;

	for (i = 0; i<strlen(str); i++) {
		if (str[i] == 0) break;
		if (str[i] == '_') continue;
		if (str[i] == '$') continue;
		if (str[i] >= 'a' && str[i] <= 'z') continue;
		if (str[i] >= 'A' && str[i] <= 'Z') continue;
		if (i>0 && str[i] >= '0' && str[i] <= '9') continue;
		return 0;
	}
	if (i>0) return 1;
	return 0;
}
int is_validdata(char* str)
{
	register int i;

	/* Allow identifiers */
	if (is_identifier(str)) return 1;

	/* Allow quoted strings without embedded apostrophe */
	if (str[0] == '\'') for (i = 1; str[i]; i++) if (str[i] == '\'' && str[i + 1] == 0) return 2;

	/* Allow numbers */
	for (i = 0; str[i]; i++) {
		if (i>0 && str[i] >= '0' && str[i] <= '9') continue;
	}
	if (i>0) return 3;
	return 0;
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

int
colindex(int tid, char* colname, int colposition)
{
	register int i;

	//printf("::colindex: %d, %s, %d\n", tid, colname, colposition);
	if (tid && (tid < MAXTABLES) && tables[tid].t_name[0] && tables[tid].cp) {
		if (!strcmp(colname, tables[tid].cp[colposition].col_name)) return colposition;
		for (i = 0; i < tables[tid].colcount; i++) {
			if (!strcmp(colname, tables[tid].cp[i].col_name)) return i;
		}
	}
	return -1;
}
void
delpipetab(expr x)
{
	int i;
	char table_name[MAXDATA + 1];

	sprintf(table_name, " %x", x);

	for (i = 1; i<MAXTABLES; i++) {
		if (!strcmp(table_name, tables[i].t_name)) {
			tables[i].t_name[0] = 0;
			tables[i].cp = 0;
			tables[i].engine = 0;
			tables[i].rowcount = 0;
			tables[i].colcount = 0;
		}
	}
}
void updata_table(char* table_name, int number_columns, char** coldata)
{
	register int i = 0;
	/* Now make the entries in the in-memory data structures ***************************/
	for (i = 1; i<MAXTABLES; i++) {
		if (!tables[i].t_name[0]) {
			/* Found an empty slot */
			strcpy(tables[i].t_name, table_name);
			tables[i].colcount = 0;
			tables[i].rowcount = 0;
			tables[i].fid = -1;
			tables[i].cp = (column*)malloc((MAXDATA + 1)*number_columns);
			if (!tables[i].cp) {
				printf("::define_table: Out of memory, should never happen\n");
				exit(-1);
			}
			memcpy(tables[i].cp, coldata, number_columns*(MAXDATA + 1));
			tables[i].colcount = number_columns;
			tables[i].engine = "TSV";
			
		}
	}
}
exprnode* define_table(char* tablename, int colnum, char** colname)
{
	vector<string>col;
	for (int i = 1; colnum - i >= 0; i++)
	{
		col.push_back(colname[colnum - i]);
	}

	/*if table already exist*/
	if ((findtable(tablename)) != vectortables.tablename.end()){ return makeerrlit(define_table(11).c_str()); }
	
	/*if column name duplicated*/
	vector<string> temp = col;
	sort(temp.begin(), temp.end());
	vector<string>::iterator it;
	it = unique(temp.begin(), temp.end());
	if (it != temp.end()){ return makeerrlit(define_table(14).c_str()); }

	/*update and create file*/
	vectortables.tablename.push_back(tablename);
	vectortables.colname.push_back(col);


	/*create file*/
	char filename[1024];
	
	strcpy(filename, filepath);
	strcat(filename, "/");
	strcat(filename, tablename);
	strcat(filename, ".tbl");
	cout << filepath << endl;
	cout << filename << endl;
	ofstream myfile(filename, ofstream::out | ofstream::app | ofstream::in);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < colnum; i++)
		{
			myfile << col.at(i);
			myfile << '\t';
		}
		myfile << endl;
		myfile.close();
	}
	else { return makeerrlit(define_table(13).c_str()); }
	updata_table(tablename, colnum, colname);
	return makenulllit();
}
exprnode* insert_row(char* tablename, int colnum, char** colname)
{
	vector<string>col;
	for (int i = 1; colnum - i >= 0; i++)
	{
		col.push_back(colname[colnum - i]);
	}
	/*if table not exist*/
	if ((findtable(tablename) == vectortables.tablename.end())){ return makeerrlit(insert_row(21).c_str()); }

	/*check column size*/
	vector<string>::iterator tableptr = findtable(tablename);
	unsigned tableindex = tableptr - vectortables.tablename.begin();
	unsigned colsize = vectortables.colname.at(tableindex).size();

	if (colsize < colnum)
	{
		return makeerrlit(insert_row(22).c_str());
	}
	else if (colsize > colnum)
	{
		return makeerrlit(insert_row(23).c_str());
	}

	/*update and create file*/
	vectortables.colname.push_back(col);
	/*write to file*/
	char filename[1024];
	strcpy(filename, filepath);
	strcat(filename, "/");
	strcat(filename, tablename);
	strcat(filename, ".tbl");
	ofstream myfile(filename, ofstream::out | ofstream::app);
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < colnum; i++)
		{
			myfile << col.at(i);
			myfile << '\t';
		}
		myfile << endl;
		myfile.close();
	}
	else { return makeerrlit(insert_row(24).c_str()); }
	return makenulllit();
}
/****************************************************************************************************************/
/* Evaluate an expression - i.e. turn it into one of the above literals or an iterator **************************/
/****************************************************************************************************************/
exprnode *
subevalexpr(exprnode *x, row *context)
{
	int i, j, strmatch = 0;
	exprnode *ep, *ep1, *ep2;
	int arg[MAXCOLS];
	char *sarg[MAXCOLS + 1], *cp;
	char cbuf[MAXCOLS + 1][MAXDATA + 1];
	row *rowp, *rowo, *rowc;

	//printf("::evalexpr: %x, %x\n", x, context);
	//print_e(x,0);
	//putchar('\n');

	/*********************************************************************************************************/
	/* Evaluate implemented functions ************************************************************************/
	/* Each function may have different ways of getting its arguments from the parser so handle that first ***/
	/*********************************************************************************************************/
	if (!x) return x;
	switch (x->func) {
	default:
		//printf("func %s\n", op_name(x->func));
		return makeerrlit("ERROR: Not yet implemented (func)");

		/* Literals */
	case OP_NUMBER:
	case OP_STRING:
	case OP_NULL:
		return x;

	case OP_ITERATE:
		 subprint_relation((expr)x);
		 return x;

	case OP_GETNEXT:
		return getnext(x->values[0].ep);

	case OP_COLNAME:
		/* This must be evaluated in the context of the current row */
		if (!context)
			return makeerrlit("ERROR: Column outside row context");

		/* First find the ordinal position of the column */
		rowp = context;

		i = colindex(rowp->tableid, x->values[0].name, x->values[1].num);

		if (i >= 0) x->values[1].num = i;
		else return makeerrlit("ERROR: Column not found ");

		switch (is_validdata(rowp->data[i])) {
		case 1:
		//	cout << "is null" << endl;
			if (!strcmp("NULL", rowp->data[i]))
				return makenulllit();
		case 2:
			//cout << "is str" << endl;
			return makestrlit(rowp->data[i]);
		case 3:
			//cout << "is num" << endl;
			return makenumlit(atoi(rowp->data[i]));
		}
		return makeerrlit("ERROR: Invalid data in pipeline");

		/* Arithmetic and logic binary operators */
	case OP_AND:
	case OP_OR:
	case OP_PLUS:
	case OP_BMINUS:
	case OP_TIMES:
	case OP_DIVIDE:
	case OP_EQUAL:
	case OP_NOTEQ:
	case OP_LT:
	case OP_GT:
	case OP_GEQ:
	case OP_LEQ:
		//printf("::evalepxr: doing arith bin op ...\n");
		if (x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */

		/* Since we have a dynamic decision to make on choosing strcmp or arithmetic, we do it here */
		/* NOTE: if either argument is a string, we use strcmp for comparison */
		/* We could be a bit pickier here, as this code would not reject (2 + 'abc') */
		strmatch = 0;
		for (i = 0; i<2; i++) {
			//cout << "ep is " << x->values[i].ep->func;
			ep = subevalexpr(x->values[i].ep, context);
			if (!ep) return 0;
			if ((ep->func == OP_NULL) || (ep->func == OP_ERROR)) return ep;
			if (ep->func == OP_NUMBER) {
			//	cout << ep->values[0].num<<"  isnumber";
				arg[i] = ep->values[0].num;
				sarg[i] = cbuf[i];
				sprintf(cbuf[i], "%d", arg[i]);
			}
			else if (ep->func == OP_STRING) {
				//cout << ep->values[0].name << "isstring";
				strmatch = 1;
				arg[i] = atoi(ep->values[0].data);
				sarg[i] = ep->values[0].data;
			}
			else return makeerrlit("ERROR: Not yet implemented");
			//printf("::binop: arg%d = %d\n", i, arg[i]);
		}

		ep = makenumlit(0);
		if (strmatch)
			switch (x->func) {
			case OP_EQUAL:	ep->values[0].num = strcmp(sarg[0], sarg[1]) == 0; return ep;
			case OP_NOTEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) != 0; return ep;
			case OP_LT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) < 0;  return ep;
			case OP_GT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >  0; return ep;
			case OP_GEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >= 0; return ep;
			case OP_LEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) <= 0; return ep;
		}

		/* Use arithmetic for remaining cases */
		switch (x->func) {
		case OP_AND:	ep->values[0].num = arg[0] && arg[1]; break;
		case OP_OR:	ep->values[0].num = arg[0] || arg[1]; break;
		case OP_PLUS:	ep->values[0].num = arg[0] + arg[1]; break;
		case OP_BMINUS:	ep->values[0].num = arg[0] - arg[1]; break;
		case OP_TIMES:	ep->values[0].num = arg[0] * arg[1]; break;
		case OP_DIVIDE:	if (arg[1] == 0) { ep->func = OP_NULL; ep->count = 0; return ep; }
						ep->values[0].num = arg[0] / arg[1]; break;
		case OP_EQUAL:	ep->values[0].num = arg[0] == arg[1]; break;
		case OP_NOTEQ:	ep->values[0].num = arg[0] != arg[1]; break;
		case OP_LT:	ep->values[0].num = arg[0] < arg[1];  break;
		case OP_GT:	ep->values[0].num = arg[0] > arg[1]; break;
		case OP_GEQ:	ep->values[0].num = arg[0] >= arg[1]; break;
		case OP_LEQ:	ep->values[0].num = arg[0] <= arg[1]; break;
		}
		return ep;

	case OP_STREQUAL:
	case OP_STRNOTEQ:
	case OP_STRLT:
	case OP_STRGT:
	case OP_STRGEQ:
	case OP_STRLEQ:
		//printf("::evalepxr: doing string bin op ...\n");
		if (x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */
		for (i = 0; i<2; i++) {
			ep = subevalexpr(x->values[i].ep, context);
			if (!ep) return 0;
			if ((ep->func == OP_NULL) || (ep->func == OP_ERROR)) return ep;
			if (ep->func != OP_STRING) {
				return makeerrlit("Not yet implemented (string overload)");
			}
			sarg[i] = ep->values[i].data;
		}
		ep = makenumlit(0);
		i = strcmp(sarg[0], sarg[1]);
		switch (x->func) {
		case OP_STREQUAL:	ep->values[0].num = (i == 0) ? 1 : 0; break;
		case OP_STRNOTEQ:	ep->values[0].num = (i != 0) ? 1 : 0; break;
		case OP_STRLT:		ep->values[0].num = (i<0) ? 1 : 0; break;
		case OP_STRGT:		ep->values[0].num = (i>0) ? 1 : 0; break;
		case OP_STRGEQ:		ep->values[0].num = (i >= 0) ? 1 : 0; break;
		case OP_STRLEQ:		ep->values[0].num = (i <= 0) ? 1 : 0; break;
		}
		return ep;

	case OP_CREATETABLE:

		//printf("::evalepxr: doing create table...\n");
		if (x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */

		ep = (x->values[0].ep);
		if (!ep || (ep->func != OP_TABLENAME)) {
			return makeerrlit("ERROR: Invalid table name in CREATE TABLE");
		}
		sarg[0] = ep->values[0].name;

		/* Would be nice if it did not build the table in reversed column order!!! */
		for (i = 1, ep = x->values[1].ep; ep && ep->func == OP_RLIST; i++, ep = ep->values[1].ep) {
			if (ep->values[0].ep && ep->values[0].ep->func == OP_COLUMNDEF && ep->values[0].ep->values[0].ep->func == OP_COLNAME)
				sarg[i] = ep->values[0].ep->values[0].ep->values[0].name;
			else
				return makeerrlit("ERROR: Invalid column def");
		}
		return define_table(sarg[0], i - 1, sarg + 1);



	case OP_INSERTROW:

		//printf("::evalepxr: doing insert row ...\n");
		if (x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */
		ep = (x->values[0].ep);
		if (!ep || (ep->func != OP_TABLENAME)) {
			return makeerrlit("ERROR: Invalid table name in INSERT command");
		}
		sarg[0] = ep->values[0].name;

		/* Would be nice if it did not do reversed column order, coordinate change with CREATETABLE */
		for (i = 1, ep = x->values[1].ep; ep && ep->func == OP_RLIST; i++, ep = ep->values[1].ep) {
			if (ep->values[0].ep && ep->values[0].ep->func == OP_STRING) {
				sarg[i] = ep->values[0].ep->values[0].data;
			}
			else if (ep->values[0].ep && ep->values[0].ep->func == OP_NULL) {
				sarg[i] = "NULL";
			}
			else  if (ep->values[0].ep && ep->values[0].ep->func == OP_NUMBER) {
				sprintf(cbuf[i], "%d", ep->values[0].ep->values[0].num);
				sarg[i] = cbuf[i];
			}
			else return makeerrlit("ERROR: Invalid data element in INSERT command");
		}
		
			return insert_row(sarg[0], i - 1, sarg + 1);

	case OP_SELECTROW:

		//printf("::evalepxr: doing select row ...%x\n", context);
		if (x->count != 2) return makeerrlit("ERROR: Invalid argument count");	/* Should never happen! */

		ep = (x->values[0].ep);
		
		if (!ep) return 0;
		if (ep->func != OP_ROW) {
			ep = subevalexpr(ep, context);
			if (!ep || ep->func == OP_ERROR || ep->func == OP_EOF) return ep;
			if (ep->func != OP_ROW)
				return makeerrlit("ERROR: Not yet implemented (select)");
		}

		/* Got a row as the first argument */
		rowp = ep->values[0].rowp;
		

		/* Return row only if selection condition evaluates to TRUE */
		//cout << rowp->data[1];//cout << ep1->values[0].num;//cout << " ";
		ep1 = subevalexpr(x->values[1].ep, rowp);
		if (ep1 && (ep1->func == OP_NUMBER) && ep1->values[0].num) {
			cout << " " << ep->values[0].data << endl;
			return ep;
		}

		/* Got something other than TRUE, prune this row */
		rowfree(rowp); ep->values[0].rowp = 0;
		if (!ep1 || ep1->func == OP_ERROR || ep1->func == OP_EOF) return ep1;
		return 0;

	case OP_PROJECTROW:

		//printf("::evalepxr: doing project row ...\n");
		if (x->count != 2) return makeerrlit("ERROR: Invalid argument count");	/* Should never happen! */

		/***********************************************************************************************/
		/* First get the row we are going to work on ***************************************************/
		/***********************************************************************************************/
		ep = (x->values[0].ep);
		if (!ep) return 0;
		if (ep->func != OP_ROW) {
			ep = subevalexpr(ep, context);
			
			//printf("::evalepxr: doing project row - got row %x\n", ep);
			if (!ep || ep->func == OP_ERROR || ep->func == OP_EOF) return ep;
			//cout << "in projdection:" << ep->values[0].rowp->data[1] << endl;
			if (ep->func != OP_ROW)
				return makeerrlit("ERROR: Not yet implemented (project)");
		}

		/* Got a row as the first argument */
		rowp = ep->values[0].rowp;

		/***********************************************************************************************/
		/* Get the pipe table associated with this node (so we know the columns of the projection) *****/
		/* (For C++ coders the destructor for this node needs to release the pipetable) ****************/
		/***********************************************************************************************/
		j = listlen(x->values[1].ep);
		//cout << "j is : " << j<<" ";
		if (!(i = findpipetab(x))) {
			rowc = rowalloc(x);
		rowc->tableid = i = getpipetab(x, j, rowc->data[0]);

			/* We just allocated space, have not filled in the names yet */
		}
		//else rowc = 0;

		/* Allocate a row to put our output data in ****************************************************/
		rowo = rowalloc(x);
		rowo->tableid = i; /* Link to pipe table for this projection */
		delid = rowo->tableid;
		/***********************************************************************************************/
		/* Compute each one of the output columns in the correct order *********************************/
		/***********************************************************************************************/
		for (i = 0, ep1 = x->values[1].ep; ep1; i++, ep1 = ep1->values[1].ep) {
			//each rlist
			ep2 = ep1->values[0].ep;
			//cout << "op is :" << ep2->func << endl;
			if (!ep2 || (ep2->func != OP_OUTCOLNAME) || (ep1->func != OP_RLIST))
				return makeerrlit("Bad projection spec");
			if (rowc)  strcpy(rowc->data[j - i - 1], ep2->values[1].ep->values[0].name); //cout << "rename as:" << ep2->values[1].ep->values[0].name << endl;
	/*		cout << "i is:" << i << endl;
			cout << "op is :" << ep2->values[0].ep->func << endl;
			cout << "data is:" << rowp->data[0];
			cout << "data is:" << rowp->data[1];
			cout << "data is:" << rowp->data[2];*/
			ep2 = subevalexpr(ep2->values[0].ep, rowp);
			if (!ep2 || ep2->func == OP_NULL) {
				//cout << "become null";
				strcpy(rowo->data[j - i - 1], "NULL");
				continue;
			}
				//cout << "datastr is :" << ep2->values[0].data << endl;cout << "datanum is :" << ep2->values[0].num << endl;
			switch (ep2->func) {
			case OP_ERROR:	rowfree(rowo); rowfree(rowp); ep->values[0].rowp = 0; return ep2;
			case OP_STRING: strcpy(rowo->data[j - i - 1], ep2->values[0].data); continue;
			case OP_NUMBER:	 sprintf(rowo->data[j - i - 1], "%d", ep2->values[0].num); continue;
			}
			return makeerrlit("ERROR: Not yet implemented (project data)");
		}

		/***********************************************************************************************/
		/* Dont need the input row anymore *************************************************************/
		/***********************************************************************************************/
		rowfree(rowp); ep->values[0].rowp = 0;

		return makeexprnode(OP_ROW, 1, (exprnode *)rowo, 0);

	}
	return 0;
}




/**********************************************************************************************/
/* Get Next Function: *************************************************************************/
/* There is some magic!!!! going on here ******************************************************/
/* The getnext is linked to the iterator by the common argument they share ********************/
/* The shared argument must not be a copy, but physically the same node ***********************/
/**********************************************************************************************/
exprnode *
getnext(exprnode *ep)
{
	int cursor;
	int tid;

	//printf("::getnext:\n");
	if (!ep) return makeerrlit("ERROR: null table invalid\n");
	switch (ep->func) {
	case OP_TABLENAME:	cursor = ep->values[1].num;
		do {
			if (!cursor) {
				cursor = opentbl(ep->values[0].name);
				ep->values[1].num = cursor;
			}
			tid = findtab(ep->values[0].name);
			if (tid < 0) return makeerrlit("NO such table\n");
			ep = (exprnode *)getnextrow(cursor, tid);
		} while (!ep);
		if (ep->func == OP_EOF)
		{
			closetbl(cursor);
		}
		//else{ cout << "returned: " << ep->values[0].rowp->data[1] << endl; }
		return ep;
	default: return makeerrlit("ERROR: not a valid table\n");
	}
}

/**********************************************************************************************/
/* Example consumer of an iterator ************************************************************/
/* Normally an iterator fully implemented would put together the result "bag" *****************/
/* But often we dont need to do that, which is why use the iterator ***************************/
/**********************************************************************************************/
void
subprint_relation(expr e)
{
	struct expression *ep = (struct expression *)e;
	struct expression *rp;
	int rowcnt = 0;
	int i, tw;
	row *rowp, *rowc;;

	switch (ep->func) {
	case OP_EOF:	return;
	case OP_ERROR:	printf("%s\n", ep->values[0].data);
		return;
	case OP_ITERATE:
		//printf("::print_relation got iterator\n");
		do  {
			rp = subevalexpr(ep->values[1].ep, 0);
			if (!rp) continue;
			switch (rp->func) {
			default:	printf("::print_relation: dont know how to print OP_%s\n", op_name(rp->func));
				return;
			case OP_ERROR:
				printf("%s\n", rp->values[0].data);
				return;
			case OP_ROW:
				//printf("Got a row\n");
				rowp = rp->values[0].rowp;
				tw = tblwidth(rowp->tableid);
				//printf("%d columns, tid=%d\n", tw, rowp->tableid);
				if (!rowcnt) { for (i = 0; i<tw; i++) printf("%s\t", colname(rowp->tableid, i)); printf("\n"); }
				for (i = 0; i<tw; i++) printf("%s\t", rowp->data[i]); printf("\n");
				rowcnt++;
				continue;
			case OP_EOF:
				printf("%d rows returned\n", rowcnt++);
				return;
			}
		} while (1);

	}
	tables[delid].t_name[0] = 0;
	tables[delid].cp = 0;
	tables[delid].engine = 0;
	tables[delid].rowcount = 0;
	tables[delid].colcount = 0;
	delid = -1;
}
