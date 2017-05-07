//class Map
public class Map
{
    public MapNode begin;
    public MapNode last;
    public int size;
    
    //constructor
    public Map()
    {
        begin = null;
        last = null;
        size = 0;
    }
    
    public MapIterator begin()
    {
        MapIterator it = new MapIterator();
        it.current = begin;
        return it;
    }
    public MapIterator end()
    {
        MapIterator it = new MapIterator();
        it.current = null;
        return it;
    }
    //Print
    public void Print()
    {
        System.out.print("[ ");
        MapNode ptr = begin;       // iteration purpose
        
        while(ptr.next != null)
        {
            ptr.data.Print();
            System.out.print(" ");
            ptr = ptr.next;
        }
        ptr.data.Print();       //print last
        System.out.print(" ]");
        
    }
    
    // method map add intake pair Object
    // if same key exist, insert at back
    public void add(Pair pair)
    {
        int pos = 0;
        for(;pos<=size; pos++)
        {
            if(pos == size)
            {
                addpos(pair,size);// no pair have larger key, add to the end
                break;
            }
            if(pair.key.Get()<index(pos).key.Get())
            {
                addpos(pair,pos);                                       // add pair to correct position
                break;
            }
        }// find the first pair which key is larger than our pair
        
        
    }
    
    // method map find intake Mychar key 
    // if same key exist, return first
    public MapIterator find(MyChar mykey)
    {
        MapIterator nodeitr = begin();
        for(;!nodeitr.equal(end());nodeitr.advance())
        {
            if(nodeitr.current.data.key.Get() == mykey.Get())
            {
                return nodeitr;
            }
        }
        MapIterator nullptr = end();
        return nullptr;
    }
    // method addpos helper function of add(pair)
    public void addpos(Pair pair,int pos)
    {
        MapNode nodeptr = new MapNode(pair,null);
        if(begin==null && pos == 0)        //nothting in the Sequence
        {
            begin = nodeptr;                // both begin and last is the first node 
            last = nodeptr;
            size++;
        }
        else if(pos>size || pos<0)          // invalid position
        {
            System.err.println("Invalid Position: "+pos+" while size of Sequence is: "+size);
            System.exit(1);
        }
        else
        {
            
            if(pos==0)                              
            {
                nodeptr.SetNext(begin);           // new begin link to old begin
                begin = nodeptr;                  // declare new begin as begin 
                size++;
            }// if insert at begin 
            
            else if(pos==size)
            {
                last.SetNext(nodeptr);             // old last link to new last 
                last = nodeptr;                    // declare new last as last 
                size++;
            }// if insert at last 
            
            else
            {
                MapNode ptr = begin;               // for iteration purpose
                for(int i =1; i<size ; i++)
                {
                   if(i==pos)
                   {
                       MapNode tmp = ptr.next;     // store next node
                       ptr.SetNext(nodeptr);    // link to new node
                       nodeptr.SetNext(tmp);    // new node link to stored node
                       size++;
                       break;
                   }
                   ptr = ptr.next;              // iteration
                }
            }// if insert at middle 
            
        }
    }
    
    // method node index
    public MapNode NodeIndex(int pos)
    {
        MapNode nodeptr = begin;
        for(int i=0;i<size;i++)
        {
            if(i==pos)
            {
                return nodeptr;
            }
            nodeptr = nodeptr.next;
        }
        System.err.println("Index: "+ pos +" Out of Bound, size is: "+size);
        System.exit(1);
        return nodeptr;
    }
    
    // method Index
    public Pair index(int pos)
    {
        MapNode nodeptr = NodeIndex(pos);
        return nodeptr.data;
    }
}


// Class Node
class MapNode
{
    public Pair data;
    public MapNode next;
    
    //constructor 1
    public MapNode()
    {
        next = null;
        data = null;
    }
    
    //constructor 2
    public MapNode(Pair pair,MapNode n)
    {
        data = pair;
        next = n;
    }
    
    //set data method 
    public void SetData(Pair pair)
    {
        data = pair;
    }
    
    //set next method 
    public void SetNext(MapNode n)
    {
        next = n;
    }
}

// class Pair
class Pair 
{
    MyChar key;
    Element value;
    
    //constructor
    public Pair(MyChar Key,Element Value)
    {
        key = Key;
        value = Value;
    }
    
    //Get Key
    public MyChar GetKey()
    {
        return key;
    }
    
    //Get Value
    public Element GetValue()
    {
        return value;
    }
    
    //print
    public void Print()
    {
         System.out.print("(");
         key.Print();
         System.out.print(" ");
         value.Print();
         System.out.print(")");
    }
}