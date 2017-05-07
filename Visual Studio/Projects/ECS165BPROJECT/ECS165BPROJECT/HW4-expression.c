#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"

int linenum;

#include "HW6-expr.h"
#include "HW4-expression.h"

#define MAXROWS	1000
#define PINROW	1000

/* CSIF machines refuse to accept a proper initialization, so only do it partly here */
exprnode ERROR_OUTOFNODES = { OP_ERROR, 1, 0, 0 };

/*****************************************************************************************************************/
/* Row Cache                                                                                  ********************/
/* NOTE:	The turnover is huge, so dont rely on automated garbage collection algorithms ********************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
row rowbuf[MAXROWS];
int rowexp = 0;
int rowseq = 1;

row *
rowalloc(expr x)
{
	/* nth chance clock algorithm */
	int rid, loopcnt=0;
	do {
		rid = rowexp = (rowexp+1)%1000;
		if(!rid) { rid = rowexp++; loopcnt++; }
		if(rowbuf[rid].tableid == 0) {
			rowbuf[rid].rowexp = 1000;
			rowbuf[rid].tableid = MAXTABLES;
			rowbuf[rid].diskaddr = 0;
			rowbuf[rid].rowid = rowseq++;
			return rowbuf+rid;
		}
		if(rowbuf[rid].rowexp-- <= 0) {
			rowbuf[rid].rowexp = 1000;
			rowbuf[rid].tableid = MAXTABLES;
			rowbuf[rid].diskaddr = 0;
			rowbuf[rid].rowid = rowseq++;
			return rowbuf+rid;
		}
		if(rowbuf[rid].rowexp > 500)
			rowbuf[rid].rowexp = 1000;
	} while (loopcnt < 3);
	return 0;
}

rowfree(row *rowp)
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
	exprnode *ep = (exprnode *)malloc(sizeof (exprnode));
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
	return (int)makeexprnode(op, cnt, (exprnode *)arg1, (exprnode *)arg2);
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
	exprnode *ep = makeexprnode(OP_ERROR,1,0,0);
	ep->values[0].data = (char *)errmsg;
	return ep;
}

exprnode *
makerow(int tid)
{
	row *rowp = rowalloc(0);
	exprnode *ep=makeexprnode(OP_ROW, 1, 0, 0);
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
	int i,j, strmatch=0;
	exprnode *ep,*ep1,*ep2;
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
			//printf("func %s\n", op_name(x->func));
			return makeerrlit("ERROR: Not yet implemented (func)");

	/* Literals */
	case OP_NUMBER:
	case OP_STRING:
	case OP_NULL:
			return x;

	case OP_ITERATE:
			return x;

	case OP_GETNEXT:
			return getnext(x->values[0].ep);

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
		for(i=0; i<2; i++) {
			ep = evalexpr(x->values[i].ep, context);
			if(!ep) return 0;
			if((ep->func == OP_NULL) || (ep->func == OP_ERROR)) return ep;
			if(ep->func == OP_NUMBER) {
				arg[i] = ep->values[0].num;
				sarg[i] = cbuf[i];
				sprintf(cbuf[i],"%d",arg[i]);
			} else if(ep->func == OP_STRING) {
				strmatch = 1;
				arg[i] = atoi(ep->values[0].data);
				sarg[i] = ep->values[0].data;
			} else return makeerrlit("ERROR: Not yet implemented");
			//printf("::binop: arg%d = %d\n", i, arg[i]);
		}

		ep = makenumlit(0);
		if(strmatch)
		switch(x->func) {
		case OP_EQUAL:	ep->values[0].num = strcmp(sarg[0], sarg[1]) == 0; return ep;
		case OP_NOTEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) != 0; return ep;
		case OP_LT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) <  0; return ep;
		case OP_GT:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >  0; return ep;
		case OP_GEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) >= 0; return ep;
		case OP_LEQ:	ep->values[0].num = strcmp(sarg[0], sarg[1]) <= 0; return ep;
		}

		/* Use arithmetic for remaining cases */
		switch(x->func) {
		case OP_AND:	ep->values[0].num = arg[0] && arg[1]; break;
		case OP_OR:	ep->values[0].num = arg[0] || arg[1]; break;
		case OP_PLUS:	ep->values[0].num = arg[0] + arg[1]; break;
		case OP_BMINUS:	ep->values[0].num = arg[0] - arg[1]; break;
		case OP_TIMES:	ep->values[0].num = arg[0] * arg[1]; break;
		case OP_DIVIDE:	if(arg[1]==0) { ep->func=OP_NULL; ep->count=0; return ep; }
				ep->values[0].num = arg[0] / arg[1]; break;
		case OP_EQUAL:	ep->values[0].num = arg[0] == arg[1]; break;
		case OP_NOTEQ:	ep->values[0].num = arg[0] != arg[1]; break;
		case OP_LT:	ep->values[0].num = arg[0] < arg[1]; break;
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

		/* Would be nice if it did not build the table in reversed column order!!! */
		for(i=1, ep=x->values[1].ep; ep && ep->func==OP_RLIST; i++, ep=ep->values[1].ep) {
			if(ep->values[0].ep && ep->values[0].ep->func==OP_COLUMNDEF && ep->values[0].ep->values[0].ep->func==OP_COLNAME)
				sarg[i] = ep->values[0].ep->values[0].ep->values[0].name;
			else 
			return makeerrlit("ERROR: Invalid column def");
		}

		cp = (char *)define_table(sarg[0], i-1, sarg+1);
		if(cp) return makeerrlit(cp);
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
			rowc=rowalloc(x);
			rowc->tableid = i = getpipetab(x, j, rowc->data[0]);

			/* We just allocated space, have not filled in the names yet */
		} else rowc=0;

		/* Allocate a row to put our output data in ****************************************************/
		rowo = rowalloc(x);
		rowo->tableid = i; /* Link to pipe table for this projection */

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
	default:	printf("(%d \n", ep->func); break;
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
getnext(exprnode *ep)
{
	int cursor;
	int tid;

	//printf("::getnext:\n");
	if(!ep) return makeerrlit("ERROR: null table invalid\n");
	switch(ep->func) {
	case OP_TABLENAME:	cursor=ep->values[1].num;
				do {
					if(!cursor) {
						cursor=opentbl(ep->values[0].name);
						ep->values[1].num = cursor;
					}
					tid = findtab(ep->values[0].name);
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
void
print_relation(expr e)
{
	struct expression *ep = (struct expression *)e;
	struct expression *rp;
	int rowcnt = 0;
	int i, tw;
	row *rowp, *rowc;;

	switch(ep->func) {
	case OP_EOF:	return;
	case OP_ERROR:	printf("%s\n", ep->values[0].data);
			return;
	case OP_ITERATE:
			//printf("::print_relation got iterator\n");
			do  {
				rp=evalexpr(ep->values[1].ep, 0);
				if(!rp) continue;
				switch(rp->func) {
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
						if(!rowcnt) { for(i=0;i<tw;i++) printf("%s\t", colname(rowp->tableid,i)); printf("\n"); }
						for(i=0;i<tw;i++) printf("%s\t", rowp->data[i]); printf("\n");
						rowcnt++;
						continue;
				case OP_EOF:
						printf("%d rows returned\n", rowcnt++);
						return;
				}
			} while(1);
			
	}
}

