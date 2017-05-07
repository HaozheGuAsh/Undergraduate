typedef struct {
	char data[MAXCOLS][MAXDATA+1];
	int tableid;
	int rowid;
	int diskaddr;
	int rowexp;
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

char *op_name(int);
extern exprnode ERROR_OUTOFNODES;
