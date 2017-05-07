/* Copyright (c) 2016 - Niket K. Patwardhan */
/* You are permitted to adapt the contents of this file for my database class */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"

#include "HW6-expr.h"
#include "HW6-expression.h"
#include "HW6-buf.h"

extern int debug;
extern exprnode *
makeexprnode(int,int,exprnode *,exprnode *);
int hasspecial = 0;

/* Find an indexed column of the table ********************************/
char *
hasindex(exprnode *t)
{
	char *col;

	if(!t) return 0;
	if(t->func == OP_GETNEXT) {
		if(t->values[0].ep && t->values[0].ep->func == OP_TABLENAME) {
			col = (char *)get_idx_col(t->values[0].ep->values[0].name);
			return col;
		}
	}
	return 0;
}

int
hascol(exprnode *ep, char *col)
{
	if(!ep) return 0;
	if(ep->func == OP_COLNAME && !strcmp(col, ep->values[0].name)) return 1;
	if(ep->func == OP_NOT || ep->func == OP_UMINUS) return hascol(ep->values[0].ep, col);
	if(ep->count < 2) return 0;
	if(hascol(ep->values[0].ep, col) || hascol(ep->values[1].ep, col)) return 1;
}

exprnode *
insert_into_andchain(exprnode *e1, exprnode *chain, char *col)
{
	int csv, isv;

	//printf("::insert_into_andchain:-----------------------------------------------------------\n");
	//print_e(e1, 0);
	//printf("\n-----------\n");
	//print_e(chain, 0);
	//printf("\n");
	if(!chain) return e1;
	switch(chain->func) {
	default: 	return makeexprnode(OP_AND, 2, e1, chain);
	case OP_EQUAL:	csv = 1; break;
	case OP_GT:
	case OP_GEQ:	csv = 2; break;
	case OP_LT:
	case OP_LEQ:	csv = 3; break;
	case OP_AND:	switch(chain->values[0].ep->func) {
			case OP_EQUAL:	csv = 1; break;
			case OP_GT:
			case OP_GEQ:	csv = 2; break;
			case OP_LT:
			case OP_LEQ:	csv = 3; break;
			default:	csv = 4; break;
			}
			break;
	}
	if(chain->func != OP_AND) {
		if(chain->values[0].ep->func != OP_COLNAME) csv = 4;
		else { 
			if(strcmp(col, chain->values[0].ep->values[0].name)) csv = 4;
			if(chain->values[1].ep->func != OP_STRING &&
			   chain->values[1].ep->func != OP_NUMBER) csv = 4;
		}
	} else {
		if(chain->values[0].ep->values[0].ep->func != OP_COLNAME) csv = 4;
		else { 
			if(strcmp(col, chain->values[0].ep->values[0].ep->values[0].name)) csv = 4;
			if(chain->values[0].ep->values[1].ep->func != OP_STRING &&
			   chain->values[0].ep->values[1].ep->func != OP_NUMBER) csv = 4;
		}
	}

	switch(e1->func) {
	default: 	isv = 4; break;
	case OP_EQUAL:	isv = 1; break;
	case OP_GT:
	case OP_GEQ:	isv = 2; break;
	case OP_LT:
	case OP_LEQ:	isv = 3; break;
	}
	if(e1->func != OP_AND) {
		if(e1->values[0].ep->func != OP_COLNAME) isv = 4;
		else { 
			if(strcmp(col, e1->values[0].ep->values[0].name)) isv = 4;
			if(e1->values[1].ep->func != OP_STRING &&
			   e1->values[1].ep->func != OP_NUMBER) isv = 4;
		}
	} else {
		printf("::insert_into_andchain: Normally, we should not get here\n");
		if(e1->values[0].ep->values[0].ep->func != OP_COLNAME) isv = 4;
		else { 
			if(strcmp(col, e1->values[0].ep->values[0].ep->values[0].name)) isv = 4;
			if(e1->values[0].ep->values[1].ep->func != OP_STRING &&
			   e1->values[0].ep->values[1].ep->func != OP_NUMBER) isv = 4;
		}
	}

	if(isv <= csv) return makeexprnode(OP_AND, 2, e1, chain);
	if(chain->func == OP_AND) {
		return makeexprnode(OP_AND, 2, chain->values[0].ep,
				    insert_into_andchain(e1, chain->values[1].ep, col));
	}
	return makeexprnode(OP_AND, 2, chain, e1);
}

/* Work on the selection condition */
/* Look for (col >= value), (col <= value), (col == value), (col > value), and (col < value) */
/* Bubble them to top left */
exprnode *
bring2left(exprnode *sp, char *col)
{
	exprnode *e1, *e2, *e3;
	int op;

	if(!sp) return 0;
	if(sp->count < 2) return sp;

	/* Some operators are not symmetric in an exchange of arguments */
	op = sp->func;
	switch(op) {
	default:	return sp;	/* Exchange not possible */
	/* Commutative operators */
	case OP_EQUAL:	op = OP_EQUAL; break;
	case OP_NOTEQ:	op = OP_NOTEQ; break;
	case OP_PLUS:	op = OP_PLUS; break;
	case OP_TIMES:	op = OP_TIMES; break;
	case OP_AND:	op = OP_AND; break;
	case OP_OR:	op = OP_OR; break;
	/* Non-commutative operator, but there is an exchange equivalent */
	case OP_LEQ:	op = OP_GEQ; break;
	case OP_GEQ:	op = OP_LEQ; break;
	case OP_LT:	op = OP_GT; break;
	case OP_GT:	op = OP_LT; break;
	}

	/* At this point, all remaining operators allow an exchange of arguments */
	if(!hascol(sp->values[1].ep, col)) {
		e2 = sp->values[1].ep;
		e3 = 0;
	} else {
		e2 = bring2left(sp->values[1].ep, col);
		e3 = e2->values[0].ep;
	}

	if(!hascol(sp->values[0].ep, col)) {
		if(!e3) return sp;

		/* Right has references to the column, but left does not. Need to do an exchange */
		if(sp->func != OP_AND) {
			return makeexprnode(op, 2, e2, sp->values[0].ep);
		}
		e2 = insert_into_andchain(sp->values[0].ep, e2, col);
		return e2;
	}

	/* Left side has references to the column */
	e1=bring2left(sp->values[0].ep, col);
	if(sp->func != OP_AND) {
		if(e1==sp->values[0].ep && e2==sp->values[1].ep) return sp;
		return makeexprnode(sp->func, 2, e1, e2);
	}

	if(!e3) {
		/* But RHS has none */
		if(e1->func != OP_AND) {
			/* Only need to rearrange LHS, dont create new node if no rearrangement */
			if(e1==sp->values[0].ep) return sp;
			return makeexprnode(OP_AND, 2, e1, sp->values[1].ep);
		}

		e3 = e1->values[0].ep;
		/* AND rollover - e3 needs to be top left, and e2 bottom right */
		return makeexprnode(OP_AND, 2, e3, makeexprnode(OP_AND, 2, e1->values[1].ep, e2));
	}

	/* Both have references to the column */
	/* Linearize the ANDs into a chain. GT and LT dealt with by inserting NOTEQ */
	while(e1->func == OP_AND) {
		e2 = insert_into_andchain(e1->values[0].ep, e2,col);
		if(e1->func == OP_LT || e1->func == OP_GT) {
			e3 = makeexprnode(OP_NOTEQ, 2, e1->values[0].ep, e1->values[1].ep);
			e2 = insert_into_andchain(e3, e2, col);
		}
		e1 = e1->values[1].ep;
	}
	e2 = insert_into_andchain(e1, e2,col);
	if(e1->func == OP_LT || e1->func == OP_GT) {
		e3 = makeexprnode(OP_NOTEQ, 2, e1->values[0].ep, e1->values[1].ep);
		e2 = insert_into_andchain(e3, e2, col);
	}
	return e2;
}

void find_special(expr e, int lev)
{
	struct expression *ep = e;
	register int i, slev = lev;

	if (!ep) { return; }
	switch (ep->func) {

	case OP_IN: hasspecial = 1; return;
		/* Literals */
	case 257:	 return;
	case OP_NUMBER:	 return;
	case OP_STRING:	 return;
	case OP_NULL:	 return;

		/* Names */
	case OP_COLNAME:
		//printf("COLUMN:%s ", ep->values[0].name); 
		return;
	case OP_TABLENAME:
		//printf("TABLE:%s ", ep->values[0].name);
		return;
	case OP_FNAME:
		//printf("FUNC:%s ", ep->values[0].name);
		return;

		/* Relational operators */
	case OP_PROJECTROW:
		//printf("(PROJECT1 \n"); 
		break;
	case OP_PROJECTION:
		//printf("(PROJECT \n");
		break;
	case OP_SELECTROW:
		//printf("(SELECT1 \n");
		break;
	case OP_SELECTION:
		//printf("(SELECT \n"); 
		break;
	case OP_PRODUCT:
		//printf("(PRODUCT \n"); 
		break;
	case OP_SORT:
		//printf("(SORT \n"); 
		break;
	case OP_GROUP:
		//printf("(GROUP \n");
		break;
	case OP_DELTA:
		//printf("(DELTA \n"); 
		break;
	case OP_CREATETABLE:
		//printf("(CREATETABLE \n");
		break;
	case OP_INSERTROW:
		//printf("(INSERTROW \n");
		break;
	case OP_GETNEXT:
		//printf("(GETNEXT \n"); 
		break;
	case OP_ITERATE:
		//printf("(ITERATE \n");
		break;

	case OP_PLUS:	//printf("(+ \n");
		break;
	case OP_BMINUS:	//printf("(- \n"); 
		break;
	case OP_TIMES:	//printf("(* \n");
		break;
	case OP_DIVIDE:	//printf("(/ \n"); 
		break;

	case OP_AND:	//printf("(AND \n");
		break;
	case OP_OR:	//printf("(OR \n"); 
		break;
	case OP_NOT:	//printf("(! \n"); 
		break;
	case OP_GT:	//printf("(> \n"); 
		break;
	case OP_LT://	printf("(< \n"); 
		break;
	case OP_EQUAL:	//printf("(== \n");
		break;
	case OP_NOTEQ:	//printf("(<> \n"); 
		break;
	case OP_GEQ:	//printf("(>= \n"); 
		break;
	case OP_LEQ:	//printf("(<= \n"); 
		break;

	case OP_SORTSPEC:
		//printf("(SORTSPEC \n"); 
		break;

	case OP_COLUMNDEF:
		//printf("(COLSPEC \n"); 
		break;

	case OP_OUTCOLNAME:
		//printf("(AS \n");
		break;

	case OP_RLIST:	//printf("(RLIST ");
		find_special(ep->values[0].ep, lev + 7);
		//putchar('\n');
		//for (i = 0; i<lev; i++) putchar(' ');
		find_special(ep->values[1].ep, lev);
		//putchar(')');
		return;
	case OP_GETNEXT_ISCAN:
		//printf("(ISCAN \n");
		break;
	case OP_RANGE:	//printf("(RANGE %s - %s)\n", ep->values[0].data, ep->values[1].data);
		return;
	default:	//printf("(%s \n", op_name(ep->func)); 
		break;
	}
	lev += 2;
	//for (i = 0; i<lev; i++) putchar(' ');
	for (i = 0; i<ep->count; i++) {
		find_special(ep->values[i].ep, lev + 2); //putchar(' ');
	}
	//putchar('\n');
	//for (i = 0; i<slev; i++) putchar(' ');
	//putchar(')');
}
exprnode *
optimize(exprnode *x)
{
	/* Heuristic optimizer */

	exprnode *left, *right, *e1, *e2, *e3,*saved;
	char *tbl, *col;
	char *idxc, *skey, *ekey, *ckey;
	int op;
	//int isdistinct;

	if(!x) return x;
	if (x->func == OP_DISTINCT) 
	{
		return makeexprnode(OP_DISTINCT, 1, optimize(x->values[0].ep), 0);
	}
	if (x->func == OP_GROUP)
	{
		//printf("meet group\n");
		x = makeexprnode(OP_GROUP, 2, optimize(x->values[0].ep), x->values[1].ep);
	}
	if (x->func == OP_ITERATE)
	{
		find_special(x, 0);
		if (hasspecial == 1)
		{
			hasspecial = 0;
			return x;
		}
		
	}
	if(x->count < 2) return x;

	switch(x->func) {
	case OP_SELECTROW:
			/* If there is a selection on a table which has an index,
				we move around the pieces of the selection until the indexed column is first. */
			//print_e(x, 0); printf("\n\n");
			left = x->values[0].ep;
			right = x->values[1].ep;
			if(col=hasindex(left)) {
				//printf("::optimize: found indexed column in table %s\n", tbl);
				tbl = left->values[0].ep->values[0].name;
				right = bring2left(right,col);
				//print_e(right, 0);
				//printf("\n::optimize: that is the new selection clause\n");
				idxc = (char *)malloc(MAXDATA*2+2);
				strcpy(idxc, tbl);
				strcat(idxc, ".");
				strcat(idxc, col);

				/* Determine the selection range for iscan, start with maximum range */
				/* Look through the AND chain setting up the values for skey and ekey */
				skey = ""; ekey = 0;
				for(;right && right->func == OP_AND; right = right->values[1].ep) {
					e1 = right->values[0].ep;
					if(!e1) continue;	/* Actually should not happen */
					switch(e1->func) {
					default:	op = 0; break;
					case OP_EQUAL:	op = OP_EQUAL; break;
					case OP_GT:	op = OP_GT; break;
					case OP_GEQ:	op = OP_GEQ; break;
					case OP_LT:	op = OP_LT; break;
					case OP_LEQ:	op = OP_LEQ; break;
					}
					if(!op) break;
					if(e1->values[0].ep->func != OP_COLNAME) break;
					if(strcmp(e1->values[0].ep->values[0].name, col)) break;
					if(e1->values[1].ep->func != OP_STRING && e1->values[1].ep->func != OP_NUMBER) break;

					/* This is a condition that iscan can deal with */
					//ckey = e1->values[1].ep->values[0].data;
					if(e1->values[1].ep->func == OP_STRING) ckey = e1->values[1].ep->values[0].data;
					else {
						ckey = (char *)malloc(20);
						sprintf(ckey, "%d",  e1->values[1].ep->values[0].num);
					}
					//printf("HERE1  op %d  skey %s ckey %s\n",op,skey,ckey);
					/* If we detect a selection condition that is always false, the tree shrinks to EOF */
					switch(op) {
					case OP_EQUAL:	
						//printf("equal cmp %s > %s", skey, ckey);
							if(atoi(skey)>atoi(ckey))
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && atoi(ekey)<atoi(ckey))
								return makeexprnode(OP_EOF,0,0,0);
							skey = ekey = ckey;
							break;
					case OP_GT:	
							if(ekey && atoi(ekey)<=atoi(ckey))
								return makeexprnode(OP_EOF,0,0,0);
							if(atoi(skey)>=atoi(ckey))
								break;
							skey = ckey;
							break;
					case OP_GEQ:	
							if(ekey && atoi(ekey)<atoi(ckey))
								return makeexprnode(OP_EOF,0,0,0);
							if(atoi(skey)>=atoi(ckey))
								break;
							skey = ckey;
							break;
					case OP_LT:	
							if(atoi(skey)>=atoi(ckey))
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && atoi(ekey)<=atoi(ckey))
								break;
							ekey = ckey;
							break;
					case OP_LEQ:	
							if(atoi(skey)>atoi(e1->values[1].ep->values[0].data))
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && atoi(ekey)<=atoi( ckey))
								break;
							ekey = ckey;
							break;
					}
				}
				//printf("HERE2\n");
				/* Deal with the tail of the AND chain */
				if(right && right->func != OP_AND) switch (1) {
				default:
					e1 = right;
					switch(e1->func) {
					default:	op = 0; break;
					case OP_EQUAL:	op = OP_EQUAL; break;
					case OP_GT:	op = OP_GT; break;
					case OP_GEQ:	op = OP_GEQ; break;
					case OP_LT:	op = OP_LT; break;
					case OP_LEQ:	op = OP_LEQ; break;
					}
					if(!op) break;
					if(e1->values[0].ep->func != OP_COLNAME) break;
					if(strcmp(e1->values[0].ep->values[0].name, col)) break;
					if(e1->values[1].ep->func != OP_STRING && e1->values[1].ep->func != OP_NUMBER) break;
					right = 0;	/* We absorbed the entire condition, there is nothing remaining */
					//ckey = e1->values[1].ep->values[0].data;
					if (e1->values[1].ep->func == OP_STRING) ckey = e1->values[1].ep->values[0].data;
					else {
						ckey = (char *)malloc(20);
						sprintf(ckey, "%d", e1->values[1].ep->values[0].num);
					}
					/* This is a condition that iscan can deal with */
					/* If we detect a selection condition that is always false, the tree shrinks to EOF */
					switch(op) {
					case OP_EQUAL:	
							if(strcmp(skey, ckey)>0)
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && strcmp(ekey, ckey) < 0)
								return makeexprnode(OP_EOF,0,0,0);
							skey = ekey = ckey;
							break;
					case OP_GT:	
							if(ekey && strcmp(ekey, ckey) <= 0)
								return makeexprnode(OP_EOF,0,0,0);
							if(strcmp(skey, ckey)>=0)
								break;
							skey = ckey;
							break;
					case OP_GEQ:	
							if(ekey && strcmp(ekey, ckey) < 0)
								return makeexprnode(OP_EOF,0,0,0);
							if(strcmp(skey, ckey)>=0)
								break;
							skey = ckey;
							break;
					case OP_LT:	
							if(strcmp(skey, ckey)>=0)
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && strcmp(ekey, ckey) <= 0)
								break;
							ekey = ckey;
							break;
					case OP_LEQ:	
							if(strcmp(skey, e1->values[1].ep->values[0].data)>0)
								return makeexprnode(OP_EOF,0,0,0);
							if(ekey && strcmp(ekey, ckey) <= 0)
								break;
							ekey = ckey;
							break;
					}
				}

				/* Then we combine the selection and table scan getnext into an index scan */
				
				//printf("HERE3\n");
				if(skey[0] != 0 || ekey) {
					/*if (skey[0] == 0)
					{
						char ary[5];
						snprintf(ary, 10, "%d", 0);
						skey = &ary[0];
					}*/
					//printf("skey is %s   ckey is %s", skey, ckey);
					e1 = makeexprnode(OP_COLNAME, 1, (exprnode *)idxc, 0);
					e2 = makeexprnode(OP_RANGE, 0, (exprnode *)skey, (exprnode *)ekey);
					e3 = makeexprnode(OP_GETNEXT_ISCAN, 2, e1, e2);

					/* Apply the rest of the selection to what comes out of this combination */
					if(right) e1 = makeexprnode(OP_SELECTROW, 2, e3, right);
					else e1 = e3;

					/* For now try this */
					//print_e(e1); 
					printf("\n::optimize done\n");
					printf("USING INDEX SELECTION\n");
					return e1;
				}
				/* Dont want to do iscan, do default optimization */
			}
	default:	
			//printf("current node is %s\n", op_name(x->func));
			if (x->func >= 103){  return x; }//printf("just return \n");
			//printf("!!!!!!!DOING DEFAULT\n");
			left=optimize(x->values[0].ep);
			right=optimize(x->values[1].ep);
			/* Dont do unnecessary reconstruction */
			if(left==x->values[0].ep && right==x->values[1].ep)
				return x;
			/*else if (isdistinct == 1)
			{
				printf("just below distinct\n");
				return makeexprnode(OP_DISTINCT, 1, makeexprnode(x->func, x->count, left, right), 0);
			}*/
			return makeexprnode(x->func, x->count, left, right);

	}
	return x;
}
