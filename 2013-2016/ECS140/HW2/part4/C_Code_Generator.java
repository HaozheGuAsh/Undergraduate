/* This class will provide C language code generating function for parser*/

public class C_Code_Generator
{
    //Constructor
    C_Code_Generator(){}
    
    public void Code_Start()
    {
        System.out.println("//Code generated from E language\n");
        System.out.println("#include<stdio.h>\n");
        System.out.println("int main()");
    }//print necessary code for prologue
    
    public void Code_Startblock()
    {
        System.out.print("{");
    }//print { for startblock
    
    public void Code_Endblock()
    {
        System.out.print("}\n");
    }//print } for endblock
    
    // @ declaration
    public void Code_Declare()
    {
        System.out.print("int ");
    }
    
    // ! print
    public void Code_Print()
    {
        System.out.print("printf(\"%d\\n\",");
    }
    
    // [ if 
    public void Code_If()
    {
        System.out.print("if ");
    }
    
    // : then
    public void Code_Elseif()
    {
        System.out.print("else if ");
    }
    
    // % else
    public void Code_Else()
    {
        System.out.print("else ");
    }
    
    // ] endelse
    public void Code_Endelse()
    {
        System.out.print("}");
    }
    
    // < do
    public void Code_Do()
    {
        System.out.print("while ");
    }
    
    // > enddo
  //  public void Code_Enddo()
  //  {
  //      System.out.println("");
  //  }
    
    // = assign
    public void Code_Assign()
    {
        System.out.print(" = ");
    }
    
    // , comma
    public void Code_Comma()
    {
        System.out.print(",");
    }
    
    // ( lparen
    public void Code_Lparen()
    {
        System.out.print("( ");
    }
    
    // ) rparen
    public void Code_Rparen()
    {
        System.out.print(" )");
    }
    
    // + plus
    public void Code_Plus()
    {
        System.out.print(" + ");
    }
    
    // - minus
    public void Code_Minus()
    {
        System.out.print(" - ");
    }
    
    // * times
    public void Code_Times()
    {
        System.out.print(" * ");
    }
    
    // / divide
    public void Code_Divide()
    {
        System.out.print(" / ");
    }
    
    // ~ tilde
    
    // id
    public void Code_Id(String var,int level)
    {
        System.out.print("scope_"+level+"Var_"+var);
    }
    
    // Number
    public void Code_Num(String num)
    {
        System.out.print(num);
    }
    
    // {
    public void Code_Lbracket()
    {
        System.out.print("{ ");
    }
    
    // }
    public void Code_Rbracket()
    {
        System.out.print(" }");
    }
    
    // ;
    public void Code_Semicolon()
    {
        System.out.println(";");
    }
}