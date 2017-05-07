#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"

#include "HW6-expr.h"
#include "HW4-expression.h"

#define IMPLEMENTED	1
#define OP_VAR		257
#define MAXRULES	100
exprnode *lhs[MAXRULES], *rhs[MAXRULES];;

/***********************************************************************************************/
/* Rule table - preloading prevents abuse, loading from a file allows experimentation **********/
/***********************************************************************************************/
char *rules[MAXRULES] = {
"(PROJECTION (ITERATE $1 $2) $3) =>    (ITERATE $1 (PROJECTROW $2 $3))",
"(PROJECTION (TABLENAME $1 ) $2) => (ITERATE (TABLENAME $1) (PROJECTROW (GETNEXT (TABLENAME $1)) $2))",
"(SELECTION (ITERATE $1 $2) $3) => (ITERATE $1 (SELECTROW $2 $3))",
"(SELECTION (TABLENAME $1) $2) => (ITERATE (TABLENAME $1) (SELECTROW (GETNEXT (TABLENAME $1)) $2))",
};
int rulecnt=4;

void
init_rules();

/***********************************************************************************************/
/* Structures to allow conversion of number to name and vice-versa *****************************/
/***********************************************************************************************/
struct opmap {
	char *name;
	int	flag;
} opmap[256];

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
	i = OP_OUTCOLNAME; opmap[i].name = "OUTCOLNAME";		
	i = OP_COLUMNDEF; opmap[i].name = "COLUMNDEF";		
	i = OP_CREATETABLE; opmap[i].name = "CREATETABLE";	 opmap[i].flag = IMPLEMENTED;
	i = OP_FNAME; opmap[i].name = "FNAME";			 opmap[i].flag = IMPLEMENTED;
	i = OP_RLIST; opmap[i].name = "RLIST";		
	i = OP_STRING; opmap[i].name = "STRING";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NUMBER; opmap[i].name = "NUMBER";		 opmap[i].flag = IMPLEMENTED;
	i = OP_NULL; opmap[i].name = "NULL";			 opmap[i].flag = IMPLEMENTED;

	i = OP_ITERATE; opmap[i].name = "ITERATE";		 opmap[i].flag = IMPLEMENTED;
	init_rules();

	/* Initialization hack for CSIF machines */
	ERROR_OUTOFNODES.values[0].data = "ERROR: Out of nodes";
}

char *
op_name(int op_num)
{
	if(op_num < 1 || op_num > OP_EOF) {
		return "INVALID";
	}
	return opmap[op_num].name;
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
/* Function to convert rules into an expression tree *****************************/
/***********************************************************************************************/
exprnode *
getexpr(char *str)
{
	int off=0, op;
	int n, rv;
	char opname[MAXDATA+1];
	exprnode *v1, *v2;
	int varnum;

	n=0; rv=sscanf(str, " ( %[a-zA-Z0-9] %n", opname, &n);	
	if(rv!=1) { printf("Badly formed rule segment %s\n", str); exit(1); }
	op = opnum(opname);
	strcpy(str, str+n);
	n=0; rv=sscanf(str, " ) %n", &n);
	if(n) {
		strcpy(str, str+n);
		return (exprnode *)makeexpr(op, 0, 0, 0);
	}

	/* One argument *************************************************************/
	n=0; rv=sscanf(str, " $%d %n", &varnum, &n);
	if(rv==1) {
		strcpy(str, str+n);
		v1 = (exprnode *)makeexpr(OP_VAR, 1, varnum, 0);
	} else {
		n=0; rv=sscanf(str, " ( %n", &n);
		if(n) {
			v1 = getexpr(str);
		} else  { printf("Badly formed rule segment %s\n", str); exit(1); }
	} 
	n=0; rv=sscanf(str, " ) %n", &n);
	if(n) {
		strcpy(str, str+n);
		return (exprnode *)makeexpr(op, 1, (int)v1, 0);
	}

	/* Two arguments ************************************************************/
	n=0; rv=sscanf(str, " $%d %n", &varnum, &n);
	if(rv==1) {
		strcpy(str, str+n);
		v2 = (exprnode *)makeexpr(OP_VAR, 1, varnum, 0);
	} else {
		n=0; rv=sscanf(str, " ( %n", &n);
		if(n) {
			v2 = getexpr(str);
		} else  { printf("Badly formed rule segment %s\n", str); exit(1); }
	} 
	n=0; rv=sscanf(str, " ) %n", &n);
	if(n) {
		strcpy(str, str+n);
		return (exprnode *)makeexpr(op, 2, (int)v1, (int)v2);
	}

	/* More than two not supported *********************************************/
	printf("Too many arguments in rule %s\n", str);
	exit(1);
}

/***********************************************************************************************/
/***********************************************************************************************/
void
init_rules()
{
	FILE *fid;
	int i=0;
	int c;
	char *rp;
	char buf[MAXDATA+1];
	fid = fopen("data/rules","r");
	if(fid) {
		while((c=fgetc(fid))>0) {
			if(c=='\n') {
				buf[i]=0;
				rules[rulecnt] = malloc(strlen(buf)+1);
				strcpy(rules[rulecnt],buf);
				i=0; rulecnt++;
				continue;
			}
			buf[i++] = toupper(c);
		}
		fclose(fid);
	}

	for(i=0; i<MAXRULES; i++) {
		if(!rules[i]) return;
		//printf("Loading rule: %s\n", rules[i]);
		rp = strstr(rules[i], "=>");
		strncpy(buf,rules[i], rp-rules[i]);
		lhs[i] = getexpr(buf);
		//printf("got LHS \n"); 
		//print_e(lhs[i], 0);
		strcpy(buf,rp+2);
		rhs[i] = getexpr(buf);
		//printf("got RHS \n"); 
		//print_e(rhs[i], 0);
	}
}

/***********************************************************************************************/
/* Rule Matcher - matches a rule to a tree, remembering the values of the variables ************/
/* NOTE: This matcher supports "unification" where a variable may appear more than  ************/
/*       once on the left hand side (LHS) of a rule, if it matches to the same value ***********/
/*       everywhere it occurs.                                                      ************/
/*       Does not support "any" function matches.                                   ************/
/***********************************************************************************************/
exprnode *var[100];
int
matchrule(exprnode *e, exprnode *r)
{
	register int i;

	if(e == r) return 1;
	if(!e || !r) return 0;
	//printf("Matching %s vs %s\n", opmap[e->func].name, opmap[r->func].name);
	if(e->func != r->func) {
		//printf("failed func match\n");
		return 0;
	}
	if(e->count != r->count) {
		//printf("failed count match%d %d\n", e->count, r->count);
		return 0;
	}

	for(i=0; i<e->count; i++) {
		if(r->values[i].ep->func == OP_VAR) {
			if(var[r->values[i].ep->values[0].num] == 0) {
				var[r->values[i].ep->values[0].num] = e->values[i].ep;
				//printf("success - assign var\n");
				continue;
			} else if (var[r->values[i].ep->values[0].num] == e->values[i].ep) {
				/* Support Unification - variable may appear more than once on LHS */
				//printf("success - matching var\n");
				continue;
			}
			//printf("failed conflict\n");
			return 0; /* Conflicting assignment */
		}
		/* Some nodes dont really have subnodes */
		switch(e->func) {
		case OP_NULL:	 	printf("failed OP_NULL\n"); return 0;
		case OP_NUMBER:		if(e->values[0].num == r->values[0].num) return 1; else return 0;
		case OP_STRING:		if(!strcmp(e->values[0].data, r->values[0].data)) return 1; else return 0;
		case OP_COLNAME:	if(!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		case OP_TABLENAME:	if(!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		case OP_FNAME:		if(!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		}
		//printf("checking subnodes\n");
		if(!matchrule(e->values[i].ep, r->values[i].ep)) {
			//printf("subnode fail\n");
			return 0;
		}
	}	
	//printf("success\n");
	return 1;
}

/***********************************************************************************************/
/* The Rewriter - creates a new expression with all the variables replaced *********************/
/***********************************************************************************************/
exprnode *
rhs_with_vars(exprnode *r)
{
	exprnode *v1, *v2;
	
	if(!r) return 0;
	if(r->func == OP_VAR) {
		return var[r->values[0].num];
	}
	v1 = rhs_with_vars(r->values[0].ep);
	v2 = rhs_with_vars(r->values[1].ep);
	return (exprnode *)makeexpr(r->func, r->count, (int)v1, (int)v2);
}

/***********************************************************************************************/
/* Compilation step - try to make sure everything is implementable *****************************/
/***********************************************************************************************/
exprnode *
rcompile(exprnode *x)
{
	int i,j;
	exprnode *a1, *a2;

	if(!x) return 0;
	//printf("Compile on %s\n", opmap[x->func].name);

	/* Some nodes dont really have subnodes */
	switch(x->func) {
	case OP_NULL:	
	case OP_NUMBER:
	case OP_STRING:
	case OP_COLNAME:
	case OP_TABLENAME:
	case OP_FNAME:	
		return x;
	}

	/* Make sure the arguments are implementable */
	/* Use same tree if no changes */
	a1 = rcompile(x->values[0].ep); a2 = rcompile(x->values[1].ep);
	if((a1 != (x->values[0].ep)) || (a2 != (x->values[1].ep))) {
		x = (exprnode *)makeexpr(x->func, x->count, (int)a1, (int)a2);
	}

	/* Try rewrite if not implementable */
	if(!(opmap[x->func].flag & IMPLEMENTED)) {
		for(i=0;lhs[i];i++) {
			for(j=0; j<100; j++) var[j]=0;
			if(matchrule(x,lhs[i])) {
				//printf("matched rule %d\n", i);
				x = rhs_with_vars(rhs[i]);
				//print_e(x,0);
				x = rcompile(x);
				break;
			}
		}
	}
	
	return x;
}

exprnode *
compile(exprnode *x)
{
	printf("Before compilation\n");
	print_e(x,0);
	x = rcompile(x);
	printf("After compilation\n");
	print_e(x,0);
	return x;
}

exprnode *
optimize(exprnode *x)
{
	return x;
}
