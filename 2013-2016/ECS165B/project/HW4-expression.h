typedef struct {
	int tableid;
	int rowid;
	int diskaddr;
	int rowexp;
	char data[MAXCOLS][MAXDATA+1];
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
