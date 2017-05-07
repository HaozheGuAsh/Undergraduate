#include <iostream>
#include "stdlib.h"
#include <stdio.h>
#include "string.h"
#include <vector>
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include <inttypes.h>
#include "HW6-expr.h"
//#include "HW4-expression.h"

using namespace std;
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
int rulecnt = 4;

void
init_rules();
/*global*/
extern struct myopmap opmap[256];

/*char *
op_name(int op_num)
{
	if (op_num < 1 || op_num > OP_EOF) {
		return "INVALID";
	}
	return opmap[op_num].name;
}

int
opnum(char *str)
{
	int i;
	for (i = 1; i<256; i++) {
		if (!opmap[i].name) continue;
		if (!strcmp(opmap[i].name, str)) return i;
	}
	return 0;
}
*/
/***********************************************************************************************/
/* Function to convert rules into an expression tree *****************************/
/***********************************************************************************************/
exprnode *
getexpr(char *str)
{
	int off = 0, op;
	int n, rv;
	char opname[MAXDATA + 1];
	exprnode *v1, *v2;
	int varnum;

	n = 0; rv = sscanf(str, " ( %[a-zA-Z0-9] %n", opname, &n);
	if (rv != 1) { printf("Badly formed rule segment %s\n", str); exit(1); }
	op = opnum(opname);
	strcpy(str, str + n);
	n = 0; rv = sscanf(str, " ) %n", &n);
	if (n) {
		strcpy(str, str + n);
		return (exprnode *)makeexpr(op, 0, 0, 0);
	}

	/* One argument *************************************************************/
	n = 0; rv = sscanf(str, " $%d %n", &varnum, &n);
	if (rv == 1) {
		strcpy(str, str + n);
		v1 = (exprnode *)makeexpr(OP_VAR, 1, (expr)varnum, (expr)0);
	}
	else {
		n = 0; rv = sscanf(str, " ( %n", &n);
		if (n) {
			v1 = getexpr(str);
		}
		else  { printf("Badly formed rule segment %s\n", str); exit(1); }
	}
	n = 0; rv = sscanf(str, " ) %n", &n);
	if (n) {
		strcpy(str, str + n);
		return (exprnode *)makeexpr(op, 1, (expr)v1, 0);
	}

	/* Two arguments ************************************************************/
	n = 0; rv = sscanf(str, " $%d %n", &varnum, &n);
	if (rv == 1) {
		strcpy(str, str + n);
		v2 = (exprnode *)makeexpr(OP_VAR, 1, (expr)varnum, (expr)0);
	}
	else {
		n = 0; rv = sscanf(str, " ( %n", &n);
		if (n) {
			v2 = getexpr(str);
		}
		else  { printf("Badly formed rule segment %s\n", str); exit(1); }
	}
	n = 0; rv = sscanf(str, " ) %n", &n);
	if (n) {
		strcpy(str, str + n);
		return (exprnode *)makeexpr(op, 2, (expr)v1, (expr)v2);
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
	//FILE *fid;
	int i = 0;
	int c;
	char *rp;
	char buf[MAXDATA + 1];
	/*fid = fopen("data/rules", "r");
	if (fid) {
		while ((c = fgetc(fid))>0) {
			if (c == '\n') {
				buf[i] = 0;
				rules[rulecnt] = (char*)malloc(strlen(buf) + 1);
				strcpy(rules[rulecnt], buf);
				i = 0; rulecnt++;
				continue;
			}
			buf[i++] = toupper(c);
		}
		fclose(fid);
	}*/

	for (i = 0; i<MAXRULES; i++) {
		if (!rules[i]) return;
		//printf("Loading rule: %s\n", rules[i]);
		rp = strstr(rules[i], "=>");
		strncpy(buf, rules[i], rp - rules[i]);
		lhs[i] = getexpr(buf);
		//printf("got LHS \n"); 
		//print_e(lhs[i], 0);
		strcpy(buf, rp + 2);
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
	//cout << "in match rule" << endl;
	if (e == r) return 1;
	if (!e || !r) return 0;
	//printf("Matching %s vs %s\n", opmap[e->func].name, opmap[r->func].name);
	if (e->func != r->func) {
		//printf("failed func match\n");
		return 0;
	}
	if (e->count != r->count) {
		//printf("failed count match%d %d\n", e->count, r->count);
		return 0;
	}

	for (i = 0; i<e->count; i++) {
		if (r->values[i].ep->func == OP_VAR) {
			if (var[r->values[i].ep->values[0].num] == 0) {
				var[r->values[i].ep->values[0].num] = e->values[i].ep;
				//printf("success - assign var\n");
				continue;
			}
			else if (var[r->values[i].ep->values[0].num] == e->values[i].ep) {
				/* Support Unification - variable may appear more than once on LHS */
				//printf("success - matching var\n");
				continue;
			}
			//printf("failed conflict\n");
			return 0; /* Conflicting assignment */
		}
		/* Some nodes dont really have subnodes */
		switch (e->func) {
		case OP_NULL:	 	printf("failed OP_NULL\n"); return 0;
		case OP_NUMBER:		if (e->values[0].num == r->values[0].num) return 1; else return 0;
		case OP_STRING:		if (!strcmp(e->values[0].data, r->values[0].data)) return 1; else return 0;
		case OP_COLNAME:	if (!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		case OP_TABLENAME:	if (!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		case OP_FNAME:		if (!strcmp(e->values[0].name, r->values[0].name)) return 1; else return 0;
		}
		//printf("checking subnodes\n");
		if (!matchrule(e->values[i].ep, r->values[i].ep)) {
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

	if (!r) return 0;
	if (r->func == OP_VAR) {
		return var[r->values[0].num];
	}
	v1 = rhs_with_vars(r->values[0].ep);
	v2 = rhs_with_vars(r->values[1].ep);
	return (exprnode *)makeexpr(r->func, r->count, (expr)v1, (expr)v2);
}

/***********************************************************************************************/
/* Compilation step - try to make sure everything is implementable *****************************/
/***********************************************************************************************/
exprnode *
rcompile(exprnode *x)
{
	int i, j;
	exprnode *a1, *a2;

	if (!x) return 0;
	//printf("Compile on %s\n", opmap[x->func].name);

	/* Some nodes dont really have subnodes */
	switch (x->func) {
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
	if ((a1 != (x->values[0].ep)) || (a2 != (x->values[1].ep))) {
		x = (exprnode *)makeexpr(x->func, x->count, (expr)a1, (expr)a2);
	}

	/* Try rewrite if not implementable */
	if (!(opmap[x->func].flag & IMPLEMENTED)) {
		for (i = 0; lhs[i]; i++) {
			for (j = 0; j<100; j++) var[j] = 0;
			if (matchrule(x, lhs[i])) {
				printf("matched rule %d\n", i);
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
subcompile(exprnode *x)
{
	init_rules();
	//printf("Before compilation\n");
	//PrintTree(x, 0);
	x = rcompile(x);
	//printf("After compilation\n");
	PrintTree(x, 0);
	return x;
}

exprnode *
optimize(exprnode *x)
{
	return x;
}
