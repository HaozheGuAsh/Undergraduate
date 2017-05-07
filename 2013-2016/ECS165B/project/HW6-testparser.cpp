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
#include <fcntl.h>
#include <inttypes.h>
using namespace std;

/**********************************************************************/
/* Stuff to make the yacc and lex stuff compile in C++ without errors */
/**********************************************************************/
#define MAXNODE 20000
int freen = 0;
int initfreen;
/**********************************************************************/
/* Parser *************************************************************/
/**********************************************************************/
int linenum;

#include "HW6-expr.h"
//#include "rewriter.cpp"
//#include "HW4-rewriter.c"

expr cvt_itoe(int);
int yylex();
int yyerror(char const *);
expr makestrexpr(char *), makename(int, char*), makenum(int);
expr compile(expr), evalexpr(expr, int), optimize(expr);
void print_relation(expr);
void setname(int, int);
void init_op_map();
char * op_name(int);
void init_database();

/*global*/
myopmap opmap[256];
mytable vectortables;
struct  table tables[MAXTABLES];
char filepath[1024];

#define YYSTYPE expr
#include "HW6-sql.tab.cpp"
#include "lex.yy.cc"
yyFlexLexer *t = new yyFlexLexer;

int main()
{
    init_op_map();
	init_database();
    initfreen = freen;

    while (true) {
        if (!yyparse())  {
            break;
        }
	cout << "Syntax error, resyncing...\n";
    }
    cout << "QUITting...\n";
    return 0;
}
void printdata(mytable vectortables)
{
	for (int i = 0; i < vectortables.tablename.size(); i++)	//each table
	{
		cout << string(120, '-') << endl;
		cout << vectortables.tablename.at(i) << endl;
		for (int j = 0; j < vectortables.colname.at(i).size(); j++)
		{
			cout << setw(15) << vectortables.colname.at(i).at(j);
		}
		cout << endl;


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

void init_table(const char* table_name)
{
	int i;
	char fname[MAXDATA + 11];
	for (i = 1; i<MAXTABLES; i++) {
		
		if (!tables[i].t_name[0]) {
			/* Found an empty slot */
			strcpy(tables[i].t_name, table_name);
			tables[i].colcount = 0;
			tables[i].rowcount = 0;

			strcpy(fname, filepath);
			strcat(fname, "/");
			strcat(fname, table_name);
			strcat(fname , ".tbl");

			tables[i].fid = open(fname, O_RDWR);;

			tables[i].engine = "TSV";
			readcsvhdr(&tables[i]);
			if (!tables[i].cp) {
				printf("::define_table: Out of memory, should never happen\n");
				exit(-1);
			}
			return;
		}
	}
	


}
void init_database()
{
	struct dirent *d;
	DIR *dp;
	char datapath[1024];

	/*get current path*/
	if (getcwd(datapath, sizeof(datapath)) == NULL){ perror("error is:"); cout << global_err(3) << endl; exit(-1); }
	/*open dir*/
	strcat(datapath, "/database");
	strcpy(filepath, datapath);
	if ((dp = opendir(datapath)) == NULL)
	{
		if (mkdir(datapath, 0777) == -1)
		{
			perror("error is:");
			cout << global_err(4) << endl;
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
			vectortables.tablename.push_back(str);
			vectortables.colname.push_back(vector<string>());
			



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
						vectortables.colname.at(tablecount).push_back(name);
						columncount++;

					}
				}
				cout << endl;

				fs.close();
				tablecount++;
				cout << "here" << endl;
				init_table(str.c_str());
			}
			else	{ perror("error is:"); cout << global_err(5) << endl << "  file name: " << d->d_name << " , Exit program" << endl; exit(-1); }	//cannot open file


		}
	}
	//for (int i = 0; i < 2; i++) { cout << tables[3].cp[i].col_name << endl; }
	printdata(vectortables);
	cout << string(120, '-') << endl;
	cout << endl << "< " << tablecount << " tables > Readed" << endl;
}

int
yylex()
{
	return t->yylex();
}

/**********************************************************************/
/* Expression generation code *****************************************/
/**********************************************************************/
/*typedef
struct expression {
	int func;
	int count;
	union values {
		char *name;
		char *data;
		int num;
		struct expression *ep;
	} values[2];
} expression;*/
 
/* yyparse wants integers and CSIF machines have larger pointers than ints */
/* So need conversion routines between ints and node pointers **************/
expression ebuf[MAXNODE];

expr
cvt_itoe(int i)
{
	expr e;

	//printf("::cvt_itoe called with %d\n", i);

	if(!i) return 0;
	if(i<MAXNODE) {
		printf("Messed up index - too low\n");
		return 0;
	}
	if(i > MAXNODE+MAXNODE) {
		printf("Messed up index - too high\n");
		return 0;
	}
	e = (expr)(ebuf + (i-MAXNODE));
	return e;
}

/* Utility to convert a list into an array **********************************/
expr *
makearray(expr e)
{
	expression **epp, *ep = (expression *)e;
	int i, size = listlen(e);
	
	if(size==0) return 0;
	if(size < 0) {
		printf("::Bad list structure\n");
		exit(0);
	}
	epp = (expression **)malloc(size * sizeof (struct expression *));
	
	for(i=size-1; i>=0; i--) {
		if(!ep || ep->func != OP_RLIST) {
			printf("::Not a list element\n");
			return 0;
		}
		epp[i] = ep->values[0].ep;
		ep = ep->values[1].ep;
	}

	return (expr *)epp;
}

expr
makeexpr(int op, int cnt, expr arg1, expr arg2)
{
	expression *ep;
	int i, size;

	//printf(":make_expr called with %d %d %d %d\n", op, cnt, arg1, arg2);

	/* yyparse wants integers not pointers, and on CSIF machines they are incompatible */
	/* So allocate from an array, and return a modified index */
	if(freen<MAXNODE) {
		ep = ebuf + (freen++);
	} else {
		printf("Out of expression nodes\n");
		return 0;
	}

	ep->func = op;
	ep->count = cnt;
	ep->values[0].ep = (expression *)(arg1);
	switch(ep->func) {
	default:	ep->values[1].ep = (expression *)(arg2);
			break;
	case OP_COLUMNDEF:
		ep->values[1].num = (intptr_t)arg2;
			break;
	}

	return (expr)ep;
}

expr
makenum(int v)
{
	expression *ep = (expression *)makeexpr(OP_NUMBER,1,0,0);
	ep->count = 1;
	ep->values[0].num = v;
	return (expr)ep;
}

expr
makestrexpr(char *str)
{
	expression *ep = (expression *)makeexpr(OP_STRING,1,0,0);
	ep->count = 1;
	ep->values[0].data = str;
	return ep;
}

expr
makename(int op, char*str)
{
	expression *ep = (expression *)makeexpr(op,1,0,0);

	ep->count = 1;
	ep->values[0].name = str;
	//printf("::makename: returning %d\n", i);
	return (expr)ep;
}

expr
setname(int op, expr *ep)
{
	if(!ep) return 0;
	((expression *)ep)->func=op;
	return ep;
}

int
listlen(expr e)
{
	expression *ep = (expression *)e;
	int i;

	for(i=0; ep; i++) {
		if(ep->func != OP_RLIST) return -1;		/* Not a list element */
		ep = ep->values[1].ep;
	}
	return i;
}

void
print_e(expr e, int lev)
{
	expression *ep = (expression *)e;
	register int i, slev=lev;

	if(!ep) { printf("() "); return; }
	switch(ep->func) {

	/* Literals */
	case 257:	printf("$%d ", ep->values[0].num); return;
	case OP_NUMBER:	printf("%d ", ep->values[0].num); return;
	case OP_STRING:	printf("%s ", ep->values[0].data); return;
	case OP_NULL:	printf("NULL "); return;

	/* Names */
	case OP_COLNAME:
			printf("COLUMN:%s ", ep->values[0].name); return;
	case OP_TABLENAME:
			printf("TABLE:%s ", ep->values[0].name); return;
	case OP_FNAME:
			printf("FUNC:%s ", ep->values[0].name); return;

	/* Relational operators */
	case OP_PROJECTROW:
			printf("(PROJECT1 \n"); break;
	case OP_PROJECTION:
			printf("(PROJECT \n"); break;
	case OP_SELECTROW:
			printf("(SELECT1 \n"); break;
	case OP_SELECTION:
			printf("(SELECT \n"); break;
	case OP_PRODUCT:
			printf("(PRODUCT \n"); break;
	case OP_SORT:
			printf("(SORT \n"); break;
	case OP_GROUP:
			printf("(GROUP \n"); break;
	case OP_DELTA:
			printf("(DELTA \n"); break;
	case OP_CREATETABLE:
			printf("(CREATETABLE \n"); break;
	case OP_INSERTROW:
			printf("(INSERTROW \n"); break;
	case OP_GETNEXT:
			printf("(GETNEXT \n"); break;
	case OP_ITERATE:
			printf("(ITERATE \n"); break;
	
	case OP_PLUS:	printf("(+ \n"); break;
	case OP_BMINUS:	printf("(- \n"); break;
	case OP_TIMES:	printf("(* \n"); break;
	case OP_DIVIDE:	printf("(/ \n"); break;

	case OP_AND:	printf("(AND \n"); break;
	case OP_OR:	printf("(OR \n"); break;
	case OP_NOT:	printf("(! \n"); break;
	case OP_GT:	printf("(> \n"); break;
	case OP_LT:	printf("(< \n"); break;
	case OP_EQUAL:	printf("(== \n"); break;
	case OP_NOTEQ:	printf("(<> \n"); break;
	case OP_GEQ:	printf("(>= \n"); break;
	case OP_LEQ:	printf("(<= \n"); break;

	case OP_SORTSPEC:
			printf("(SORTSPEC \n"); break;

	case OP_COLUMNDEF:
			printf("(COLSPEC \n"); break;

	case OP_OUTCOLNAME:
			printf("(AS \n"); break;

	case OP_RLIST:	printf("(RLIST ");
			print_e(ep->values[0].ep, lev+7);
			putchar('\n');
			for(i=0;i<lev;i++) putchar(' ');
			print_e(ep->values[1].ep, lev);
			putchar(')');
			return;
	default:	printf("(%s \n", op_name(ep->func)); break;
	}
	lev += 2;
	for(i=0; i<lev; i++) putchar(' ');
	for(i=0; i<ep->count; i++) {
		print_e(ep->values[i].ep, lev+2); putchar(' ');
	}
	putchar('\n');
	for(i=0; i<slev; i++) putchar(' ');
	putchar(')');
}

void PrintTree(expr e, int tLevel){
	expression *ep = (expression *)e;

	if (!ep){
		cout << "NOTHING HERE" << endl;
		return;
	}

	cout << "Macro #" << op_name(ep->func)<< " @ level " << tLevel << "; #Nodes attached : " << ep->count << endl;
	if (ep->count==1&& ep->func !=91)
	{
		cout << "value: " << ep->values[0].data << endl;
	}
	else if (ep->count == 1 && ep->func == 91)
	{
		cout << "value: " << ep->values[0].num << endl;
	}

	if (ep->count > 0 && ep->func <= 60){
		cout << "traversing LEFT ";
		PrintTree(ep->values[0].ep, tLevel + 1);
		cout << " backtracking from the LEFT TO LEVEL " << tLevel << endl;
	}

	if (ep->count == 2){
		cout << "traversing RIGHT ";
		PrintTree(ep->values[1].ep, tLevel + 1);
		cout << " backtracking from the RIGHT TO LEVEL " << tLevel << endl;
	}
}

/**********************************************************************/
/* Dummy routines that need to be filled out for HW4 ******************/
/* Move to another module and fully define there **********************/
/**********************************************************************/
expr compile(expr e)
{
	exprnode *x= subcompile((exprnode *)e);
	return (expr) x;
}

expr evalexpr(expr e, int r)
{
	//cout << "r is :" << r << endl;
	//PrintTree((exprnode*)e, 0);
	expression *ep = (expression *) subevalexpr((exprnode*)e, 0);
	if (ep->func == OP_ERROR) cout << ep->values->data << endl;

	return e;
}

expr optimize(expr e)
{
	return e;
}

void print_relation(expr e)
{
	//PrintTree(e, 0);
	//print_e(e, 0);
}

int yyerror(char const *s) 
{
	printf("Error: %s\n", s);
}

/***********************************************************************************************/
/* Structures to allow conversion of number to name and vice-versa *****************************/
/***********************************************************************************************/


char opnamebuf[MAXDATA];

char *
op_name(int op_num)
{
	if(op_num < 1 || op_num > OP_EOF) {
		return "INVALID";
	}
	if(opmap[op_num].name)
		return opmap[op_num].name;
	else
		sprintf(opnamebuf,"OP_%d", op_num);
	return opnamebuf;
}

int
opnum(char *str)
{
	int i;
	for(i=1;i<256;i++) {
		if(!opmap[i].name) continue;
		if(!strcmp(opmap[i].name,str)) return i;
	}
	return 0;
}


/***********************************************************************************************/
/* Initialize the operator map *****************************************************************/
/***********************************************************************************************/
void
init_op_map()
{
	register int i;

	i = OP_SELECTION; opmap[i].name = "SELECTION";		
	i = OP_PROJECTION; opmap[i].name = "PROJECTION";		
	i = OP_PRODUCT; opmap[i].name = "PRODUCT";		
	i = OP_GROUP; opmap[i].name = "GROUP";		
	i = OP_DELTA; opmap[i].name = "DELTA";		
	i = OP_SORT; opmap[i].name = "SORT";		
	i = OP_SORTSPEC; opmap[i].name = "SORTSPEC";		
	i = OP_INSERT; opmap[i].name = "INSERT";		
	i = OP_DELETE; opmap[i].name = "DELETE";		
	i = OP_OPEN; opmap[i].name = "OPEN";		
	i = OP_GETNEXT; opmap[i].name = "GETNEXT";		
	i = OP_CLOSE; opmap[i].name = "CLOSE";		
	i = OP_PROJECTROW; opmap[i].name = "PROJECTROW";	 opmap[i].flag = IMPLEMENTED;
	i = OP_SELECTROW; opmap[i].name = "SELECTROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_INSERTROW; opmap[i].name = "INSERTROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_DELETEROW; opmap[i].name = "DELETEROW";		 opmap[i].flag = IMPLEMENTED;
	i = OP_ROW; opmap[i].name = "ROW";			 opmap[i].flag = IMPLEMENTED;
	i = OP_FETCH1; opmap[i].name = "FETCH1";		 opmap[i].flag = IMPLEMENTED;
	i = OP_EQUAL; opmap[i].name = "EQUAL";			 opmap[i].flag = IMPLEMENTED;
	i = OP_NOTEQ; opmap[i].name = "NOTEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_LEQ; opmap[i].name = "LEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_GEQ; opmap[i].name = "GEQ";			 opmap[i].flag = IMPLEMENTED;
	i = OP_LT; opmap[i].name = "LT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_GT; opmap[i].name = "GT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_PLUS; opmap[i].name = "PLUS";			 opmap[i].flag = IMPLEMENTED;
	i = OP_BMINUS; opmap[i].name = "BMINUS";		 opmap[i].flag = IMPLEMENTED;
	i = OP_TIMES; opmap[i].name = "TIMES";			 opmap[i].flag = IMPLEMENTED;
	i = OP_DIVIDE; opmap[i].name = "DIVIDE";		 opmap[i].flag = IMPLEMENTED;
	i = OP_UMINUS; opmap[i].name = "UMINUS";		
	i = OP_AND; opmap[i].name = "AND";			 opmap[i].flag = IMPLEMENTED;
	i = OP_OR; opmap[i].name = "OR";			 opmap[i].flag = IMPLEMENTED;
	i = OP_NOT; opmap[i].name = "NOT";		
	i = OP_FCALL; opmap[i].name = "FCALL";		
	i = OP_STREQUAL; opmap[i].name = "STREQUAL";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRNOTEQ; opmap[i].name = "STRNOTEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRLEQ; opmap[i].name = "STRLEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRGEQ; opmap[i].name = "STRGEQ";		 opmap[i].flag = IMPLEMENTED;
	i = OP_STRLT; opmap[i].name = "STRLT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STRGT; opmap[i].name = "STRGT";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STRCONCAT; opmap[i].name = "STRCONCAT";		
	i = OP_ATOI; opmap[i].name = "ATOI";			 opmap[i].flag = IMPLEMENTED;
	i = OP_ITOA; opmap[i].name = "ITOA";			 opmap[i].flag = IMPLEMENTED;
	i = OP_STXN; opmap[i].name = "STXN";		
	i = OP_COMMIT; opmap[i].name = "COMMIT";		
	i = OP_CLOSEALL; opmap[i].name = "CLOSEALL";		
	i = OP_SET; opmap[i].name = "SET";		
	i = OP_TABLENAME; opmap[i].name = "TABLENAME";		 opmap[i].flag = IMPLEMENTED;
	i = OP_COLNAME; opmap[i].name = "COLNAME";		 opmap[i].flag = IMPLEMENTED;
	i = OP_AS; opmap[i].name = "AS";		
	i = OP_COLUMNDEF; opmap[i].name = "COLUMNDEF";		
	i = OP_CREATETABLE; opmap[i].name = "CREATETABLE";	 opmap[i].flag = IMPLEMENTED;
	i = OP_FNAME; opmap[i].name = "FNAME";			 opmap[i].flag = IMPLEMENTED;
	i = OP_RLIST; opmap[i].name = "RLIST";		
	i = OP_STRING; opmap[i].name = "STRING";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NUMBER; opmap[i].name = "NUMBER";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NULL; opmap[i].name = "NULL";			 opmap[i].flag = IMPLEMENTED;
	i = OP_IN; opmap[i].name ="IN";

	i = OP_ITERATE; opmap[i].name = "ITERATE";		 opmap[i].flag = IMPLEMENTED;
}
