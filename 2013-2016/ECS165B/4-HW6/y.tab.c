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
#define COUNT 267
#define AVG 268
#define HAVING 269
#define ORDER 270
#define ASC 271
#define DESC 272
#define INSERT 273
#define INTO 274
#define VALUES 275
#define UPDATE 276
#define SET 277
#define DELETE 278
#define CREATE 279
#define TABLE 280
#define DESCRIBE 281
#define SHOW 282
#define TABLES 283
#define DROP 284
#define UNIQUE 285
#define DISTINCT 286
#define PRIMARY 287
#define KEY 288
#define IN 289
#define ON 290
#define JOIN 291
#define NOTEQ 292
#define GEQ 293
#define LEQ 294
#define AND 295
#define OR 296
#define NOT 297
#define QUIT 298
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    5,    6,    6,    6,    6,    6,
    6,    6,    6,   10,   10,   11,   11,    8,    8,    8,
    4,   12,   12,   15,   15,   17,   17,   16,   16,   19,
   19,   20,   18,   18,   21,   21,   22,   22,   22,   22,
   22,   22,   13,   13,   23,   23,   23,   23,   14,   14,
   14,    3,    3,    3,    3,    3,    3,    7,    7,   24,
   24,   24,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,
};
static const short yylen[] = {                            2,
    0,    2,    3,    8,    5,    2,    9,    6,    7,    3,
    3,    4,    2,    1,    1,    1,    3,    5,    5,    5,
    3,    3,    1,    4,    3,    1,    3,    1,    1,    1,
    9,    0,    1,    0,    2,    0,    2,    0,    3,    1,
    3,    1,    0,    3,    1,    3,    1,    2,    2,    1,
    2,    2,    1,    3,    6,    6,    3,    1,    1,    3,
    5,    1,    1,    1,    3,    3,    3,    1,    3,    1,
    2,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,
};
static const short yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    2,    0,   13,   33,    0,    0,   14,    0,    0,
    0,    0,    0,    0,    3,    6,    0,   29,   30,    0,
    0,    0,   58,    0,   16,   23,    0,   53,    0,    0,
    0,    0,   10,   11,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   74,   77,   78,   83,   84,   73,   75,
   76,   79,   80,   81,   82,    0,    0,    0,    0,    0,
   15,    0,    0,    0,   12,   25,    0,    0,    0,    0,
   21,   22,   57,    0,   28,    0,   17,   59,    0,   54,
    0,    5,    0,    0,    0,    0,   68,   24,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   62,   63,
   64,    0,    0,    8,    0,   71,    0,    0,    0,    0,
    0,   20,   19,   18,    0,    0,   60,    0,    0,    0,
    0,    0,   72,    9,   69,   56,   55,    0,    0,    0,
    0,    4,   65,   66,   67,    0,    0,   42,    0,   40,
    0,    0,   31,    7,    0,    0,   41,    0,    0,    0,
   45,   48,   49,   51,   52,    0,   46,
};
static const short yydgoto[] = {                          1,
   12,   19,  112,   13,   33,   34,   96,   35,   66,   36,
   78,   16,   37,   89,  108,  129,  141,  153,  149,  150,
  160,  161,   38,   97,
};
static const short yysindex[] = {                         0,
 -107,  -48, -270, -252, -233, -237, -245, -233, -242, -228,
    8,    0,   37,    0,    0,   59, -233,    0, -221, -233,
 -233,   54,   68, -233,    0,    0,   58,    0,    0,   67,
   96,   94,    0,   48,    0,    0,  -31,    0, -186, -113,
 -118,  108,    0,    0,   98,   13,   66,   66,   58,  122,
  -33, -113,  125,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  119, -233,   59,  128,  111,
    0,  115,   66, -113,    0,    0,  100,    2,  -11,   -3,
    0,    0,    0,  -88,    0,   94,    0,    0,  -27,    0,
  -80,    0,   66,   69, -183,   28,    0,    0,   66,  -73,
  -70,  154,  155,   19,   66, -233, -233,  -67,    0,    0,
    0,   76,   90,    0,  -89,    0,  141, -113,  100, -113,
 -113,    0,    0,    0,  100,  -87,    0,  -65,  -64,  143,
  -76,   66,    0,    0,    0,    0,    0,   66, -113,   66,
  -66,    0,    0,    0,    0,   79,  100,    0,  162,    0,
  100,  -59,    0,    0, -113, -139,    0,  -86,  -84,  164,
    0,    0,    0,    0,    0, -139,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,   63,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   40,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -41,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  112,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -34,    0,
    0,    0,    0,    0,  114,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -36,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  123,    0,
    0,    0,    0,    0,  -26,    0,    0,    0,    6,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   35,    0,    0,    0,    0,    0,    4,    0,   -4,    0,
   27,    0,    0,    0,    0,    0,    0,   29,   33,   56,
    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  173,    0,   39,  307,  356,    0,  144,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   57,
    0,   43,  145,   93,
};
#define YYTABLESIZE 496
static const short yytable[] = {                         28,
   28,   28,   28,   28,   38,   28,   34,   82,   64,   62,
   14,   63,   68,   65,   35,   15,  107,   28,   28,   28,
   28,   17,   38,   18,   34,   20,   61,   59,   60,  100,
   64,   62,   35,   63,   21,   65,   39,  101,   64,   62,
   23,   63,   98,   65,   61,   99,   36,   61,   61,   59,
   60,   24,   32,   76,   39,   40,   61,   59,   60,  124,
   64,   62,   61,   63,   36,   65,   25,   37,  117,   47,
   50,  118,   47,   50,    3,   43,   50,   70,   61,   59,
   60,   28,   28,   15,   28,   37,   28,   47,   69,   64,
   62,   50,   63,   43,   65,   26,   44,   46,   32,   28,
   28,   28,   32,  115,  116,   32,   47,   61,   59,   60,
   64,   62,   43,   63,   44,   65,  130,   71,  158,  131,
   64,   62,  102,   63,  103,   65,   44,  114,   61,   59,
   60,   64,   62,   32,   63,   48,   65,  154,   61,   59,
   60,   64,   62,   71,   63,   73,   65,   74,    2,   61,
   59,   60,   26,    3,   70,   26,   75,   70,   86,   61,
   59,   60,   81,   27,   84,    4,   27,   91,    5,   92,
    6,    7,    3,    8,    9,   93,   10,  109,  110,  111,
   22,  143,  144,  145,  162,  163,  164,  165,  120,   39,
   11,  121,   41,   42,  122,  123,   45,  128,  133,  134,
  139,  142,  138,  152,  140,  155,  156,  166,  167,   87,
  135,  157,   90,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   28,   28,    0,    0,    0,   28,   28,    0,
   34,   67,   38,   38,   34,   34,  105,    0,   35,   88,
    0,    0,   35,   35,    0,    0,    0,   28,    0,   28,
   28,   28,   28,   28,   28,   53,    0,    0,   54,   55,
   56,   57,   58,  106,   39,   39,    0,   61,   61,   49,
   28,   29,   61,   61,    0,   36,    0,   53,  126,  127,
   54,   55,   56,   57,   58,   53,    0,    0,   54,   55,
   56,   57,   58,    0,   61,    0,   37,    0,    0,    0,
    0,   28,   15,    0,    0,    0,    0,   53,    0,   52,
   54,   55,   56,   57,   58,   27,   28,   29,    0,   32,
   32,   32,   49,   28,   29,   30,   31,    0,   28,   32,
   32,   28,   28,   28,   28,   28,   53,    0,    0,   54,
   55,   56,   57,   58,    0,    0,   72,    0,    0,    0,
   49,   28,   29,  132,    3,    0,    0,   53,   83,    0,
   54,   55,   56,   57,   58,    0,    0,   53,    0,    0,
   54,   55,   56,   57,   58,   85,   28,   29,   53,    0,
   95,   54,   55,   56,   57,   58,    0,   51,   53,    0,
    0,   54,   55,   56,   57,   58,    0,    0,    0,    0,
    0,   77,   79,   80,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   95,    0,  136,  137,   94,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  104,    0,    0,    0,  148,    0,    0,  113,    0,
    0,    0,    0,    0,  119,    0,    0,    0,    0,    0,
  125,  148,  159,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  159,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  146,    0,    0,
    0,    0,    0,  147,    0,  151,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,   41,   47,   41,   41,   42,   43,
   59,   45,   44,   47,   41,  286,   44,   59,   60,   61,
   62,  274,   59,  257,   59,  263,   60,   61,   62,   41,
   42,   43,   59,   45,  280,   47,   41,   41,   42,   43,
  283,   45,   41,   47,   41,   44,   41,   44,   60,   61,
   62,  280,   40,   41,   59,  277,   60,   61,   62,   41,
   42,   43,   59,   45,   59,   47,   59,   41,   41,   41,
   32,   44,   44,   41,  261,   41,   44,   39,   60,   61,
   62,   42,   43,   44,   45,   59,   47,   59,  275,   42,
   43,   59,   45,   59,   47,   59,   41,   40,   40,   60,
   61,   62,   40,  287,  288,   40,   40,   60,   61,   62,
   42,   43,   59,   45,   59,   47,   41,  257,  258,   44,
   42,   43,   84,   45,   86,   47,   59,   59,   60,   61,
   62,   42,   43,   40,   45,   40,   47,   59,   60,   61,
   62,   42,   43,  257,   45,  264,   47,   40,  256,   60,
   61,   62,   41,  261,   41,   44,   59,   44,   40,   60,
   61,   62,   41,   41,   40,  273,   44,   40,  276,   59,
  278,  279,  261,  281,  282,   61,  284,  258,  259,  260,
    8,  258,  259,  260,  271,  272,  271,  272,  262,   17,
  298,  262,   20,   21,   41,   41,   24,  265,  288,   59,
  266,   59,  290,  270,  269,   44,  266,   44,  166,   66,
  118,  155,   68,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  264,  265,   -1,   -1,   -1,  269,  270,   -1,
  265,  263,  269,  270,  269,  270,  264,   -1,  265,   67,
   -1,   -1,  269,  270,   -1,   -1,   -1,  289,   -1,  291,
  292,  293,  294,  295,  296,  289,   -1,   -1,  292,  293,
  294,  295,  296,  291,  269,  270,   -1,  264,  265,  257,
  258,  259,  269,  270,   -1,  270,   -1,  289,  106,  107,
  292,  293,  294,  295,  296,  289,   -1,   -1,  292,  293,
  294,  295,  296,   -1,  291,   -1,  270,   -1,   -1,   -1,
   -1,  262,  263,   -1,   -1,   -1,   -1,  289,   -1,  262,
  292,  293,  294,  295,  296,  257,  258,  259,   -1,  257,
  258,  259,  257,  258,  259,  267,  268,   -1,  289,  267,
  268,  292,  293,  294,  295,  296,  289,   -1,   -1,  292,
  293,  294,  295,  296,   -1,   -1,   40,   -1,   -1,   -1,
  257,  258,  259,  264,  261,   -1,   -1,  289,   52,   -1,
  292,  293,  294,  295,  296,   -1,   -1,  289,   -1,   -1,
  292,  293,  294,  295,  296,  257,  258,  259,  289,   -1,
   74,  292,  293,  294,  295,  296,   -1,   32,  289,   -1,
   -1,  292,  293,  294,  295,  296,   -1,   -1,   -1,   -1,
   -1,   46,   47,   48,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  118,   -1,  120,  121,   73,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   86,   -1,   -1,   -1,  139,   -1,   -1,   93,   -1,
   -1,   -1,   -1,   -1,   99,   -1,   -1,   -1,   -1,   -1,
  105,  155,  156,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  166,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  132,   -1,   -1,
   -1,   -1,   -1,  138,   -1,  140,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 298
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
"GROUP","BY","COUNT","AVG","HAVING","ORDER","ASC","DESC","INSERT","INTO",
"VALUES","UPDATE","SET","DELETE","CREATE","TABLE","DESCRIBE","SHOW","TABLES",
"DROP","UNIQUE","DISTINCT","PRIMARY","KEY","IN","ON","JOIN","NOTEQ","GEQ","LEQ",
"AND","OR","NOT","QUIT",
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
"select_expr : SELECT distinct_clause projection FROM join whereclause groupclause havingclause orderclause",
"distinct_clause :",
"distinct_clause : DISTINCT",
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
"outcol : AVG '(' expr ')' AS colname",
"outcol : COUNT '(' expr ')' AS colname",
"outcol : expr AS colname",
"outcol : colname",
"join : tablename",
"join : join ',' tablename",
"join : join JOIN tablename ON expr",
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
#line 273 "HW6-sql.y"
yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}

#line 443 "y.tab.c"

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
#line 49 "HW6-sql.y"
	{ freen = initfreen; /* Recover unused nodes */ }
break;
case 3:
#line 50 "HW6-sql.y"
	{ return 0; }
break;
case 4:
#line 54 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, yystack.l_mark[-5], yystack.l_mark[-2]))),0)); yyval=0; }
break;
case 5:
#line 57 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERT, 2, yystack.l_mark[-2], yystack.l_mark[-1]))),0)); yyval=0; }
break;
case 6:
#line 60 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(yystack.l_mark[-1])),0)); }
break;
case 7:
#line 63 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(
			makeexpr(OP_UPDATE, 2, yystack.l_mark[-7], makeexpr(OP_PROJECTION,2,makeexpr(OP_SELECTION, 2, yystack.l_mark[-7], yystack.l_mark[-1]), 
									    makeexpr(OP_RLIST,2,makeexpr(OP_AS,2,yystack.l_mark[-5],yystack.l_mark[-3]),0)))
			)),0)); yyval=0; }
break;
case 8:
#line 69 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DELETE, 2, yystack.l_mark[-3], yystack.l_mark[-1]))),0)); yyval=0; }
break;
case 9:
#line 72 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, yystack.l_mark[-4], yystack.l_mark[-2]))),0)); yyval=0; }
break;
case 10:
#line 75 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DESCRIBE, 1, yystack.l_mark[-1], 0))),0)); yyval=0; }
break;
case 11:
#line 79 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_SHOWTABLES, 0, 0, 0))),0)); yyval=0; }
break;
case 12:
#line 83 "HW6-sql.y"
	{ print_relation(evalexpr(optimize(compile(makeexpr(OP_DROPTABLE, 2, yystack.l_mark[-1], 0))),0)); yyval=0; }
break;
case 14:
#line 90 "HW6-sql.y"
	{
		  yyval = makeexpr(OP_TABLENAME, 1, yystack.l_mark[0], 0);
		}
break;
case 15:
#line 96 "HW6-sql.y"
	{
		  yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0);
		}
break;
case 17:
#line 103 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-1], 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 18:
#line 105 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 19:
#line 107 "HW6-sql.y"
	{ yyval = makeexpr(yystack.l_mark[-3], 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 20:
#line 109 "HW6-sql.y"
	{ yyval = makeexpr(OP_IN, 2, yystack.l_mark[-4], yystack.l_mark[-1]); }
break;
case 21:
#line 111 "HW6-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 22:
#line 113 "HW6-sql.y"
	{ yyval = yystack.l_mark[-1]; }
break;
case 23:
#line 115 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 24:
#line 119 "HW6-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-3], 0), yystack.l_mark[-1]); }
break;
case 25:
#line 121 "HW6-sql.y"
	{ yyval = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, yystack.l_mark[-2], 0), 0); }
break;
case 26:
#line 125 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 27:
#line 127 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 28:
#line 132 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLNAME, 1, yystack.l_mark[0], 0); }
break;
case 29:
#line 134 "HW6-sql.y"
	{ yyval = makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0); }
break;
case 30:
#line 136 "HW6-sql.y"
	{ yyval = makeexpr(OP_STRING, 1, yystack.l_mark[0], 0); }
break;
case 31:
#line 141 "HW6-sql.y"
	{ yyval = yystack.l_mark[-4];
			if (yystack.l_mark[-3]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-3]);
			if (yystack.l_mark[-2]) yyval = makeexpr(OP_GROUP, 2, yyval, yystack.l_mark[-2]);
			yyval = makeexpr(OP_PROJECTION, 2, yyval, yystack.l_mark[-6]);
			if (yystack.l_mark[-1]) yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[-1]);
			if (yystack.l_mark[0]) yyval = makeexpr(OP_SORT, 2, yyval, yystack.l_mark[0]);
			if (yystack.l_mark[-7]) { yyval = makeexpr(OP_DISTINCT, 1, yyval, 0); }
		}
break;
case 32:
#line 151 "HW6-sql.y"
	{yyval=0;}
break;
case 33:
#line 152 "HW6-sql.y"
	{yyval=1;}
break;
case 34:
#line 155 "HW6-sql.y"
	{ yyval = 0; }
break;
case 35:
#line 156 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 36:
#line 159 "HW6-sql.y"
	{ yyval = 0; }
break;
case 37:
#line 160 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 38:
#line 163 "HW6-sql.y"
	{ yyval = 0; }
break;
case 39:
#line 165 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 40:
#line 169 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 41:
#line 171 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 43:
#line 177 "HW6-sql.y"
	{ yyval = 0; }
break;
case 44:
#line 179 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 45:
#line 183 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 46:
#line 185 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 47:
#line 189 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 48:
#line 191 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), 0); }
break;
case 49:
#line 193 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[-1], 0), makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 50:
#line 195 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[0], 0); }
break;
case 51:
#line 197 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[-1], 0); }
break;
case 52:
#line 199 "HW6-sql.y"
	{ yyval = makeexpr(OP_SORTSPEC, 2, yystack.l_mark[-1], makeexpr(OP_NULL, 0, 0, 0)); }
break;
case 53:
#line 203 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 54:
#line 205 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 55:
#line 209 "HW6-sql.y"
	{yyval = makeexpr(OP_AVG,2 , yystack.l_mark[-3],yystack.l_mark[0]);}
break;
case 56:
#line 211 "HW6-sql.y"
	{yyval = makeexpr(OP_COUNT,2 , yystack.l_mark[-3],yystack.l_mark[0]);}
break;
case 57:
#line 214 "HW6-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 58:
#line 216 "HW6-sql.y"
	{ yyval = makeexpr(OP_OUTCOLNAME, 2, yystack.l_mark[0], yystack.l_mark[0]); }
break;
case 59:
#line 221 "HW6-sql.y"
	{ yyval = yystack.l_mark[0]; }
break;
case 60:
#line 222 "HW6-sql.y"
	{ yyval = makeexpr(OP_PRODUCT, 2, yystack.l_mark[-2], yystack.l_mark[0]); }
break;
case 61:
#line 224 "HW6-sql.y"
	{   yyval = makeexpr(OP_PRODUCT, 2, yystack.l_mark[-4], yystack.l_mark[-2]);
            yyval = makeexpr(OP_SELECTION, 2, yyval, yystack.l_mark[0]);
        }
break;
case 62:
#line 230 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), 0); }
break;
case 63:
#line 232 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), 0); }
break;
case 64:
#line 234 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
break;
case 65:
#line 236 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 66:
#line 238 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, yystack.l_mark[0], 0), yystack.l_mark[-2]); }
break;
case 67:
#line 240 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), yystack.l_mark[-2]); }
break;
case 68:
#line 245 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], 0); }
break;
case 69:
#line 247 "HW6-sql.y"
	{ yyval = makeexpr(OP_RLIST, 2, yystack.l_mark[0], yystack.l_mark[-2]); }
break;
case 70:
#line 251 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[0], 0); }
break;
case 71:
#line 253 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-1], makeexpr(OP_STRING, 1, (int)"KEY", 0)); }
break;
case 72:
#line 255 "HW6-sql.y"
	{ yyval = makeexpr(OP_COLUMNDEF, 2, yystack.l_mark[-2], makeexpr(OP_STRING, 1, (int)"PRIMARY", 0)); }
break;
case 73:
#line 258 "HW6-sql.y"
	{ yyval = OP_EQUAL; }
break;
case 74:
#line 259 "HW6-sql.y"
	{ yyval = OP_NOTEQ; }
break;
case 75:
#line 260 "HW6-sql.y"
	{ yyval = OP_GT; }
break;
case 76:
#line 261 "HW6-sql.y"
	{ yyval = OP_LT; }
break;
case 77:
#line 262 "HW6-sql.y"
	{ yyval = OP_GEQ; }
break;
case 78:
#line 263 "HW6-sql.y"
	{ yyval = OP_LEQ; }
break;
case 79:
#line 264 "HW6-sql.y"
	{ yyval = OP_PLUS; }
break;
case 80:
#line 265 "HW6-sql.y"
	{ yyval = OP_BMINUS; }
break;
case 81:
#line 266 "HW6-sql.y"
	{ yyval = OP_TIMES; }
break;
case 82:
#line 267 "HW6-sql.y"
	{ yyval = OP_DIVIDE; }
break;
case 83:
#line 268 "HW6-sql.y"
	{ yyval = OP_AND; }
break;
case 84:
#line 269 "HW6-sql.y"
	{ yyval = OP_OR; }
break;
#line 985 "y.tab.c"
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
