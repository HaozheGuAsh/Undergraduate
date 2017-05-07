//class MapIterator
public class MapIterator
{
    public MapNode current;
    
    // constructor
    public MapIterator()
    {
        current = null;
    }
    
    // method equal 
    public boolean equal (MapIterator other)
    {
        return current==other.current;
    }
    
    // method advance 
    public MapIterator advance()
    {

        if(!check())                                    // check for end of sequence before advance
        { 
            MapNode nullptr=null;
            current = nullptr;
            return this;                                // if is null then just return null node 
        }                                     
        current = current.next;
        return this;
    }
    
    // method get
    public Pair get()
    {
        return current.data;
    }
    
    // method check to give error information
    public boolean check()
    {
        if(current.next == null)
        {
            return false;
        }
        else 
        {
            return true;
        }
    }
    
}
