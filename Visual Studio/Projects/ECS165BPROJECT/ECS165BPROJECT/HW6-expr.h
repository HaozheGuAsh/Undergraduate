#include <vector>
#include <string>
#include <string.h>
using namespace std;
/* Relational operators */
#define OP_SELECTION	1
#define OP_PROJECTION	2
#define OP_PRODUCT	3
#define OP_GROUP	4
#define OP_DELTA	5
#define OP_INSERT	6
#define OP_DELETE	7
#define OP_UPDATE	8
#define OP_SORT		9

/* Iteration */
#define OP_ITERATE	10
#define OP_OPEN		11
#define OP_GETNEXT	12
#define OP_CLOSE	13
#define OP_PROJECTROW	14
#define OP_SELECTROW	15
#define OP_INSERTROW	16
#define OP_DELETEROW	17
#define OP_FETCH1	18
#define OP_SORTSPEC	19

/* Standard arithmetic */
#define OP_EQUAL	20
#define OP_NOTEQ	21
#define OP_LEQ		22
#define OP_GEQ		23
#define OP_LT		24
#define OP_GT		25
#define	OP_PLUS		26
#define OP_BMINUS	27		/* Subtract */
#define OP_TIMES	28
#define OP_DIVIDE	29
#define OP_UMINUS	30		/* Unary minus, negate */
#define OP_AND		31
#define OP_OR		32
#define OP_NOT		33
#define OP_FCALL        34
#define OP_IN		35

/* String operators	*/
#define OP_STREQUAL	70
#define OP_STRNOTEQ	71
#define OP_STRLEQ	72
#define OP_STRGEQ	73
#define OP_STRLT	74
#define OP_STRGT	75
#define OP_STRCONCAT	76

/* Conversion operators */
#define	OP_ATOI		80
#define OP_ITOA		81

/* Transaction control */
#define OP_STXN		40
#define OP_COMMIT	41
#define OP_CLOSEALL	42

/* DDL */
#define OP_SET		50
#define OP_TABLENAME	51		/* Reference to a table */
#define OP_COLNAME	52		/* Reference to a column */
#define OP_OUTCOLNAME	53		/* Rename of column (AS operator) */
#define OP_AS		53		/* Rename of column (AS operator) */
#define OP_COLUMNDEF	54		/* A column definition (only to say if it is a key or primary key ) */
#define OP_CREATETABLE	55
#define OP_FNAME	56
#define OP_DROPTABLE	57
#define OP_SHOWTABLES	58
#define OP_DESCRIBE	59

/* Composition */
#define OP_RLIST	60		/* List in reverse order */

/* Literals */
#define	OP_STRING	90
#define OP_NUMBER	91
#define OP_NULL		92
#define OP_ROW		93

/* Additional codes */

#define OP_GETNEXT_ISCAN	100
#define OP_RANGE		101

#define OP_EOF		255
#define OP_ERROR	-1

typedef void *expr;

expr *makearray(expr rlist);
int listlen(expr rlist);
expr makeexpr(int , int , expr, expr);
void PrintTree(expr e, int tLevel);
extern int freen;

char * op_name(int op_num);
int opnum(char *str);
#define IMPLEMENTED	1
#define MAXDATA		255
#define MAXTABLES	100
#define MAXCOLS		100
#define MAXNODES	1000

class myopmap{
public:
	char *name;
	int	flag;

myopmap(){}
};


/*From expression.cpp*/
typedef struct {
	int tableid;
	int rowid;
	int diskaddr;
	int rowexp;
	char data[MAXCOLS][MAXDATA + 1];
} row;

typedef
struct expression {
	int func;
	int count;
	union {
		int num;
		char *name;
		char *data;
		struct expression *ep;
		row *rowp;
	} values[3];
} exprnode;

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
};

struct column {
	char col_name[MAXDATA + 1];
};
class mytable
{
public:
	vector<string> tablename;
	vector<vector<string> > colname;

};
void
readcsvhdr(struct table *tp);
exprnode* subevalexpr(exprnode *x, row *context);
//int makeexpr(int, int, int, int);


/*From rewrite.cpp*/
exprnode* subcompile(exprnode *x);