/* *** Part3 semantic check ---- SymbolTable *** 
   *** This class are consist of five major  *** 
   *** Add new variable list   pop finished variable list  Add var to list ***   
   ***check for declaration     check for use  *** */
   
//in order to use listarray
import java.util.*;

public class SymbolTable
{
    // stack to store variable
    public ArrayList< ArrayList<Token> > table;
    
    // constructor 
    SymbolTable()
    {
        table = new ArrayList< ArrayList<Token> >();
    }
    
    // 1: Add new table list
    public void add_symbol_list()
    {
        table.add(new ArrayList<Token>());
    }
    
    // 2: pop finished table list
    public void remove_symbol_list()
    {
        table.remove(table.size()-1);
    }
    
    // 3: Add variable to table list
    public void insert_var(Token token)
    {
        if(is_in_list(token))
        {
            System.err.println("redeclaration of variable "+token.string);
        }// if ID in current list, this will be re-declaration
        else
        {
            table.get(table.size()-1).add(token);
        }// if ID not in current list, append it to list
    }
    
    // 4: Check for re-declaration or undeclared use
    public void check_variable(Token token, int level)
    {
        //System.err.println( "in check variable" + level+"token:"+token.string);
        if(level == -1)
        {
            if(!is_in_table(token))
            {
                System.err.println(token.string+" is an undeclared variable on line "+ token.lineNumber);
                System.exit(1);
            }// undeclared usage
        }// -1: non-referenced var   need to search in whole table
        
        else if (level == -2)
        {
            if(!is_in_table(token,(table.size()-1)))
            {
                System.err.println("no such variable ~"+token.string+" on line "+ token.lineNumber);                
                System.exit(1);
            }// undeclared usage
        }// -2: implicit reference number  means global scope
        
        else if (level <= (table.size()-1))
        {
            if(!is_in_table(token,level))
            {
                System.err.println("no such variable ~"+level+token.string+" on line "+ token.lineNumber);
                System.exit(1);
            }// undeclared usage
            
        }// search with correct ref number
        
        else
        {
             System.err.println("no such variable ~"+level+token.string+" on line "+ token.lineNumber);
             System.exit(1);
        }//access level that does not exist
    }
    
    // 5: helper function I  return if variable is in whole table 
    public boolean is_in_table(Token token)
    {
        for(ArrayList<Token> list : table)
        {
            for(Token tmp : list)
            {
                if(tmp.string.equals(token.string))
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    // 6: helper function II(overload)  return if referenced_variable is in whole table
    public boolean is_in_table(Token token,int level)
    {
       // System.err.println("in table search level: "+level);
        for (Token tmp : table.get(table.size()-1-level))
        {
            if(tmp.string.equals(token.string))
            {
                return true;
            }
        }
        return false;
    }
    // 7: helper function III  return if variable is in current list 
    public boolean is_in_list(Token token)
    {
        for (Token tmp : table.get(table.size()-1))
        {
            if(tmp.string.equals(token.string))
            {
                return true;
            }
        }
        return false;
    }
    public int current_level()
    {
        return table.size()-1;
    }
    public int searchnearest(Token token)
    {
        int level= 0;
        int nearest=0;
        for(ArrayList<Token> list : table)
        {
            for(Token tmp : list)
            {
                if(tmp.string.equals(token.string))
                {
                    nearest=level; 
                }
            }
            level++;
        }
        return nearest;
    }
}