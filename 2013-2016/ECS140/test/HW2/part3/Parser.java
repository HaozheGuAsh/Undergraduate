/* *** This file is given as part of the programming assignment. *** */

public class Parser {


    // tok is global to all these parsing methods;
    // scan just calls the scanner's scan method and saves the result in tok.
    private Token tok; // the current token
    private SymbolTable table; // SymbolTable
    private void scan() {
	tok = scanner.scan();
    }

    private Scan scanner;
    Parser(Scan scanner) 
    {
        this.table = new SymbolTable();
    	this.scanner = scanner;
    	scan();
    	program();
    	if( tok.kind != TK.EOF )
    	    parse_error("junk after logical end of program");
    }

    private void program() 
    {
        //print c language prologue
    	block();
    }

    private void block()
    {
        table.add_symbol_list();
    	declaration_list();
    	statement_list();
    	table.remove_symbol_list();
    	
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
        
    	mustbe(TK.DECLARE);
    	table.insert_var(tok);
    	mustbe(TK.ID);
    	
    	while( is(TK.COMMA) ) 
    	{
    	    scan();
    	    table.insert_var(tok);
    	    mustbe(TK.ID);
	    }
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
        EXPR();
    }
    
    private void ASSIGN()
    //assign function
    {
        REF_ID();//ref id here 
        mustbe(TK.ASSIGN);
        EXPR();
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
                mustbe(TK.ID);
            }
            else if(is(TK.ID))// ~  ID
            {
                table.check_variable(tok, -2);//check global
                mustbe(TK.ID);
            }
            
        }
        else if(is(TK.ID))// no ~
        {
            table.check_variable(tok, -1);//check all scopes
            mustbe(TK.ID);
        }
        
    }
    
    private void DO_stmt()
    //do function
    {
        mustbe(TK.DO);
        GUARDED_COMMAND();
        mustbe(TK.ENDDO);
    }
    
    private void IF_stmt()
    //if function
    {
        mustbe(TK.IF);
        GUARDED_COMMAND();
        while(is(TK.ELSEIF))
        {
            mustbe(TK.ELSEIF);
            GUARDED_COMMAND();
        }
        if(is(TK.ELSE))  //optional else
        {
            mustbe(TK.ELSE);
            block();
        }
        mustbe(TK.ENDIF);
    }
    
    private void GUARDED_COMMAND()
    //GUARDED_COMMAND function
    {
        EXPR();
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
            EXPR();
            mustbe(TK.RPAREN);
        }
        else if (is(TK.NUM))
        {
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
        }
        else if (is(TK.MINUS))
        {
            mustbe(TK.MINUS);
        }
        // maybe need error warning
    }
    
    private void MULTOP()
    //MULTOP function
    {
        if(is(TK.TIMES))
        {
            mustbe(TK.TIMES);
        }
        else if(is(TK.DIVIDE))
        {
            mustbe(TK.DIVIDE);
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
