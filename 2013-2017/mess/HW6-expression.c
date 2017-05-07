#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "errno.h"

int linenum;

#include "HW6-expr.h"
#include "HW6-expression.h"

#define MAXROWS	1000
#define PINROW	1000

/* CSIF machines refuse to accept a proper initialization, so only do it partly here */
exprnode ERROR_OUTOFNODES = { OP_ERROR, 1, 0, 0 };
exprnode exprnodes[MAXNODES];
int freen=0;

/*****************************************************************************************************************/
/* Row Cache                                                                                  ********************/
/* NOTE:	The turnover is huge, so dont rely on automated garbage collection algorithms ********************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
row rowbuf[MAXROWS];
int rowexp = 0;
int rowseq = 1;


row *
rowalloc()
{
	int i;
	for(i=0;i<MAXROWS;i++) {
		if(rowbuf[i].tableid == 0) {
			rowbuf[i].rowexp = 1000;
			rowbuf[i].tableid = MAXTABLES;
			rowbuf[i].diskaddr = 0;
			rowbuf[i].rowid = rowseq++;
			return rowbuf+i;
		}
	}

	printf("ERROR: Out of rows\n");
	return 0;
}

rowfree(row *rowp)
{
	rowp->tableid = 0;
}

void
del_tbl_rows(int t)
{
	int i;

	if(t<=0 || t>= MAXTABLES) return;
	for(i=0; i<MAXROWS; i++) {
		if(rowbuf[i].tableid == t) {
			rowbuf[i].tableid = 0;
			rowbuf[i].diskaddr = 0;
			rowbuf[i].rowexp = 0;
			rowbuf[i].rowid = 0;
			rowbuf[i].data[0][0] = 0;
		}
	}
}

exprnode *getnext(exprnode*);
exprnode *getnext_iscan(exprnode *, exprnode *);

/******************************************************************************************************/
/* Make different kinds of expression *****************************************************************/
/******************************************************************************************************/
exprnode *
makeexprnode(int op, int cnt, exprnode *arg1, exprnode *arg2)
{
	exprnode *ep;
	int i, size;

	if(freen>=MAXNODES) {
		return &ERROR_OUTOFNODES;
	} else ep = exprnodes + freen++;
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
	return (int)makeexprnode(op, cnt, (exprnode *)arg1, (exprnode *)arg2);
}

/* Literals */
exprnode *
makenulllit()
{
	exprnode *ep = makeexprnode(OP_NULL, 0, 0, 0);
	if(ep==&ERROR_OUTOFNODES) return ep;
	return ep;
}

exprnode *
makenumlit(int num)
{
	exprnode *ep = makeexprnode(OP_NUMBER, 1, 0, 0);
	if(ep==&ERROR_OUTOFNODES) return ep;
	ep->values[0].num = num;
	return ep;
}

exprnode *
makestrlit(const char *str)
{
	exprnode *ep = makeexprnode(OP_STRING, 1, 0, 0);
	if(ep==&ERROR_OUTOFNODES) return ep;
	ep->values[0].data = (char *)str;
	return ep;
}

exprnode *
makeerrlit(const char *errmsg)
{
	exprnode *ep = makeexprnode(OP_ERROR,1,0,0);
	if(ep==&ERROR_OUTOFNODES) return ep;
	ep->values[0].data = (char *)errmsg;
	return ep;
}

exprnode *
makerow(int tid)
{
	row *rowp = rowalloc();
	exprnode *ep=makeexprnode(OP_ROW, 1, 0, 0);
	if(ep==&ERROR_OUTOFNODES) return ep;
	if(!rowp) {
		return makeerrlit("ERROR: Cannot allocate a row element");
	}
	ep->values[0].rowp = rowp;
	rowp->tableid = tid;

	return ep;
}

/****************************************************************************************************************/
/* Evaluate an expression - i.e. turn it into one of the above literals or an iterator **************************/
/****************************************************************************************************************/
exprnode *
evalexpr(exprnode *x, row *context)
{
	int i, j, strmatch = 0, logic = 0,doindex=0;
	exprnode *ep,*ep1,*ep2,*ep3,*tmp;
	int arg[MAXCOLS];
	char *sarg[MAXCOLS+1], *cp;
	char cbuf[MAXCOLS+1][MAXDATA+1];
	row *rowp, *rowo, *rowc;

	//printf("::evalexpr: %x, %x\n", x, context);
	//print_e(x,0);
	//putchar('\n');

	/*********************************************************************************************************/
	/* Evaluate implemented functions ************************************************************************/
	/* Each function may have different ways of getting its arguments from the parser so handle that first ***/
	/*********************************************************************************************************/
	if(!x) return x;
	switch(x->func) {
	default:	
			printf("func %s\n", op_name(x->func));
			return makeerrlit("ERROR: Not yet implemented (func)");

	/* Literals */
	case OP_NUMBER:
	case OP_STRING:
	case OP_NULL:
			return x;

	case OP_ITERATE:
			return x;

	case OP_SORT:
		return x;

	case OP_DISTINCT:
		return x;

	case OP_GETNEXT:
			return getnext(x->values[0].ep);

	case OP_GETNEXT_ISCAN:
			return getnext_iscan(x->values[0].ep, x->values[1].ep);

	case OP_COLNAME:
			/* This must be evaluated in the context of the current row */
			if(!context) 
				return makeerrlit("ERROR: Column outside row context");

			/* First find the ordinal position of the column */
			rowp = context;

			i = colindex(rowp->tableid, x->values[0].name, x->values[1].num);

			if(i>=0) x->values[1].num = i;
			else return makeerrlit("ERROR: Column not found ");

			switch(is_validdata(rowp->data[i])) {
			case 1:
				if(!strcmp("NULL",rowp->data[i]))
					return makenulllit();
			case 2:
				return makestrlit(rowp->data[i]);
			case 3:
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
		if(x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */

		/* Since we have a dynamic decision to make on choosing strcmp or arithmetic, we do it here */
		/* NOTE: if either argument is a string, we use strcmp for comparison */
		/* We could be a bit pickier here, as this code would not reject (2 + 'abc') */
		strmatch = 0;
		logic = 0;
		for (i = 0; i < 2; i++) {
			ep = evalexpr(x->values[i].ep, context);
			if (!ep) return 0;
			if ((ep->func == OP_NULL) || (ep->func == OP_ERROR)) return ep;
			if (ep->func == OP_NUMBER) {
				arg[i] = ep->values[0].num;
				sarg[i] = cbuf[i];
				sprintf(cbuf[i], "%d", arg[i]);
			}
			else if (ep->func == OP_STRING) {
				strmatch = 1;
				arg[i] = atoi(ep->values[0].data);
				sarg[i] = ep->values[0].data;
			}
		/*	else if (ep->func == OP_AND || ep->func == OP_OR)
			{
				//printf("in logic\n");
				logic = 1;
				tmp = makeexprnode(x->func, 2, x->values[0].ep->values[1].ep,x->values[1].ep);
				//printf("finish copy in logic, node is %d cout %d left is %d,right is%d \n", tmp->func, tmp->count, tmp->values[0].ep->func, tmp->values[1].ep->func);
				tmp->count = 2;
				tmp->func = x->func;
				tmp->values[1].ep = x->values[1].ep;
				tmp->values[1].name = x->values[1].name;
				tmp->values[1].data = x->values[1].data;
				tmp->values[1].num = x->values[1].data;

				tmp->values[0].ep = x->values[0].ep->values[1].ep;
				tmp->values[0].name = x->values[0].ep->values[1].name;
				tmp->values[0].data = x->values[0].ep->values[1].data;
				tmp->values[0].num = x->values[0].ep->values[1].data;
			
				exprnode* logicep = evalexpr(tmp, context);
				
				ep->values[1].num = logicep->values[0].num;
				ep3 = ep;
				
			}*/
			else return makeerrlit("ERROR: Not yet implemented");
		}

			//printf("::binop: arg%d = %d\n", i, arg[i]);
		
		/*if (logic)
		{
			ep = makenumlit(0);
			switch (ep3->func)
			{
			case OP_AND: ep->values[0].num = ep3->values[0].num &&ep3->values[1].num; 
				//printf("logic left %d right %d return %d \n", ep3->values[0].num, ep3->values[1].num,ep->values[0].num);
				return ep;
			case OP_OR:  ep->values[0].num = ep3->values[0].num || ep3->values[1].num;
				//printf("finish or");
				return ep;
			}
			return makeerrlit("ERROR: Not match in logic");
		}*/
		ep = makenumlit(0);
		if(strmatch)
		switch(x->func) {
		case OP_EQUAL:	ep->values[0].num = strcmp(sarg[0], sarg[1]) == 0; return ep;
		case OP_NOTEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) != 0; return ep;
		case OP_LT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) < 0; return ep;
		case OP_GT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >  0; return ep;
		case OP_GEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >= 0; return ep;
		case OP_LEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) <= 0; return ep;
		}

		/* Use arithmetic for remaining cases */
		switch(x->func) {
		case OP_AND:	 ep->values[0].num = arg[0] && arg[1]; break;
			//exprnode* logicep = makenumlit(arg[1]);
			//ep->values[1].ep = logicep; 
			//printf("in and,op is %d left is %d  right is %d end\n", ep->func, arg[0], ep->values[1].ep->values[0].num);  
			
		case OP_OR:ep->values[0].num = arg[0] || arg[1]; break;
		case OP_PLUS:	ep->values[0].num = arg[0] + arg[1]; break;
		case OP_BMINUS:	ep->values[0].num = arg[0] - arg[1]; break;
		case OP_TIMES:	ep->values[0].num = arg[0] * arg[1]; break;
		case OP_DIVIDE:	if(arg[1]==0) { ep->func=OP_NULL; ep->count=0; return ep; }
				ep->values[0].num = arg[0] / arg[1]; break;
		case OP_EQUAL:	ep->values[0].num = arg[0] == arg[1]; break;
		case OP_NOTEQ:	ep->values[0].num = arg[0] != arg[1]; break;
		case OP_LT:	ep->values[0].num = arg[0] < arg[1]; 
			//if (ep->values[0].num>0){ printf("in Less,return %d,id is %d compared to %d end\n", ep->values[0].num, arg[0], arg[1]); } 
			break;
		case OP_GT:	ep->values[0].num = arg[0] > arg[1]; 
			//if (ep->values[0].num>0){ printf("in greater,return %d,id is %d compared to %dend\n", ep->values[0].num, arg[0], arg[1]); }
			break;
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
		if(x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */
		for(i=0; i<2; i++) {
			ep = evalexpr(x->values[i].ep, context);
			if(!ep) return 0;
			if((ep->func == OP_NULL) || (ep->func == OP_ERROR)) return ep;
			if(ep->func != OP_STRING) {
				return makeerrlit("Not yet implemented (string overload)");
			}
			sarg[i] = ep->values[i].data;
		}
		ep = makenumlit(0);
		i = strcmp(sarg[0],sarg[1]);
		switch(x->func) {
		case OP_STREQUAL:	ep->values[0].num = (i==0)?1:0; break;
		case OP_STRNOTEQ:	ep->values[0].num = (i!=0)?1:0; break;
		case OP_STRLT:		ep->values[0].num = (i<0)?1:0; break;
		case OP_STRGT:		ep->values[0].num = (i>0)?1:0; break;
		case OP_STRGEQ:		ep->values[0].num = (i>=0)?1:0; break;
		case OP_STRLEQ:		ep->values[0].num = (i<=0)?1:0; break;
		}
		return ep;

	case OP_CREATETABLE:

		//printf("::evalepxr: doing create table...\n");
		if(x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */

		ep = (x->values[0].ep);
		if(!ep || (ep->func != OP_TABLENAME)) {
			return makeerrlit("ERROR: Invalid table name in CREATE TABLE");
		}
		sarg[0] = ep->values[0].name;

		
		char* indexcol[MAXDATA + 1];
		/* Would be nice if it did not build the table in reversed column order!!! */
		for (i = 1, ep = x->values[1].ep; ep && ep->func == OP_RLIST; i++, ep = ep->values[1].ep) {
			if (ep->values[0].ep && ep->values[0].ep->func == OP_COLUMNDEF && ep->values[0].ep->values[0].ep->func == OP_COLNAME)
			{
				sarg[i] = ep->values[0].ep->values[0].ep->values[0].name;
				//printf("here,%s", ep->values[0].ep->values[1].ep->values[0].name);

				
				if (ep->values[0].ep->values[1].ep)
				{
					if (!strcmp(ep->values[0].ep->values[1].ep->values[0].name, "KEY"))
					{
						doindex = 1;
						strcpy(indexcol, sarg[i]);
						//printf("need index col:%s", indexcol);
					}

				}
			}
			else 
			return makeerrlit("ERROR: Invalid column def");
		}

		cp = (char *)define_table(sarg[0], i-1, sarg+1);
		if(cp) return makeerrlit(cp);
		if (doindex)
		{
			char filename[MAXDATA + 1];
			strcpy(filename, "data/");
			strcat(filename, sarg[0]);
			strcat(filename, ".");
			strcat(filename, indexcol);
			strcat(filename, ".idx");
			printf("Creating Index on column %s\n", indexcol);
			strcpy(indexcol, "");
			int rv;
			if ((rv = open(filename, O_CREAT | O_EXCL | O_RDWR, 0666)) < 0) {
				if (errno == EEXIST) return "ERROR: Table already exists";
				return "ERROR: Cannot create table";
			}
			//init_btree(filename); 
		}
		return 0;

	case OP_INSERTROW:

		//printf("::evalepxr: doing insert row ...\n");
		if(x->count != 2) return makeerrlit("Invalid argument count");	/* Should never happen! */
		ep = (x->values[0].ep);
		if(!ep || (ep->func != OP_TABLENAME)) {
			return makeerrlit("ERROR: Invalid table name in INSERT command");
		}
		sarg[0] = ep->values[0].name;

		/* Would be nice if it did not do reversed column order, coordinate change with CREATETABLE */
		for(i=1, ep=x->values[1].ep; ep && ep->func==OP_RLIST; i++, ep=ep->values[1].ep) {
			if(ep->values[0].ep && ep->values[0].ep->func==OP_STRING) {
				sarg[i] = ep->values[0].ep->values[0].data;
			} else if(ep->values[0].ep && ep->values[0].ep->func==OP_NULL) {
				sarg[i] = "NULL";
			} else  if(ep->values[0].ep && ep->values[0].ep->func==OP_NUMBER) {
				sprintf(cbuf[i], "%d", ep->values[0].ep->values[0].num);
				sarg[i] = cbuf[i];
			} else return makeerrlit("ERROR: Invalid data element in INSERT command");
		}
		cp = (char *)insert_row(sarg[0], i-1, sarg+1);
		if(cp) return makeerrlit(cp);
		return 0;

	case OP_SELECTROW:

		//printf("::evalepxr: doing select row ...%x\n", context);
		if(x->count != 2) return makeerrlit("ERROR: Invalid argument count");	/* Should never happen! */

		ep = (x->values[0].ep);
		if(!ep) return 0;
		if(ep->func != OP_ROW) {
			ep = evalexpr(ep, context);
			if(!ep || ep->func == OP_ERROR || ep->func == OP_EOF) return ep;
			if(ep->func != OP_ROW)
				return makeerrlit("ERROR: Not yet implemented (select)");
		}

		/* Got a row as the first argument */
		rowp = ep->values[0].rowp;

		/* Return row only if selection condition evaluates to TRUE */
		ep1=evalexpr(x->values[1].ep, rowp);
		if(ep1 && (ep1->func == OP_NUMBER) && ep1->values[0].num) {
			return ep;
		}

		/* Got something other than TRUE, prune this row */
		rowfree(rowp); ep->values[0].rowp=0;
		if(!ep1 || ep1->func == OP_ERROR || ep1->func == OP_EOF) return ep1;
		return 0;

	case OP_PROJECTROW:

		//printf("::evalepxr: doing project row ...\n");
		if(x->count != 2) return makeerrlit("ERROR: Invalid argument count");	/* Should never happen! */

		/***********************************************************************************************/
		/* First get the row we are going to work on ***************************************************/
		/***********************************************************************************************/
		ep = (x->values[0].ep);
		if(!ep) return 0;
		if(ep->func != OP_ROW) {
			ep = evalexpr(ep, context);
			//printf("::evalepxr: doing project row - got row %x\n", ep);
			if(!ep || ep->func == OP_ERROR || ep->func == OP_EOF) return ep;
			if(ep->func != OP_ROW)
				return makeerrlit("ERROR: Not yet implemented (project)");
		}

		/* Got a row as the first argument */
		rowp = ep->values[0].rowp;

		/***********************************************************************************************/
		/* Get the pipe table associated with this node (so we know the columns of the projection) *****/
		/* (For C++ coders the destructor for this node needs to release the pipetable) ****************/
		/***********************************************************************************************/
		j=listlen(x->values[1].ep);
		if(!(i=findpipetab(x))) {
			rowc=rowalloc();
			if(!rowc) {
				return makeerrlit("ERROR: Cant find space for pipeline table column names");
			}
			rowc->tableid = i = getpipetab(x, j, rowc->data[0]);

			/* We just allocated space, have not filled in the names yet */
		} else rowc=0;

		/* Allocate a row to put our output data in ****************************************************/
		rowo = rowalloc();
		if(!rowo) {
			return makeerrlit("ERROR: Cant find space for output row");
		}
		rowo->tableid = i;		/* Link to pipe table for this projection */
		rowo->rowid = rowp->rowid;	/* Pass on the row id */

		/***********************************************************************************************/
		/* Compute each one of the output columns in the correct order *********************************/
		/***********************************************************************************************/
		for(i=0,ep1=x->values[1].ep; ep1; i++,ep1=ep1->values[1].ep) {
			ep2 = ep1->values[0].ep;
			if(!ep2 || (ep2->func != OP_OUTCOLNAME) || (ep1->func != OP_RLIST))
				return makeerrlit("Bad projection spec");
			if(rowc) strcpy(rowc->data[j-i-1], ep2->values[1].ep->values[0].name);
			ep2 = evalexpr(ep2->values[0].ep,rowp);
			if(!ep2 || ep2->func == OP_NULL) {
				strcpy(rowo->data[j-i-1],"NULL");
				continue;
			}
			switch(ep2->func) {
			case OP_ERROR:	rowfree(rowo); rowfree(rowp); ep->values[0].rowp = 0; return ep2;
			case OP_STRING:	strcpy(rowo->data[j-i-1], ep2->values[0].data); continue;
			case OP_NUMBER:	sprintf(rowo->data[j-i-1], "%d", ep2->values[0].num); continue;
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
/* Utility functions **************************************************************************/
/**********************************************************************************************/
expr *
makearray(expr e)
{
	exprnode **epp, *ep = e;
	int i, size = listlen(e);
	
	if(size < 0) {
		printf("::Bad list structure\n");
		exit(0);
	}
	epp = malloc(size * sizeof (struct expression *));
	
	for(i=size-1; i>=0; i--) {
		epp[i] = ep->values[0].ep;
		ep = ep->values[1].ep;
	}

	return (expr *)epp;
}

listlen(expr e)
{
	exprnode *ep = e;
	int i;

	for(i=0; ep; i++) {
		if(ep->func != OP_RLIST) return -1;		/* Not a list element */
		ep = ep->values[1].ep;
	}
	return i;
}

print_e(expr e, int lev)
{
	struct expression *ep = e;
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
	case OP_GETNEXT_ISCAN:
			printf("(ISCAN \n"); break;
	case OP_RANGE:	printf("(RANGE %s - %s)\n", ep->values[0].data, ep->values[1].data); return;
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

/**********************************************************************************************/
/* Get Next Function: *************************************************************************/
/* There is some magic!!!! going on here ******************************************************/
/* The getnext is linked to the iterator by the common argument they share ********************/
/* The shared argument must not be a copy, but physically the same node ***********************/
/**********************************************************************************************/
exprnode *
getnext(exprnode *tp)
{
	exprnode *ep;
	int cursor;
	int tid;

	//printf("::getnext:\n");
	if(!tp) return makeerrlit("ERROR: null table invalid\n");
	switch(tp->func) {
	case OP_TABLENAME:	cursor=tp->values[1].num;
				do {
					if(!cursor) {
						cursor=opentbl(tp->values[0].name);
						tp->values[1].num = cursor;
					}
					tid = findtab(tp->values[0].name);
					if(tid < 0) return makeerrlit("NO such table\n");
					ep = (exprnode *)getnextrow(cursor, tid);
				} while(!ep);
				if(ep->func == OP_EOF) closetbl(cursor);
				return ep;
	default: return makeerrlit("ERROR: not a valid table\n");
	}
}

/**********************************************************************************************/
/* Example consumer of an iterator ************************************************************/
/* Normally an iterator fully implemented would put together the result "bag" *****************/
/* But often we dont need to do that, which is why use the iterator ***************************/
/**********************************************************************************************/
int countline(char * filename)
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
	if (ch != '\n' && number_of_lines != 0)
		number_of_lines++;

	fclose(myfile);
	return number_of_lines;
}
void dosort(int isdigit, char* filename,int index)
{
	pid_t pid;
	//printf("index is %d\n", index);
	char* chindex;
	char ary[5];
	index++;
	snprintf(ary, 10,"%d", index);
	//printf("ary is %s", ary);
	chindex=&ary[0];
	//printf("int is %s", chindex);
	pid = fork();
	if (pid == 0)		//child
	{
		if (isdigit)	//digit
		{
			//printf("here1\n");
			//execlp("ls", "ls", "-la", NULL);
			//execlp("bash", "bash", "-c","sort",filename, NULL);
			//execlp("bash", "sort", "-t$'\t'", "-k3 ","-n", filename, NULL);
			execlp("sort", "sort","-t","\t", "-k", chindex, "-n", filename, NULL);
			//printf("here12\n");
		}
		else          //string
		{
			execlp("sort", "sort", "-t", "\t", "-k", chindex,  filename, NULL);
		}
	}
	else                //parent
	{
		int status;
		int corpse;
		//printf("child died\n");
		while ((corpse = wait(&status)) > 0 && corpse != pid)
		{

		}
		
	}
	//do print


}
void dodistinctsort(int isdigit, char* filename, int index)
{
	pid_t pid,pid1;
	//printf("index is %d\n", index);
	char* chindex;
	char ary[5];
	index++;
	snprintf(ary, 10, "%d", index);
	//printf("ary is %s", ary);
	chindex = &ary[0];
	//printf("int is %s", chindex);
	pid = fork();
	if (pid == 0)		//child
	{
		if (isdigit)	//digit
		{
			pid1 = fork();
			if (pid1 == 0)
			{
				//printf("111");
				execlp("sort", "sort", "-o", filename, "-t", "\t", "-k", chindex, "-n", filename, NULL);
			}
			else                //parent
			{
				int status;
				int corpse;
				//printf("child died\n");
				while ((corpse = wait(&status)) > 0 && corpse != pid)
				{

				}
				
				execlp("uniq", "uniq", filename, NULL);
			}
		}
		else          //string
		{
			pid1 = fork();
			if (pid1 == 0)
			{
				execlp("sort", "sort", "-o", filename, "-t", "\t", "-k", chindex,filename, NULL);
			}
			else                //parent
			{
				int status;
				int corpse;
				//printf("child died\n");
				while ((corpse = wait(&status)) > 0 && corpse != pid)
				{

				}
				execlp("uniq", "uniq", filename, NULL);
			}
			
		}
	}
	else                //parent
	{
		int status;
		int corpse;
		//printf("child died\n");
		while ((corpse = wait(&status)) > 0 && corpse != pid)
		{

		}
		int count = countline(filename);
		printf("%d rows returned\n", count);
	}
	//do print

}
void dodistinct(char* filename)
{
	pid_t pid, pid1;

	pid = fork();
	if (pid == 0)		//child
	{
	
			pid1 = fork();
			if (pid1 == 0)
			{
				printf("111");
				execlp("sort", "sort", "-o", filename, "-t", "\t", "-n", filename, NULL);
			}
			else                //parent
			{
				int status;
				int corpse;
				//printf("child died\n");
				while ((corpse = wait(&status)) > 0 && corpse != pid)
				{

				}

				execlp("uniq", "uniq", filename, NULL);
			}
	
	}
	else                //parent
	{
		int status;
		int corpse;
		//printf("child died\n");
		while ((corpse = wait(&status)) > 0 && corpse != pid)
		{

		}
		int count = countline(filename);
		printf("%d rows returned\n", count);
	}
	//do print
}
void
print_relation(expr e)
{
	struct expression *ep = (struct expression *)e;
	struct expression *rp;
	struct expression *epsort=NULL;
	char filename[MAXDATA + 1];
	int special = -1;
	/*
	1--------- Sort only
	2--------- Sort on distinct column
	3--------- Distinct alone
	*/
	int initialspecial = -1;
	int isdigit = -1;
	int columnindex = 0;
	int fid;
	int rowcnt = 0;
	int i, tw;
	row *rowp, *rowc;;
	int savefreen;

	//print_e(e,0);
	if(!e) return;
	//printf("root is %d", ep->func);
	if (ep->func == OP_DISTINCT)
	{
		 special = 3;
		ep = ep->values[0].ep;
		//printf("in distinct special is :%d \n", special);
	}
	if (ep->func == OP_SORT)
	{
		if (epsort = ep->values[1].ep->values[0].ep->values[0].ep) //rlist->colspec->colname
		{
			//printf("Doing order by %d   %s", epsort->func, epsort->values[0].name);
			ep = ep->values[0].ep;
			if (special == 3) special = 2;
			else special = 1;
		}
		else return makeerrlit("Invalid order by structure");
	}

	switch(ep->func) {

	case OP_EOF:	return;
	case OP_ERROR:	printf("%s\n", ep->values[0].data);
			return;
	case OP_ITERATE:
			//printf("::print_relation got iterator\n");
			savefreen = freen;
			do  {
				rp=evalexpr(ep->values[1].ep, 0);
				if(!rp) {
					freen = savefreen;
					continue;
				}
				switch(rp->func) {
				default:	printf("::print_relation: dont know how to print OP_%s\n", op_name(rp->func));
						break;
				case OP_ERROR:	
						printf("%s\n", rp->values[0].data);
						printf("%d rows processed\n", rowcnt);
						printf("savefreen = %d, freen = %d\n", savefreen, freen);
						break;
				case OP_ROW: 
						//printf("Got a row\n");
						rowp = rp->values[0].rowp;
						tw = tblwidth(rowp->tableid);
						//printf("%d columns, tid=%d\n", tw, rowp->tableid);
						if(!rowcnt) { for(i=0;i<tw;i++) printf("%s\t", colname(rowp->tableid,i)); printf("\n"); }
						if ((special!=-1)&&(initialspecial==-1))// special command, store the output 
						{
							initialspecial = 1;
							//printf("here00");
							if (special == 1 || special == 2) // case require sort
							{
								columnindex = colindex(rowp->tableid, epsort->values[0].name, epsort->values[1].num);
								//printf("in 0,colindex: %d", columnindex);
								if (columnindex >= 0) epsort->values[1].num = columnindex;
								else return makeerrlit("ERROR: Column not found ");

								switch (is_validdata(rowp->data[columnindex])) {

								case 2:
									isdigit = 0;  break;//printf("col is str\n");
								case 3:
									isdigit = 1;  break;//printf("col is int\n");
								default:return makeerrlit("ERROR: Invalid data in orderby");;
								}
							
							//	printf("in 1,colindex: %d",columnindex);
							}

							
							strcpy(filename, "data/"); strcat(filename, "output.txt");
							fid = open(filename, O_CREAT | O_EXCL | O_RDWR, 0666);
							for (i = 0; i < tw; i++)
							{
								write(fid, rowp->data[i], strlen(rowp->data[i]));
								write(fid, "\t", strlen("\t"));
							}
							write(fid, "\n", strlen("\n"));
							rowcnt++;
						}
						else if (special!=1&& initialspecial==1)
						{
							//printf("here");
							for (i = 0; i < tw; i++)
							{
								write(fid, rowp->data[i], strlen(rowp->data[i]));
								write(fid, "\t", strlen("\t"));
							}
							write(fid, "\n", strlen("\n"));
							rowcnt++;
						}
						else
						{
							//printf("here 1");
							for (i = 0; i<tw; i++) printf("%s\t", rowp->data[i]); printf("\n");
							rowcnt++;
						}

						rowfree(rowp);
						freen = savefreen;
						continue;
				case OP_EOF:
						
						if (special==1)
						{
							//printf("in 3");
							//printf("case special==1 sort\n");
							close(fid);
							dosort(isdigit, filename,columnindex);
							remove(filename);
							printf("%d rows returned\n", rowcnt++);
						}
						else if (special == 2)
						{
							//printf("case special==2 sort+distinct\n");
							close(fid);
							dodistinctsort(isdigit, filename, columnindex);
							remove(filename);
						}
						else if (special == 3)
						{
							//printf("case special==3 distinct\n");
							close(fid);
							dodistinct(filename);
							remove(filename);
						}
						
						break;
				}
				blkflush();
				delallpipetab();
				freen = savefreen;
				return;
			} while(1);
			
	}
}

