// Class Element
public abstract class Element
{
    String Type;
    abstract void Print();
    public Element()
    {
        Type = "NULL";
    }
}

// Derived Class of Element
class MyChar extends Element
{
    char data;
    
    //constructor
    public MyChar()
    {
        Type = "Char";
        data = '0';
    }
    
    //Get Char value
    public char Get()
    {
        return data;
    }
    
    //Set Char value
    public void Set(char val)
    {
        data = val;
    }
    
    //Print
    public void Print()
    {
        System.out.print("'"+data+"'");   
    }
}

class MyInteger extends Element
{
    Integer data;
    
    //constructor
    public MyInteger()
    {
        Type = "Integer";
        data = 0;
    }
    
    //Get int value
    public Integer Get()
    {
        return data;
    }
    
    //Set int value
    public void Set(Integer val)
    {
        data = val;
    }
    
    //Print
    public void Print()
    {
        System.out.print(data);
    }
}











