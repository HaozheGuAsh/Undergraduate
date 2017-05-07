#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130925

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0


#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define IDENT 257
#define NUMBER 258
#define STRING 259
#define NUL 260
#define SELECT 261
#define AS 262
#define FROM 263
#define WHERE 264
#define GROUP 265
#define BY 266
#define HAVING 267
#define ORDER 268
#define ASC 269
#define DESC 270
#define INSERT 271
#define INTO 272
#define VALUES 273
#define UPDATE 274
#define SET 275
#define DELETE 276
#define CREATE 277
#define TABLE 278
#define DESCRIBE 279
#define SHOW 280
#define TABLES 281
#define DROP 282
#define UNIQUE 283
#define DISTINCT 284
#define PRIMARY 285
#define KEY 286
#define IN 287
#define NOTEQ 288
#define GEQ 289
#define LEQ 290
#define AND 291
#define OR 292
#define NOT 293
#define QUIT 294
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    5,    6,    6,    6,    6,    6,
    6,    6,    6,   10,   10,   11,   11,    8,    8,    8,
    4,   14,   14,   16,   16,   15,   15,   18,   18,   19,
   17,   17,   20,   20,   21,   21,   21,   21,   21,   21,
   12,   12,   22,   22,   13,   13,    3,    3,    3,    3,
    3,    3,    7,    7,   23,   23,   23,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,
};
static const short yylen[] = {                            2,
    0,    2,    3,    8,    5,    2,    9,    6,    7,    3,
    3,    4,    2,    1,    1,    1,    3,    5,    5,    5,
    3,    3,    1,    4,    3,    1,    3,    1,    1,    1,
    8,    0,    2,    0,    2,    0,    3,    1,    3,    1,
    0,    3,    1,    3,    1,    2,    2,    1,    2,    2,
    1,    3,    3,    1,    1,    3,    1,    1,    1,    3,
    3,    3,    1,    3,    1,    2,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
static const short yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    2,    0,   13,    0,   29,   30,    0,   54,    0,
   16,   23,    0,   51,    0,   14,    0,    0,    0,    0,
    0,    0,    3,    6,    0,    0,    0,    0,    0,    0,
   69,   72,   73,   78,   79,   68,   70,   71,   74,   75,
   76,   77,    0,    0,    0,    0,    0,    0,    0,   10,
   11,    0,   25,    0,    0,   21,   22,   15,   53,    0,
   28,    0,   17,   55,    0,   52,    0,    0,    0,    0,
    0,   12,   24,    0,    0,    0,    0,    0,    0,    0,
    0,    5,    0,    0,    0,    0,   63,    0,   20,   19,
   18,    0,   56,    0,    0,   57,   58,   59,    0,    0,
    8,    0,   66,    0,    0,    0,    0,    0,    0,    0,
    0,   67,    9,   64,   40,    0,   38,    0,    0,   31,
    4,   60,   61,   62,    0,    0,    0,    7,   39,    0,
    0,    0,   43,   46,   47,   49,   50,    0,   44,
};
static const short yydgoto[] = {                          1,
   12,   27,  109,   13,   19,   20,   96,   21,   53,   22,
   65,   23,   75,   90,  105,  118,  130,  126,  127,  142,
  143,   24,   97,
};
static const short yysindex[] = {                         0,
  -94,  -47,   55, -255, -233, -227, -240, -233, -236, -225,
    7,    0,   32,    0,   22,    0,    0,   33,    0,    9,
    0,    0,    3,    0, -233,    0, -207, -233, -233,   38,
   61, -233,    0,    0,   62,   22,   69,  -34, -133,   91,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   87, -233,   55, -251, -133, -113,  121,    0,
    0,  107,    0,   51,   73,    0,    0,    0,    0,  -87,
    0,   33,    0,    0,  -29,    0,  130,  122,  123,   90,
 -133,    0,    0,   90,  146,  149,  -12,   90, -233,  -74,
 -184,    0,   90,   18, -126,   75,    0,   51,    0,    0,
    0,   51,    0,  -73,  -75,    0,    0,    0,   95,   39,
    0,  -92,    0,  136, -133, -133,   90,  -72,  138, -102,
   90,    0,    0,    0,    0,  154,    0,   51,  -67,    0,
    0,    0,    0,    0,   45, -133,  -89,    0,    0,  -97,
  -91,  157,    0,    0,    0,    0,    0,  -89,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -3,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -41,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  105,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -36,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -25,
    0,    0,    0,    0,  109,    0,    0,  111,    0,    0,
    0,  -27,    0,    0,  -16,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   81,    0,    0,
    0,    0,    0,    0,    0,   -4,    0,    5,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   74,
  104,   82,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  100,    0,   65,   28,   54,    0,  150,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   66,    0,
   56,  151,   92,
};
#define YYTABLESIZE 349
static const short yytable[] = {                         28,
   28,   28,   28,   28,   32,   28,   67,   51,   49,    3,
   50,   14,   52,   33,   89,   36,   25,   28,   28,   28,
   28,   77,   32,   26,   34,   48,   46,   47,  101,   51,
   49,   33,   50,   36,   52,   28,   37,   29,   28,   28,
   15,   28,   34,   28,   31,   35,   55,   48,   46,   47,
   51,   49,   32,   50,   37,   52,   28,   28,   28,   51,
   49,   35,   50,   35,   52,   33,   69,   57,   48,   46,
   47,   38,   18,  106,  107,  108,  111,   48,   46,   47,
   51,   49,   37,   50,   79,   52,   51,   49,   64,   50,
   34,   52,   51,   49,   18,   50,   60,   52,   48,   46,
   47,   18,   63,  138,   48,   46,   47,   30,   95,   66,
   48,   46,   47,   83,   45,  114,   84,   45,  115,   61,
   78,   41,   42,   68,   56,   87,   72,   58,   59,   18,
   70,   62,   45,   94,   85,  119,   86,   98,  120,   41,
   42,  102,   95,  125,   48,   26,  110,   48,   26,   65,
   80,   27,   65,   74,   27,  132,  133,  134,  112,  113,
   81,    2,   48,  125,  141,   82,    3,   68,  140,   91,
  128,  144,  145,    3,  135,  141,    4,  146,  147,    5,
   92,    6,    7,   93,    8,    9,   99,   10,  103,  100,
  104,  117,  116,  122,  123,  129,  131,  136,  137,   11,
  148,  139,   73,  149,    0,   76,  124,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   28,   28,    0,   28,   28,    0,   32,    0,
   32,   32,    0,    0,   88,    0,    0,   33,    0,   33,
   33,   36,   36,    0,    0,   28,   28,   28,   28,   28,
   28,   34,   40,   41,   42,   43,   44,   45,   28,   15,
    0,    0,   37,   37,    0,   54,    0,    0,    0,    0,
   39,    0,   35,    0,   40,   41,   42,   43,   44,   45,
    0,    0,    0,   28,   28,   28,   28,   28,   28,   36,
   16,   17,    0,    3,    0,   40,   41,   42,   43,   44,
   45,    0,  121,    0,   40,   41,   42,   43,   44,   45,
    0,   15,   16,   17,    0,    0,    0,    0,   36,   16,
   17,    0,    0,    0,    0,   40,   41,   42,   43,   44,
   45,   40,   41,   42,   43,   44,   45,   40,   41,   42,
   43,   44,   45,   71,   16,   17,   36,   16,   17,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   41,   47,   41,   42,   43,  261,
   45,   59,   47,   41,   44,   41,  272,   59,   60,   61,
   62,  273,   59,  257,   41,   60,   61,   62,   41,   42,
   43,   59,   45,   59,   47,  263,   41,  278,   42,   43,
   44,   45,   59,   47,  281,   41,   44,   60,   61,   62,
   42,   43,  278,   45,   59,   47,   60,   61,   62,   42,
   43,   40,   45,   59,   47,   59,   39,  275,   60,   61,
   62,   18,   40,  258,  259,  260,   59,   60,   61,   62,
   42,   43,   18,   45,   57,   47,   42,   43,   35,   45,
   59,   47,   42,   43,   40,   45,   59,   47,   60,   61,
   62,   40,   41,   59,   60,   61,   62,    8,   81,   41,
   60,   61,   62,   41,   41,   41,   44,   44,   44,   59,
   56,   41,   41,  257,   25,   72,   40,   28,   29,   40,
   40,   32,   59,   80,   70,   41,   72,   84,   44,   59,
   59,   88,  115,  116,   41,   41,   93,   44,   44,   41,
  264,   41,   44,   54,   44,  258,  259,  260,  285,  286,
   40,  256,   59,  136,  137,   59,  261,  257,  258,   40,
  117,  269,  270,  261,  121,  148,  271,  269,  270,  274,
   59,  276,  277,   61,  279,  280,   41,  282,   89,   41,
  265,  267,  266,  286,   59,  268,   59,   44,  266,  294,
   44,  136,   53,  148,   -1,   55,  115,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  264,  265,   -1,  267,  268,   -1,  265,   -1,
  267,  268,   -1,   -1,  264,   -1,   -1,  265,   -1,  267,
  268,  267,  268,   -1,   -1,  287,  288,  289,  290,  291,
  292,  268,  287,  288,  289,  290,  291,  292,  262,  263,
   -1,   -1,  267,  268,   -1,  263,   -1,   -1,   -1,   -1,
  262,   -1,  268,   -1,  287,  288,  289,  290,  291,  292,
   -1,   -1,   -1,  287,  288,  289,  290,  291,  292,  257,
  258,  259,   -1,  261,   -1,  287,  288,  289,  290,  291,
  292,   -1,  264,   -1,  287,  288,  289,  290,  291,  292,
   -1,  257,  258,  259,   -1,   -1,   -1,   -1,  257,  258,
  259,   -1,   -1,   -1,   -1,  287,  288,  289,  290,  291,
  292,  287,  288,  289,  290,  291,  292,  287,  288,  289,
  290,  291,  292,  257,  258,  259,  257,  258,  259,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 294
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"IDENT","NUMBER","STRING","NUL","SELECT","AS","FROM","WHERE",
"GROUP","BY","HAVING","ORDER","ASC","DESC","INSERT","INTO","VALUES","UPDATE",
"SET","DELETE","CREATE","TABLE","DESCRIBE","SHOW","TABLES","DROP","UNIQUE",
"DISTINCT","PRIMARY","KEY","IN","NOTEQ","GEQ","LEQ","AND","OR","NOT","QUIT",
};
static const char *yyrule[] = {
"$accept : program",
"program :",
"program : program sql_command",
"program : program QUIT ';'",
"sql_command : INSERT INTO tablename VALUES '(' data_list ')' ';'",
"sql_command : INSERT INTO tablename select_expr ';'",
"sql_command : select_expr ';'",
"sql_command : UPDATE tablename SET colname '=' expr WHERE expr ';'",
"sql_command : DELETE FROM tablename WHERE expr ';'",
"sql_command : CREATE TABLE tablename '(' column_decls ')' ';'",
"sql_command : DESCRIBE tablename ';'",
"sql_command : SHOW TABLES ';'",
"sql_command : DROP TABLE tablename ';'",
"sql_command : error ';'",
"tablename : IDENT",
"colname : IDENT",
"expr : value",
"expr : expr bin_op value",
"expr : expr bin_op '(' expr ')'",
"expr : expr bin_op '(' select_expr ')'",
"expr : expr IN '(' select_expr ')'",
"expr : '(' select_expr ')'",
"expr : '(' expr ')'",
"expr : fcall",
"fcall : IDENT '(' fncargs ')'",
"fcall : IDENT '(' ')'",
"fncargs : expr",
"fncargs : fncargs ',' expr",
"value : IDENT",
"value : NUMBER",
"value : STRING",
"select_expr : SELECT projection FROM join whereclause groupclause havingclause orderclause",
"whereclause :",
"whereclause : WHERE expr",
"havingclause :",
"havingclause : HAVING expr",
"groupclause :",
"groupclause : GROUP BY grouplist",
"grouplist : groupspec",
"grouplist : grouplist ',' groupspec",
"groupspec : colname",
"orderclause :",
"orderclause : ORDER BY orderlist",
"orderlist : orderspec",
"orderlist : orderlist ',' orderspec",
"orderspec : NUMBER",
"orderspec : NUMBER ASC",
"orderspec : NUMBER DESC",
"orderspec : colname",
"orderspec : colname ASC",
"orderspec : colname DESC",
"projection : outcol",
"projection : projection ',' outcol",
"outcol : expr AS colname",
"outcol : colname",
"join : tablename",
"join : join ',' tablename",
"data_list : NUMBER",
"data_list : STRING",
"data_list : NUL",
"data_list : data_list ',' NUMBER",
"data_list : data_list ',' STRING",
"data_list : data_list ',' NUL",
"column_decls : column_decl",
"column_decls : column_decls ',' column_decl",
"column_decl : colname",
"column_decl : colname KEY",
"column_decl : colname PRIMARY KEY",
"bin_op : '='",
"bin_op : NOTEQ",
"bin_op : '>'",
"bin_op : '<'",
"bin_op : GEQ",
"bin_op : LEQ",
"bin_op : '+'",
"bin_op : '-'",
"bin_op : '*'",
"bin_op : '/'",
"bin_op : AND",
"bin_op : OR",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 254 "HW6-sql.y"
yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}

#line 395 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 45 "HW6-sql.y"
	{ freen = initfreen; /* Recover unused nodes */ }
break;
case 3:
#line 46 "HW6-sql.y"
	{ return 0; }
break;
case 4:
#line 50 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, yystack.l_mark[-5], yystack.l_mark[-2]))),0)); yyval=0; }
break;
case 5:
#line 53 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERT, 2, yystack.l_mark[-2], yystack.l_mark[-1]))),0)); yyval=0; }
break;
case 6:
#line 56 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(yystack.l_mark[-1])),0)); }
break;
case 7:
#line 59 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(
			makeexpr(OP_UPDATE, 2, yystack.l_mark[-7], makeexpr(OP_PROJECTION,2,makeexpr(OP_SELECTION, 2, yystack.l_mark[-7], yystack.l_mark[-1]), 
									    makeexpr(OP_RLIST,2,makeexpr(OP_AS,2,yystack.l_mark[-5],yystack.l_mark[-3]),0)))
			)),0)); yyval=0; }
break;
case 8:
#line 65 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DELETE, 2, yystack.l_mark[-3], yystack.l_mark[-1]))),0)); yyval=0; }
break;
case 9:
#line 68 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, yystack.l_mark[-4], yystack.l_mark[-2]))),0)); yyval=0; }
break;
case 10:
#line 71 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DESCRIBE, 1, yystack.l_mark[-1], 0))),0)); yyval=0; }
break;
case 11:
#line 75 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_SHOWTABLES, 0, 0, 0))),0)); yyval=0; }
break;
case 12:
#line 79 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DROPTABLE, 2, yystack.l_mark[-1], 0))),0)); yyval=0; }
break;
case 14:
#line 86 "HW6-sql.y"
	{
		  yyval = makeexpr(OP_TABLENAME, 1, yystack.l_mark[0], 0);
		}
break;
case 15:
#line 92 "HW6-sql.y"
	{
		  yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0);
		}
break;
case 17:
#line 99 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-1], 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 18:
#line 101 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 19:
#line 103 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 20:
#line 105 "HW6-sql.y"
	{ yyval = makeexpr(OP_IN, 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 21:
#line 107 "HW6-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 22:
#line 109 "HW6-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 23:
#line 111 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 24:
#line 115 "HW6-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-3], 0), yystack.l_mark[-1]); }
break;
case 25:
#line 117 "HW6-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-2], 0), 0); }
break;
case 26:
#line 121 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 27:
#line 123 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 28:
#line 128 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0); }
break;
case 29:
#line 130 "HW6-sql.y"
	{ yyval = makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0); }
break;
case 30:
#line 132 "HW6-sql.y"
	{ yyval = makeexpr(OP_STRING, 1, yystack.l_mark[0], 0); }
break;
case 31:
#line 136 "HW6-sql.y"
	{ yyval = yystack.l_mark[-4];
		  if(yystack.l_mark[-3]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-3]);
		  if(yystack.l_mark[-2]) yyval = makeexpr(OP_GROUP, 2, yyval, yystack.l_mark[-2]);
		  yyval = makeexpr(OP_PROJECTION, 2, yyval, yystack.l_mark[-6]);
		  if(yystack.l_mark[-1]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-1]);
		  if(yystack.l_mark[0]) yyval = makeexpr(OP_SORT, 2, yyval, yystack.l_mark[0]);
		}
break;
case 32:
#line 145 "HW6-sql.y"
	{ yyval = 0; }
break;
case 33:
#line 146 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 34:
#line 149 "HW6-sql.y"
	{ yyval = 0; }
break;
case 35:
#line 150 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 36:
#line 153 "HW6-sql.y"
	{ yyval = 0; }
break;
case 37:
#line 155 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 38:
#line 159 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 39:
#line 161 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 41:
#line 167 "HW6-sql.y"
	{ yyval = 0; }
break;
case 42:
#line 169 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 43:
#line 173 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 44:
#line 175 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 45:
#line 179 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 46:
#line 181 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), 0); }
break;
case 47:
#line 183 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 48:
#line 185 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[0], 0); }
break;
case 49:
#line 187 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[-1], 0); }
break;
case 50:
#line 189 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[-1], makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 51:
#line 193 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 52:
#line 195 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 53:
#line 199 "HW6-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 54:
#line 201 "HW6-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[0], yystack.l_mark[0]); }
break;
case 55:
#line 205 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 56:
#line 207 "HW6-sql.y"
	{ yyval = makeexpr(OP_PRODUCT, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 57:
#line 211 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 58:
#line 213 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), 0); }
break;
case 59:
#line 215 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
break;
case 60:
#line 217 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 61:
#line 219 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 62:
#line 221 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), yystack.l_mark[-2]); }
break;
case 63:
#line 226 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 64:
#line 228 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 65:
#line 232 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[0], 0); }
break;
case 66:
#line 234 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-1], makeexpr(OP_STRING, 1, (int)"KEY", 0)); }
break;
case 67:
#line 236 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-2], makeexpr(OP_STRING, 1, (int)"PRIMARY", 0)); }
break;
case 68:
#line 239 "HW6-sql.y"
	{ yyval = OP_EQUAL; }
break;
case 69:
#line 240 "HW6-sql.y"
	{ yyval = OP_NOTEQ; }
break;
case 70:
#line 241 "HW6-sql.y"
	{ yyval = OP_GT; }
break;
case 71:
#line 242 "HW6-sql.y"
	{ yyval = OP_LT; }
break;
case 72:
#line 243 "HW6-sql.y"
	{ yyval = OP_GEQ; }
break;
case 73:
#line 244 "HW6-sql.y"
	{ yyval = OP_LEQ; }
break;
case 74:
#line 245 "HW6-sql.y"
	{ yyval = OP_PLUS; }
break;
case 75:
#line 246 "HW6-sql.y"
	{ yyval = OP_BMINUS; }
break;
case 76:
#line 247 "HW6-sql.y"
	{ yyval = OP_TIMES; }
break;
case 77:
#line 248 "HW6-sql.y"
	{ yyval = OP_DIVIDE; }
break;
case 78:
#line 249 "HW6-sql.y"
	{ yyval = OP_AND; }
break;
case 79:
#line 250 "HW6-sql.y"
	{ yyval = OP_OR; }
break;
#line 914 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
