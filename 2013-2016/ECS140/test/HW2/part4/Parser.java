/* *** This file is given as part of the programming assignment. *** */

public class Parser {


    // tok is global to all these parsing methods;
    // scan just calls the scanner's scan method and saves the result in tok.
    private Token tok; // the current token
    private SymbolTable table; // SymbolTable
    private C_Code_Generator generator;  // C_Code_Generator
    private void scan() {
	tok = scanner.scan();
    }

    private Scan scanner;
    Parser(Scan scanner) 
    {
        this.table = new SymbolTable();
    	this.scanner = scanner;
    	this.generator = new C_Code_Generator();
    	scan();
    	program();
    	if( tok.kind != TK.EOF )
    	    parse_error("junk after logical end of program");
    }

    private void program() 
    {
        generator.Code_Start();
    	block();
    }

    private void block()
    {
        table.add_symbol_list();
        generator.Code_Startblock();
    	declaration_list();
    	statement_list();
    	table.remove_symbol_list();
    	if((tok.kind==TK.EOF)&&(table.current_level()==0))
    	{
    	    System.out.println("return 0;");
    	}
    	generator.Code_Endblock();
    	
    }// add & remove SymbolTable at the beginning or end of blocks

    private void declaration_list() {
	// below checks whether tok is in first set of declaration.
	// here, that's easy since there's only one token kind in the set.
	// in other places, though, there might be more.
	// so, you might want to write a general function to handle that.
    	while( is(TK.DECLARE) ) 
    	{
    	    declaration();
    	}
    }

    private void declaration() 
    {
        boolean deletecomma=false;
    	mustbe(TK.DECLARE);
    	if(!table.is_in_list(tok))
    	{
    	    generator.Code_Declare();
        	table.insert_var(tok);
        	generator.Code_Id(tok.string,table.current_level());
    	}
    	else
    	{
    	    table.insert_var(tok);
    	    deletecomma=true;
    	}
    	mustbe(TK.ID);

    	while( is(TK.COMMA) ) 
    	{
    	    scan();
    	    if(!table.is_in_list(tok))
            {
                if(!deletecomma){generator.Code_Comma();}
                else{generator.Code_Declare();}
                table.insert_var(tok);
    	        generator.Code_Id(tok.string,table.current_level());
    	    }
    	    else
    	    {
    	        table.insert_var(tok);
    	    }
    	    mustbe(TK.ID);
	    }
	    generator.Code_Semicolon();
    }

    private void statement_list() {
    // call general statement function
        while(is(TK.ID) || is(TK.PRINT) || is(TK.DO) || is(TK.IF)||is(TK.TILDE))
        {
            statement();
        } 
    }
    
    private void statement()
    //call four function to statement
    {
        if (is(TK.ID)||is(TK.TILDE))
        {
            ASSIGN();
            
        }
        else if (is(TK.PRINT))
        {
            PRINT();
            
        }
        else if (is(TK.DO))
        {
            DO_stmt();
        }
        else if (is(TK.IF))
        {
            IF_stmt();
        }
    }
    
    private void PRINT()
    //Print function
    {
        mustbe(TK.PRINT);//will scan 
        generator.Code_Print();
        EXPR();
        generator.Code_Rparen();
        generator.Code_Semicolon();
    }
    
    private void ASSIGN()
    //assign function
    {
        REF_ID();//ref id here 
        mustbe(TK.ASSIGN);
        generator.Code_Assign();
        EXPR();
        generator.Code_Semicolon();
    }
    
    private void REF_ID()
    //ref_id function
    {
        if(is(TK.TILDE))    // ~
        {
            mustbe(TK.TILDE);
            if(is(TK.NUM))   // ~ NUM ID
            {
                int num= get_ref_num(tok);
                mustbe(TK.NUM);
                table.check_variable(tok, num); 
                generator.Code_Id(tok.string,table.current_level()-num);
                mustbe(TK.ID);
            }
            else if(is(TK.ID))// ~  ID
            {
                table.check_variable(tok, -2);//check global
                generator.Code_Id(tok.string,0);
                mustbe(TK.ID);
            }
            
        }
        else if(is(TK.ID))// no ~
        {
            table.check_variable(tok, -1);//check all scopes
            int nearestlevel=table.searchnearest(tok);
            generator.Code_Id(tok.string,nearestlevel);
            mustbe(TK.ID);
        }
        
    }
    
    private void DO_stmt()
    //do function
    {
        mustbe(TK.DO);
        generator.Code_Do();
        GUARDED_COMMAND();
        mustbe(TK.ENDDO);
    }
    
    private void IF_stmt()
    //if function
    {
        mustbe(TK.IF);
        generator.Code_If();
        GUARDED_COMMAND();
        while(is(TK.ELSEIF))
        {
            mustbe(TK.ELSEIF);
            generator.Code_Elseif();
            GUARDED_COMMAND();
        }
        if(is(TK.ELSE))  //optional else
        {
            mustbe(TK.ELSE);
            generator.Code_Else();
            block();
        }
        mustbe(TK.ENDIF);
    }
    
    private void GUARDED_COMMAND()
    //GUARDED_COMMAND function
    {
        generator.Code_Lparen();
        System.out.print("(");
        EXPR();
        System.out.print("<=0)");
        generator.Code_Rparen();
        mustbe(TK.THEN);
        block();
    }
    
    private void EXPR()
    //EXPR function
    {
        TERM();
        while(is(TK.PLUS) || is(TK.MINUS))
        {
            ADDOP();
            TERM();
        }
    }
    
    private void TERM()
    //term function
    {
        FACTOR();
        while(is(TK.TIMES) || is(TK.DIVIDE))
        {
            MULTOP();
            FACTOR();
        }
    }
    
    private void FACTOR()
    //factor function
    {
        if(is(TK.LPAREN))
        {
            mustbe(TK.LPAREN);
            generator.Code_Lparen();
            EXPR();
            mustbe(TK.RPAREN);
            generator.Code_Rparen();
        }
        else if (is(TK.NUM))
        {
            generator.Code_Num(tok.string);
            mustbe(TK.NUM);
        }
        else if (is(TK.TILDE)|| is(TK.ID))// means it's ref_id
        {
            REF_ID();
        }
        //maybe need error warning
    }
    
    private void ADDOP()
    //addop function
    {
        if(is(TK.PLUS))
        {
            mustbe(TK.PLUS);
            generator.Code_Plus();
        }
        else if (is(TK.MINUS))
        {
            mustbe(TK.MINUS);
            generator.Code_Minus();
        }
        // maybe need error warning
    }
    
    private void MULTOP()
    //MULTOP function
    {
        if(is(TK.TIMES))
        {
            mustbe(TK.TIMES);
            generator.Code_Times();
        }
        else if(is(TK.DIVIDE))
        {
            mustbe(TK.DIVIDE);
            generator.Code_Divide();
        }
        //maybe need error warning
    }
    // is current token what we want?
    private boolean is(TK tk) {
        return tk == tok.kind;
    }
    //get the number after ~
    private int get_ref_num(Token tmp)
    {
        int level = Integer.parseInt(tmp.string);
       // System.err.println( "level is "+level);
        return level;
    }
    // ensure current token is tk and skip over it.
    private void mustbe(TK tk) {
	if( tok.kind != tk ) {
	    System.err.println( "mustbe: want " + tk + ", got " +
				    tok);
	    parse_error( "missing token (mustbe)" );
	}
	scan();
    }

    private void parse_error(String msg) {
	System.err.println( "can't parse: line "
			    + tok.lineNumber + " " + msg );
	System.exit(1);
    }
}
