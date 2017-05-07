top:		HW6

HW2:		basic_parser.c
		cc -o HW2 basic_parser.c

HW3:		HW3-datastore.c HW3-parser.c
		cc -o HW3 HW3-datastore.c HW3-parser.c

HW4parser:	HW4-expr.h HW4-sql.y HW4-sql.x HW4-testparser.c
		yacc -t HW4-sql.y
		flex HW4-sql.x
		cc -o HW4parser HW4-testparser.c
		rm lex.yy.c y.tab.c

HW4:		HW4-expr.h HW4-sql.y HW4-sql.x HW4-parser.c HW4-datastore.c HW4-expression.c HW4-rewriter.c
		yacc -t HW4-sql.y
		flex HW4-sql.x
		cc -o HW4 HW4-parser.c HW4-datastore.c HW4-expression.c HW4-rewriter.c
		rm lex.yy.c y.tab.c

HW5:		HW5-expr.h HW5-sql.y HW5-sql.x HW5-parser.c HW5-datastore.c HW5-expression.c
		yacc -t HW5-sql.y
		flex HW5-sql.x
		cc -o HW5 HW5-parser.c HW5-datastore.c HW5-expression.c
		rm lex.yy.c y.tab.c

HW6:		HW6-buf.h HW6-expr.h HW6-expression.h HW6-sql.y HW6-sql.x HW6-parser.c HW6-datastore.c HW6-expression.c HW6-rewriter.c HW6-btree.c HW6-block.c HW6-optimizer.c
		yacc -t HW6-sql.y
		flex HW6-sql.x
		cc -g -o  HW6 HW6-parser.c HW6-datastore.c HW6-expression.c HW6-rewriter.c HW6-btree.c HW6-block.c HW6-optimizer.c


HW6-btreedump:	HW6-buf.h HW6-btreedump.c

HW6-parser:	HW6-expr.h HW6-sql.y HW6-sql.x HW6-testparser.c
		yacc -t HW6-sql.y
		flex HW6-sql.x
		cc -o HW6-parser HW6-testparser.c
		rm lex.yy.c y.tab.c

PRJ:		PRJ-expr.h PRJ-sql.y PRJ-sql.x PRJ-parser.c PRJ-datastore.c PRJ-expression.c
		yacc -t PRJ-sql.y
		flex PRJ-sql.x
		cc -o PRJ -g PRJ-parser.c PRJ-datastore.c PRJ-expression.c
		rm lex.yy.c y.tab.c
