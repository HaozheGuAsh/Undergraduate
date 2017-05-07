#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <errno.h>
#include "unistd.h"
#include <fcntl.h>

/* Make warnings go away */
extern char *parse_command(), *define_table(), *fetch_rows(), *insert_row();
extern int is_identifier(), is_valid_data();
extern void init();

#include "HW6-expr.h"
#include "HW6-expression.h"

extern int debug;
extern exprnode EOF_EXPR;
/*********************************************************************************************/
/* In memory schema **************************************************************************/
/*********************************************************************************************/
struct table {
	struct column *cp;
	int colcount;
	int rowcount;
	int fid;
	const char *engine;
	char t_name[MAXDATA + 1];
} tables[MAXTABLES];

struct column {
	char col_name[MAXDATA + 1];
};

/*********************************************************************************************/
/* File format:                                                                              */
/*               *****************************************************************************/
/* First line (header) is a series of column names separated by tabs *************************/
/* No other data is present in the header line ***********************************************/
/* Data lines may contain one more column than the header line *******************************/
/* Extra column is simply spare space to accomodate fast insert/update ***********************/
/* Spare space column may contain any number of characters! **********************************/
/* Data lines with no valid fields are "deleted" and should be ignored ***********************/
/* Short data lines should be considered "deleted" *******************************************/
/*********************************************************************************************/

csv_init()
{
	/* Decided it was simpler to read only when needed */

}

/*********************************************************************************************/
/* Read in the header line of the table ******************************************************/
/*********************************************************************************************/
void
readcsvhdr(struct table *tp)
{
	int col, j, n, i, rn;
	char ibuf[MAXCOLS*(MAXDATA+1)];
	char row[MAXCOLS][MAXDATA+1];
	char filename[MAXDATA];
	int fid;

	lseek(tp->fid, 0, SEEK_SET);
	col = 0; j=0; rn=0;

	//printf("Init table %s...\n", tp->t_name);
	while((i = read(tp->fid, ibuf, MAXCOLS*(MAXDATA+1))) > 0) {
		for(n=0; n<i; n++) {
			if(ibuf[n] == '\n') { 
				if(rn==0) {
					row[col][j] = 0;
					//printf("has last column %s...\n", row[col]);
					/* We have the header row */
					tp->colcount = col+1;
					tp->cp = malloc((col+1)*(MAXDATA+1));
					if(!tp->cp) {
						printf("::readcsvhdr: Out of memory, should never happen\n");
						exit(-1);
					}
					memcpy(tp->cp, row, (col+1)*(MAXDATA+1));
				}
				/* Do next row */
				col = 0; j=0; rn++;
				continue;
			}
			if(rn==0) {
				if(ibuf[n] == '\t') {
					/* We are done with a column */
					row[col][j] = 0;
					row[col][MAXDATA] = 0;
					row[col][MAXDATA-1] = 0;
					//printf("has column %s...\n", row[col]);
					col++; j=0;
					continue;
				}
				row[col][j++] = ibuf[n];
			} /* We are just counting the data rows, so we dont do anything here */
		}
	}
	tp->rowcount = rn;
	
	/* Now that all is set up, we can mark the columns that have an index */
	strcpy(filename, "data/");
	for(i=0; i<tp->colcount; i++) {
		strcpy(filename+5,tp->t_name);
		strcat(filename, ".");
		strcat(filename,tp->cp[i].col_name);
		strcat(filename,".idx");
		fid = open(filename, O_RDWR);
		if(fid > 0) {
			close(fid);
			filename[strlen(filename)-4] = 0;
			if(debug) printf("DEBUG: %s has a B-Tree index\n", filename+5);
			tp->cp[i].col_name[MAXDATA]='I';
		}
	}
}

/* Get a list of indexed columns, right now only one */
char *
get_idx_col(char *tbl)
{
	struct table *tp;
	register int i,j;

	if(!tbl) return 0;
	for(i=0; i<MAXTABLES; i++) {
		if(!strcmp(tables[i].t_name, tbl)) {
			tp= tables+i;
			for(j=0; j<tp->colcount; j++) {
				if(tp->cp[j].col_name[MAXDATA])
					return tp->cp[j].col_name;
			}
			return 0;
		}
	}
	return 0;
}
exprnode * getnextrowp(int fid, int tid)
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
	//linebuf[j] = '\n';
	linebuf[j] = 0;
	/*for (i = 0; i <= j; i++)
	{
		if (linebuf[i] == 32)printf("_");
		else if (linebuf[i] == '\t')printf("tab");
		else if (linebuf[i] == 0)printf("end");
		else printf("%c", linebuf[i]);
	}*/
	if (j>0) {
		/* Check for deleted line */
		if (linebuf[0] == 0) return 0;			/* Deleted line */
		for (i = 0; i<numcol; i++) if (linebuf[i] != '\t') break;
		//printf("tab num %d line %s", i, linebuf);
		if (i >= numcol) return 0;			/* Deleted line style 2 */

		ep = (exprnode *)makerow(tid);
		if (!ep) return &ERROR_OUTOFNODES;
		rowp = ep->values[0].rowp;
		rowp->rowid = rowid;
		//printf("line is %s alloc=%x\n", linebuf, ep);
		j = 0; k = 0; i = 1;
		while (linebuf[i] != 0)
		{
			if (linebuf[i] == '\t')
			{
				rowp->data[j++][k] = 0;
				//printf("found one %s\n", rowp->data[j - 1]);
				k = 0;
				i++;
				while (linebuf[i] == 32||linebuf[i]=='\n'){ i++; }
				if(linebuf[i]!=0)rowp->data[j][k++] = linebuf[i];
				else break;
			}
			else if (k<MAXDATA)
			{
				rowp->data[j][k++] = linebuf[i];
				
			}
			i++;
		}
		for (i = j; i<MAXCOLS; i++) rowp->data[i][0] = 0;
		//printf("found end one %s\n", rowp->data[j - 1]);
		return ep;
		
	}
	//printf("::getnextrow: EOF\n");
	return (exprnode *)makeexpr(OP_EOF, 1, 0, 0);
}
/* Sets the flag marking this column as an indexed column */
void
setidxflag(int tid, char *colname)
{
	int i;
	struct table *tp=tables+tid;

	printf("Setting index column data\n");
	for(i=0; i<tp->colcount; i++) {
		if(!strcmp(colname,tp->cp[i].col_name))
			tp->cp[i].col_name[MAXDATA] = 'I';
	}
}

/*********************************************************************************************/
/*********************************************************************************************/
char *
define_table(table_name, number_columns, column_names,ispipe)
char *table_name;
int number_columns;
char **column_names;
int ispipe;
{
	register int i=0;
	char fname[MAXDATA+11];
	char coldata[MAXCOLS][MAXDATA+1];
	int rv;

	//printf("::define_table called on %s with %d columns\n", table_name, number_columns);
	/* First make sure the directory exists */
	if((rv = mkdir("data", 0755)) < 0) {
		if(errno != EEXIST) return "Cannot create database directory\n";
	}
	
	/* Create the file ******************************************************************/
	strcpy(fname, "data/");
	strcpy(fname+5, table_name);
	strcpy(fname+strlen(fname), ".tbl");
	/* creat did not quite do what I wanted, forgot O_RDWR when I replaced it with open */
	/* Fixes the empty header line issue - Niket. */
	if((rv = open(fname, O_CREAT|O_EXCL|O_RDWR, 0666)) < 0) {
		if(errno == EEXIST) return "ERROR: Table already exists";
		return "ERROR: Cannot create table";
	}

	/* Write the header line */
	for(i=0; i<number_columns; i++) {
		strcpy(coldata[i], column_names[i]);
		write(rv, column_names[i], strlen(column_names[i]));
		if(i+1 < number_columns) write(rv,"\t", 1);
	}
	write(rv, "\n", 1);
	close(rv);

	/* Now make the entries in the in-memory data structures ***************************/
	for(i=1; i<MAXTABLES; i++) {
		if(!tables[i].t_name[0]) {
			/* Found an empty slot */
			strcpy(tables[i].t_name, table_name);
			tables[i].colcount=0;
			tables[i].rowcount=0;
			tables[i].fid = -1;
			tables[i].cp = malloc((MAXDATA+1)*number_columns);
			if(!tables[i].cp) {
				printf("::define_table: Out of memory, should never happen\n");
				exit(-1);
			}
			memcpy(tables[i].cp, coldata, number_columns*(MAXDATA+1));
			tables[i].colcount=number_columns;
			if (ispipe){ tables[i].engine = "PIPELINE"; }
			tables[i].engine = "TSV";

			return 0;
		}
	}
	return "ERROR: Unknown system error\n";
}

/*********************************************************************************************/
/*********************************************************************************************/
char *
insert_row(char *table_name, int number_values, char **values)
{
	struct table *tp;
	char fname[MAXDATA+11];
	char rowbuf[(MAXDATA+1)*MAXCOLS];
	register int i,j, offset;
	int fid = -1;

	//printf("::insert_row called on %s with %d columns\n", table_name, number_values);
	/* Find the table */
	strcpy(fname, "data/");
	strcpy(fname+5, table_name);
	strcpy(fname+strlen(fname), ".tbl");
	j = MAXTABLES;
	for(i=1; i<MAXTABLES; i++) {
		if(tables[i].t_name[0] == 0) j = i;
		if(!strcmp(table_name, tables[i].t_name)) break;
	}
	if(i>= MAXTABLES) {
		fid = open(fname, O_RDWR);
		if(fid < 0) {
			if(errno==ENOENT) return "ERROR: Table does not exist";
			else return "ERROR: Unknown server error";
		}
		strcpy(tables[j].t_name, table_name);
		tables[j].fid = fid;
		i = j;
		readcsvhdr(&tables[j]);
	}

	tp = tables+i;
	fid = tables[i].fid;
	if(fid<0) {
		fid = open(fname, O_RDWR);	// Open for Reading and writing
		if(fid < 0) {
			return "ERROR: Unknown server error";
		}
		tables[i].fid = fid;
	}

	/* Create the row */
	if(number_values < tables[i].colcount) return "ERROR: Too few values";
	if(number_values > tables[i].colcount) return "ERROR: Too many values";
	offset = 0;
	for(i=0; i<number_values; i++) {
		if(strcmp("NULL", values[i]) && values[i][0] != '\'') {
			for(j=0; values[i][j] && j<MAXDATA+1; j++) {
				if(values[i][j] < '0' || values[i][j] > '9') {
					return "ERROR: Invalid command";
				}
			}
		}
		strcpy(rowbuf+offset, values[i]);
		offset += strlen(values[i]);
		if(i+1 < number_values) {
			strcpy(rowbuf+offset,"\t");
			offset++;
		}
	}
	/* Insert spare space in row for row expansion */
	{
		strcpy(rowbuf+offset,"\t");
		offset++;
		strcpy(rowbuf+offset,"                              ");
	}
	strcat(rowbuf+offset, "\n");

	/* Make sure there is some space left for extra rows in a block */
	/* Also make sure the row does not cross a block boundary */
	lseek(fid, 0, SEEK_END);			// Seek to end of file
	offset = lseek(fid, 0, SEEK_END);		// Get current offset
	write(fid, rowbuf, strlen(rowbuf));

	/* Now make sure the indexes are updated */
	for(i=0; i<tp->colcount; i++) {
		if(tp->cp[i].col_name[MAXDATA]) {
			printf("::insert_row: found index column\n");
			btree_insert(tp->t_name,tp->cp[i].col_name,values[i],offset);
		}
	}
	blkflush();
	return 0;
}

int
opentbl(char *table_name)
{
	register i, j, fid=-1;
	char c;
	char fname[MAXDATA+1];

	//printf("::opentbl: %s\n", table_name);
	/* Find the table ********************************************************************/
	strcpy(fname, "data/");
	strcpy(fname+5, table_name);
	strcpy(fname+strlen(fname), ".tbl");
	j = MAXTABLES;
	for(i=1; i<MAXTABLES; i++) {
		if(tables[i].t_name[0] == 0 && (j == MAXTABLES)) j = i;
		if(!strcmp(table_name, tables[i].t_name)) break;
	}
	if(i>= MAXTABLES) {
		fid = open(fname, O_RDWR);

		if(fid < 0) {
			printf("ERROR: Table does not exist\n");
			return 0;
		}
		strcpy(tables[j].t_name, table_name);
		tables[j].fid = fid;
		i = j;
		readcsvhdr(&tables[j]);
	} else fid = open(fname, O_RDWR);

	/* Get a file handle ****************************************************************/
	if(fid <= 0) {
		printf("cannot open %s ", fname);
		printf("cannot create product\n");
		printf("ERROR: Unknown server error\n");
		return 0;
	} else {
		/* skip first line */
		lseek(fid, 0, SEEK_SET);
		while(((i=read(fid,&c,1))==1) && (c != '\n'));
	}
	return fid;
}

void
closetbl(int fid)
{
	close(fid);
}

exprnode *
getnextrow(int fid, int tid)
{
	int rv, j=0, i,k;
	int numcol = tables[tid].colcount;
	int rowid;
	row* rowp;
	char c;
	exprnode *ep;
	char linebuf[MAXCOLS*(MAXDATA+1)];

	//printf("::getnextrow: fid=%d, tid=%d\n", fid, tid);
	rowid = lseek(fid, 0, SEEK_CUR);
	while((rv=read(fid,&c,1))==1 && (c != '\n')) linebuf[j++] = c;
	linebuf[j] = 0;

	if(j>0) {
		/* Check for deleted line */
		if(linebuf[0] == 0) return 0;			/* Deleted line */
		for(i=0; i<numcol; i++) if(linebuf[i]!='\t') break;
		if(i >= numcol) return 0;			/* Deleted line style 2 */

		ep = (exprnode *)makerow(tid);
		if(!ep) return &ERROR_OUTOFNODES;
		rowp = ep->values[0].rowp;
		rowp->rowid = rowid;
		//printf("line is %s alloc=%x\n", linebuf, ep);
		j=0; k=0;
		for(i=0; ; i++) {
			if(linebuf[i] == 0) {
				//printf("Found end\n");
				rowp->data[j++][k] = 0;
				for(i=j;i<MAXCOLS; i++) rowp->data[i][0] = 0;
				//printf("::getnextrow done %x\n", ep); for(i=0;i<j; i++) printf("%s\t",rowp->data[i]); printf("\n");
				return ep;
			}
			if(linebuf[i] == '\t') {
				rowp->data[j++][k] = 0;
				k = 0;
				//putchar('|');
				continue;
			}
			// Ignore excess data in column.
			if(k<MAXDATA) {
				rowp->data[j][k++] = linebuf[i];
			}
		}
	}
	//printf("::getnextrow: EOF\n");
	return (exprnode *)makeexpr(OP_EOF, 1, 0, 0);
}

/*********************************************************************************************/
/*********************************************************************************************/
char *
fetch_rows(char *table_name, char *projection, char *selection)
{
	register int i, j, n;

	char fname[MAXDATA+11];		/* Table related data */
	int tid, fid;

	int colmap[MAXCOLS], proj_cols;	/* Projection spec */
	int off, poff, rv;
	char colname[MAXDATA+1];

	int colnum;			/* Selection data */
	char data[MAXDATA+1];
	char row[MAXCOLS][MAXDATA+1];
	char ibuf[MAXCOLS*(MAXDATA+1)];
	int col;
	int rn, rowc;

	//printf("doing SELECT %s FROM %s WHERE %s ; \n", projection, table_name, selection );

	/* Find the table ********************************************************************/
	strcpy(fname, "data/");
	strcpy(fname+5, table_name);
	strcpy(fname+strlen(fname), ".tbl");
	j = MAXTABLES;
	for(i=0; i<MAXTABLES; i++) {
		if(tables[i].t_name[0] == 0) j = i;
		if(!strcmp(table_name, tables[i].t_name)) break;
	}
	if(i>= MAXTABLES) {
		fid = open(fname, O_RDWR);
		if(fid < 0) {
			return "ERROR: Table does not exist";
		}
		strcpy(tables[j].t_name, table_name);
		tables[j].fid = fid;
		i = j;
		readcsvhdr(&tables[j]);
	}

	/* Get a file handle ****************************************************************/
	fid = tables[i].fid;
	if(fid < 0) {
		fid = open(fname, O_RDWR);	// Open for Reading and writing
		if(fid < 0) {
			return "ERROR: Unknown server error";
		}
		tables[i].fid = fid;
	}
	tid = i;

	//printf("found table with %d columns...\n", tables[tid].colcount);
	//for(i=0; i<tables[tid].colcount; i++) printf("%s ", tables[tid].cp+i);
	//printf("\n");

	/* Create column number map for the projection *************************************/
	poff=0;
	for(j=0; j<MAXCOLS; j++) {
		off=0; rv=sscanf(projection+poff, " %[a-zA-Z0-9_$]%n", colname, &off);
		if(rv > 0) {
			/* Forgot to make sure it is an identifier - Niket */
			if(!is_identifier(colname)) {
				return "ERROR: Invalid column name";
			}

			/* Got a column name in projection *********************************/
			//printf("Got a column name %s at %d\n", colname, off);

			/* Find the column position ****************************************/
			for(i=0; i<tables[tid].colcount; i++) {
				if(!strcmp(tables[tid].cp[i].col_name, colname)) {
					//printf("Found column %s in table...\n", colname);
					colmap[j] = i;
					break;
				}
			}
			//printf("%s is %d th column...\n", colname, i);
			if(i<tables[tid].colcount) {
				poff += off;
				//printf("Remaining projection before , is... %s \n", projection+poff);
				off = 0; sscanf(projection+poff, ",%n", &off);
				if(off > 0) {
					poff += off;
					//printf("Remaining projection is... %s \n", projection+poff);
					continue;
				}
				break;
			}
			return "ERROR: Output column does not exist";
		}
		return "ERROR: Invalid column list";
	}
	if(j >= MAXCOLS) return "ERROR: Too many output columns";
	proj_cols = j+1;

	//printf("found %d columns in projection\n", proj_cols);

	/* Find the column number of the column to match **********************************/
	poff= 0; off= 0;
	rv=sscanf(selection, " %[a-zA-Z0-9_$]%n", colname, &off);
	if(rv > 0) {
		if(!is_identifier(colname)) return "ERROR: Invalid column name";

		/* Got a column name in selection */
		/* Find the column position */
		for(i=0; i<tables[tid].colcount; i++) {
			if(!strcmp(tables[tid].cp[i].col_name, colname)) {
				colnum = i;
				break;
			}
		}
		if(i>=tables[tid].colcount) {
			return "ERROR: Column used in WHERE clause does not exist";
		}
		poff += off;
		off = 0; sscanf(selection+poff, " = %[0-9]%n", data, &off);
		if(off <= 0) {
			off=0; sscanf(selection+poff, "'%[^']'%n", data+1, &off);
			if(off<=0) {
				off=0; sscanf(selection+poff, "NULL %n", &off);
				if(off <= 0) return "ERROR: Invalid command";
				strcpy(data, "NULL");
			} else {
				data[0] = '\'';
			}
		}
	} else return "ERROR: Invalid WHERE clause";

	//printf("need to match column %d against the data %s ...\n", colnum, data);

	/* Now scan through the rows looking for rows that match, ************************/
	/* and when we find one apply the projection *************************************/
	lseek(fid, 0, SEEK_SET);
	col = 0; j=0; rn=0; rowc=0;
	while((i = read(fid, ibuf, MAXCOLS*(MAXDATA+1))) > 0) {
		for(n=0; n<i; n++) {
			if(ibuf[n] == '\n') { 
				/* We have accumulated a whole row */
				row[col][j] = 0;
				/* See if the column matches the data */
				if(!rn || !strcmp(row[colnum], data)) {
					/* Header line or... *****************************/
					/* Yes! Print the output row *********************/
					for(j=0; j<proj_cols; j++) {
						printf("%s\t", row[colmap[j]]);
					}
					printf("\n");
					if(rn) rowc++;
				}
				/* Do next row */
				col = 0; j=0; rn++;
				continue;
			}
			if(ibuf[n] == '\t') {
				/* We are done with a column */
				row[col][j] = 0;
				col++; j=0;
				continue;
			}
			row[col][j++] = ibuf[n];
		}
	}
	printf("\n%d fetched\n", rowc);
	return 0;
}

int
getpipetab(expr x, int number_columns, char *coldata)
{
	int i;
	char table_name[MAXDATA+1];

	sprintf(table_name, " %x", x);

	for(i=1; i<MAXTABLES; i++) {
		if(!tables[i].t_name[0]) {
			/* Found an empty slot */
			strcpy(tables[i].t_name, table_name);
			tables[i].colcount=0;
			tables[i].rowcount=0;
			tables[i].fid = -1;
			tables[i].cp = (struct column *)coldata;
			tables[i].colcount=number_columns;
			tables[i].engine = "PIPELINE";
			return i;
		}
	}
	return 0;
}

int
findtab(char *table_name)
{
	int i;

	for(i=1; i<MAXTABLES; i++) {
		//printf("::findtab %s vs %s\n", table_name, tables[i].t_name);
		if(!strcmp(table_name,tables[i].t_name)) return i;
	}
	return 0;
}

int
findpipetab(expr x)
{
	int i;
	char table_name[MAXDATA+1];

	sprintf(table_name, " %x", x);

	for(i=1; i<MAXTABLES; i++) {
		//printf("::findpipetab %s vs %s\n", table_name, tables[i].t_name);
		if(!strcmp(table_name,tables[i].t_name)) return i;
	}
	return 0;
}

void
delallpipetab()
{
	int i;
	int j;

	for(i=1; i<MAXTABLES; i++) {
		if(!tables[i].engine) continue;
		if(!strcmp("PIPELINE",tables[i].engine)) {
			tables[i].t_name[0] = 0;
			tables[i].cp = 0;
			tables[i].engine = 0;
			tables[i].rowcount = 0;
			tables[i].colcount = 0;
		}
		del_tbl_rows(i);	/* Release all pipe table rows */
	}
}

void
delpipetab(expr x)
{
	int i;
	char table_name[MAXDATA+1];

	sprintf(table_name, " %x", x);

	for(i=1; i<MAXTABLES; i++) {
		if(!strcmp(table_name,tables[i].t_name)) {
			tables[i].t_name[0] = 0;
			tables[i].cp = 0;
			tables[i].engine = 0;
			tables[i].rowcount = 0;
			tables[i].colcount = 0;
		}
	}
}

char *
colname(int tid, int colpos)
{
	return tables[tid].cp[colpos].col_name;
}

int
colindex(int tid, char* colname, int colposition)
{
	register i;

	//printf("::colindex: %d, %s, %d\n", tid, colname, colposition);
	if(tid && (tid < MAXTABLES) && tables[tid].t_name[0] && tables[tid].cp) {
		if(!strcmp(colname, tables[tid].cp[colposition].col_name)) return colposition;
		for(i=0;i < tables[tid].colcount; i++) {
			if(!strcmp(colname, tables[tid].cp[i].col_name)) return i;
		}
	}
	return -1;
}

int
tblwidth(int tid)
{
	if(tid>MAXTABLES) return 0;
	return tables[tid].colcount;
}

exprnode *
csv_randomread(int tblid, int rowid)
{
	struct table *tp = tables+tblid;
	row *rowp;
	char buf[MAXCOLS*(MAXDATA+1)];
	exprnode *rp;
	register int i,j,k;

	if(rowid < 0) return &EOF_EXPR;

	if(tp->fid <= 0) {
		char filename[MAXDATA+1];
		strcpy(filename, "data/"); strcat(filename, tp->t_name); strcat(filename, ".tbl");
		tp->fid = open(filename, O_RDWR);
		if(tp->fid < 0) {
			printf("::csv_randomread: Cannot open table file %s\n", filename);
			return (exprnode *)makeerrlit("ERROR: Cannot open table file");
		}
	}

	rp = (exprnode *)makerow(tblid);
	rowp = rp->values[0].rowp;
	
	lseek(tp->fid, rowid, SEEK_SET);
	read(tp->fid,buf,tp->colcount*(MAXDATA+1));

	j=k=0;
	for(i=0; i<(tp->colcount*MAXDATA+1); i++) {
		if(buf[i] && buf[i] != '\t' && buf[i] != '\n') 
			rowp->data[j][k++] = buf[i];
		else {
			rowp->data[j++][k] = 0;
			if(!buf[i] || buf[i]=='\n') break;
			k = 0;
		}
	}
	return rp;
}
