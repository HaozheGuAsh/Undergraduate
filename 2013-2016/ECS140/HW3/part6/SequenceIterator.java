// class SequenceIterator

public class SequenceIterator
{
    public Node current;
    
    // constructor
    public SequenceIterator()
    {
        current = null;
    }
    
    // method equal 
    public boolean equal (SequenceIterator other)
    {
        return current==other.current;
    }
    
    // method advance 
    public SequenceIterator advance()
    {

        if(!check())                                    // check for end of sequence before advance
        { 
            Node nullptr=null;
            current = nullptr;
            return this;                                // if is null then just return null node 
        }                                     
        current = current.next;
        return this;
    }
    
    // method get
    public Element get()
    {
        return current.data;
    }
    
    // method check to give error information
    public boolean check()
    {
        if(current.next == null)
        {
 //           System.err.println("Cannot advance, reach the last node.");
 //           System.exit(1);
            return false;
        }
        else 
        {
            return true;
        }
    }
    
}
