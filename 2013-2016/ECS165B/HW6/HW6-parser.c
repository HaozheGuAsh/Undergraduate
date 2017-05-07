#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include <fcntl.h>
#include "dirent.h"



int linenum;
int initfreen;

#include "HW6-expr.h"
#include "HW6-expression.h"
#include "HW6-buf.h"
#define YYERROR_VERBOSE
#include "y.tab.c"
#include "lex.yy.c"

/* Function to detect whether a string matches the identifier rules */
int
is_identifier(str)
char *str;
{
	register int i;

	for(i=0; i<strlen(str); i++) {
		if(str[i] == 0) break;
		if(str[i] == '_') continue;
		if(str[i] == '$') continue;
		if(str[i] >= 'a' && str[i] <= 'z') continue;
		if(str[i] >= 'A' && str[i] <= 'Z') continue;
		if(i>0 && str[i] >= '0' && str[i] <= '9') continue;
		return 0;
	}
	if(i>0) return 1;
	return 0;
}

/* Function to detect whether a string matches valid data */
int
is_validdata(str)
char *str;
{
	register int i;

	/* Allow identifiers */
	if(is_identifier(str)) return 1;

	/* Allow quoted strings without embedded apostrophe */
	if(str[0]=='\'') for(i=1; str[i]; i++) if(str[i] == '\'' && str[i+1] == 0) return 2;

	/* Allow numbers */
	for(i=0; str[i]; i++) {
		if(i>0 && str[i] >= '0' && str[i] <= '9') continue;
	}
	if(i>0) return 3;
	return 0;
}

int debug = 0;

main(argc, argv)
int argc;
char **argv;
{
	register i;

	for(i=1; i<argc; i++) {
		if((argv[i][0] == '-') && (argv[i][1] == 'd')) debug = 1;
	}

	init_op_map();
	init_tables();

	initfreen = freen;

	while((i=yyparse())>0) printf("Syntax error, resyncing\n");
	printf("QUITting...\n");
}
void PrintTree(expr e, int tLevel){
	exprnode *ep = (exprnode *)e;

	if (!ep){
		printf("NOTHING¡¡Here\n");
		return;
	}
	if (ep->func == 102){ printf("got distinct"); 
	printf("Macro # %s @ level %d ; #Nodes attached : %d \n", op_name(ep->func), tLevel, ep->count); 
	PrintTree(ep->values[0].ep, tLevel + 1); return;
	}

	printf("Macro # %s @ level %d ; #Nodes attached : %d \n", op_name(ep->func), tLevel, ep->count);
	//cout << "Macro #" << op_name(ep->func)<< " @ level " << tLevel << "; #Nodes attached : " << ep->count << endl;
	if (ep->count==1&& ep->func !=91&& ep->func!=OP_DISTINCT)
	{
		printf("value: %s\n", ep->values[0].data);
		//cout << "value: " << ep->values[0].data << endl;
	}
	else if (ep->count == 1 && ep->func == 91)
	{
		printf("value: %d\n", ep->values[0].num);
		//cout << "value: " << ep->values[0].num << endl;
	}

	if (ep->count > 0 && ep->func <= 60){
		printf("traversing LEFT ");
		//cout << "traversing LEFT ";
		PrintTree(ep->values[0].ep, tLevel + 1);
		printf(" backtracking from the LEFT TO LEVEL %d \n", tLevel);
		//cout << " backtracking from the LEFT TO LEVEL " << tLevel << endl;
	}

	if (ep->count == 2){
		printf("traversing RIGHT ");
		//cout << "traversing RIGHT ";
		PrintTree(ep->values[1].ep, tLevel + 1);
		printf(" backtracking from the RIGHT TO LEVEL %d \n",tLevel);
		//cout << " backtracking from the RIGHT TO LEVEL " << tLevel << endl;
	}
}
int countfilerow(char * filename)
{
	FILE* myfile = fopen(filename, "r");
	int ch, number_of_lines = 0;

	do
	{
		ch = fgetc(myfile);
		if (ch == '\n')
			number_of_lines++;
	} while (ch != EOF);

	// last line doesn't end with a new line!
	// but there has to be a line at least before the last line
	//if (ch != '\n' && number_of_lines != 0)
	//	number_of_lines++;

	fclose(myfile);
	remove("data/count.txt");
	return number_of_lines;
}
void createtablespe(char * filename)
{
	int fid;
	int size;
	char fname[MAXDATA + 1],txtname[MAXDATA+1];
	strcpy(fname, "data/");
	strcat(fname , filename);
	strcpy(txtname, fname);
	strcat(fname , ".tbl");
	strcat(txtname, "spe");
	strcat(txtname , ".txt");
	//printf("txtname %s\n",txtname);
	//printf("fname %s\n", fname);
	fid = open(txtname, O_RDWR);
	if (fid < 0)
	{
		fid = open(txtname, O_CREAT | O_EXCL | O_RDWR, 0666);
		if (fid<0) return "Cannot create table statistic file\n";
	}
	

	
	FILE * table;
	table = fopen(fname, "r");
	if (table == NULL) return "Cannot Read Table\n";
	fseek(table, 0, SEEK_END); // seek to end of file
	size = ftell(table); // get current file pointer
	size = (size / BLOCKSIZE)+1;
	fseek(table, 0, SEEK_SET); // seek back to beginning of file
	
	int ch, number_of_lines = 0;
	do
	{
		ch = fgetc(table);
		if (ch == '\n')
			number_of_lines++;
	} while (ch != EOF);
	number_of_lines--;
	fclose(table);
	char ary[10], ary2[10];
	int i = 0;
	for (i; i < 10; i++)
	{
		ary[i] = 0;
		ary2[i] = 0;
	}
	sprintf(ary, "%d", size);
	write(fid, ary, strlen(ary));
	write(fid, "\t", strlen("\t"));
	sprintf(ary2, "%d", number_of_lines);
	write(fid, ary2, strlen(ary2));
	close(fid);
	if(debug)printf("DEBUG: Statistics of table %s  #Blocks: %d #Rows: %d\n",fname, size,number_of_lines);
}
void createindexspe(char* filename)
{
	int i;
	char *tblname = (char *)malloc(MAXDATA + 1), *colname = (char *)malloc(MAXDATA + 1);
	char fname[MAXDATA + 1];
	strcpy(tblname, filename + 5);
	for (i = 0; tblname[i]; i++) if (tblname[i] == '.') { tblname[i] = 0; break; }
	strcpy(colname, filename + 5 + strlen(tblname) + 1);
	for (i = 0; colname[i]; i++) if (colname[i] == '.') { colname[i] = 0; break; }
	//printf("table:%s index:%s", tblname, colname);
	strcpy(fname, "data/");
	strcat(fname, tblname);
	strcat(fname, ".tbl");
	FILE * table;
	table = fopen(fname, "r");
	if (table == NULL) return "Cannot Read Table\n";
	char col[MAXDATA + 1];
	int colindex = 0, j = 0, count = 0;;
	char ch;
	do
	{
		ch = fgetc(table);
		//printf("ch at %d is: %c\n", count, ch);
		if (ch == '\t'||ch=='\n')
		{
			colindex++;
			col[count] = '\0';
			if (!strcmp(col, colname))
			{
				//printf("match\n");
				break;
			}
			else
			{
				//printf("not match  %s   %s\n",col,colname);
				memset(&col[0], 0, sizeof(col));
				count = -1;
			}
		}
		else
		{
				col[count] = ch;
				//printf("current col %s\n", col);
		}
		count++;
	} while (ch != '\n');
	//printf("colindex is :%d", colindex);
	char command[MAXDATA + 1];
	char index[100];
	strcpy(command, "cut -f");
	sprintf(index, "%d", colindex);
	strcat(command, index);
	strcat(command, " ");
	strcat(command, fname);
	strcat(command, " > data/temp.txt ");
	//printf("command: %s\n",command);
	system(command);
	system("sort -o data/temp.txt -u data/temp.txt");
	int distinct = countfilerow("data/temp.txt") - 1;
	if(debug)printf("DEBUG: Distinct values of indexed column %s from table: %s are : %d\n",colname,tblname,distinct);
	system("rm -f data/temp.txt");
	FILE * spe;
	char spename[MAXDATA + 1];
	strcpy(spename, "data/");
	strcat(spename, tblname);
	strcat(spename, colname);
	strcat(spename, "spe.txt");
	//printf("file is : %s", spename);

	spe = fopen(spename, "wb");
	fprintf(spe, "%d", distinct);
	fclose(spe);
	return;
}
init_tables()
{
	struct dirent *dirp;
	struct dirent dirbuf;
	char filename[MAXDATA+1];
	char *extp;
	int rv;
	if ((rv = mkdir("data", 0755)) < 0) {
		if (errno != EEXIST) return "Cannot create database directory\n";
	}
	DIR *dfid = opendir("data");
	//system("cut -f 2 data/movies.tbl > hello.txt");
	while(dirp = readdir(dfid)) {
		dirbuf = *dirp;
		extp = dirbuf.d_name + strlen(dirbuf.d_name) - 4;
		//printf("dname %s  extp %s", dirbuf.d_name, extp);
		strcpy(filename, "data/"); strcat(filename, dirbuf.d_name);
		//printf("filename: %s",filename);
		if(!strcmp(extp,".tbl")) {
			filename[strlen(filename)-4] = 0;
			opentbl(filename+5);
			//printf("file is %s", filename);
			createtablespe(filename+5);
		} else if(!strcmp(extp, ".idx")) {
			//printf("idx filename:%s", filename);
			init_btree(filename);
			createindexspe(filename);
		}
	}
}
