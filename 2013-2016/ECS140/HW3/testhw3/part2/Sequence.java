// Sequence should be implemented as a linked list 
// Thus I need to create a node class

//Class Sequence
class Sequence extends Element
{
    public Node begin;
    public Node last;
    public int size;
    
    //constructor
    public Sequence()
    {
        Type = "Sequence";
        begin = null;
        last = null;
        size = 0;
    }
    
    //Print
    public void Print()
    {
        System.out.print("[ ");
        Node ptr = begin;       // iteration purpose
        
        while(ptr.next != null)
        {
            ptr.data.Print();
            System.out.print(" ");
            ptr = ptr.next;
        }
        ptr.data.Print();       //print last
        System.out.print(" ]");
        
    }
    
    // method first
    public Element first()
    {
        if(begin == null){System.out.println("No Element in the Sequence");} // if empty sequence
        return begin.data; //return first Node's data 
    }
    
    // method rest
    public Sequence rest()
    {
        Sequence newseq = new Sequence();        //create new Sequence
        newseq.size = newseq.length();
        newseq.begin=begin.next;   //set newseq's first Node as second node in current Sequence
        newseq.last = last;
        return newseq;
    }
    
    // method length also update the size
    public int length()
    {
        if(begin==null){size = 0; return size;}
        
        int i =1;
        Node nodeptr = begin;
        while(nodeptr.next!=null)
        {
            nodeptr=nodeptr.next;
            i++;
        }
        size = i;                          
        return size;
    }
    
    // method add
    public void add(Element element,int pos)
    {
        Node nodeptr = new Node(element,null);
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
                Node ptr = begin;               // for iteration purpose
                for(int i =1; i<size ; i++)
                {
                   if(i==pos)
                   {
                       Node tmp = ptr.next;     // store next node
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
    
    // method delete
    public void delete(int pos)
    {
        if(pos==0)                              // delete begin
        {
            begin = begin.next;
        }
        else if (pos == size)                   // delete last 
        {
            Node nodeptr = NodeIndex(size-1);   // find node before last
            last = nodeptr;
        }
        else if(pos>size)
        {
            System.err.println("Position: "+ pos +"Out of Bound, size is: "+size);
            System.exit(1);
        }
        else                                    // delete middle
        {
            Node nodeptr = NodeIndex(pos-1);    // find node before delete one 
            nodeptr.SetNext(nodeptr.next.next); // link that node to next next
        }
        size--;
    }
    
    // method node index
    public Node NodeIndex(int pos)
    {
        Node nodeptr = begin;
        for(int i=0;i<=size;i++)
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
    public Element index(int pos)
    {
        Node nodeptr = NodeIndex(pos);
        return nodeptr.data;
    }
    
    // method flatten
    public Sequence flatten()
    {
        Sequence newseq = shallowcopy();                                           //  copy original Sequence
        for(int i=0; i<newseq.size;i++)
        {
            if(newseq.index(i).Type.equals("Sequence"))                            // the node contain Sequence
            {   
                Sequence tmp = ((Sequence)newseq.index(i)).flatten();           // make a reference of old Sequence and make recursion call
                newseq.delete(i);                                                  // delete node contain Sequence

                for (int j=0;j<tmp.size;j++)                                // add element in sub-sequence to super-sequence
                {
                    newseq.add(tmp.index(j),j+i);                           // insert element to correct pos j+i (subpos+superpos)
                }
            }
        }
        return newseq;
    }
    
    // method deep copy     
    // the idea of deep copy is to create new Node with new Element object
    // Thus, change object value will not reflect on each other
    public Sequence copy()
    {
        Sequence newseq = new Sequence();
        newseq.size = size;
        Node nodeptr = new Node(CreateNew(begin.data),null);             //copy begin
        newseq.begin = nodeptr;
        
        for(int i =1;i<size;i++)
        {
            Node newnode = new Node(CreateNew(NodeIndex(i).data),null); // link new Sequence with new node
            nodeptr.SetNext(newnode);
            nodeptr = nodeptr.next;
        }
        
        return newseq;
    }
    
    // method shallowcopy   change in original can reflect on new one
    public Sequence shallowcopy()
    {
        Sequence newseq = new Sequence();
        newseq.size = size;
        Node nodeptr = new Node(begin.data,null);             //copy begin
        newseq.begin = nodeptr;
        
        for(int i =1;i<size;i++)
        {
            Node newnode = new Node(NodeIndex(i).data,null); // link new Sequence with new node
            nodeptr.SetNext(newnode);
            nodeptr = nodeptr.next;
        }
        
        return newseq;
    }
    
    // method create new char or integer  (for deep copy)
    public Element CreateNew(Element element)
    {
        if(element.Type.equals("Integer"))
        {
            Integer val = ((MyInteger)element).Get();
            MyInteger newelement = new MyInteger();
            newelement.Set(val);
            return newelement;                                          // create new MyInteger object
        }
        else if(element.Type.equals("Char"))
        {
            char val  = ((MyChar)element).Get();
            MyChar newelement = new MyChar();
            newelement.Set(val);
            return newelement;                                          // create new MyChar object
        }
        else if(element.Type.equals("Sequence"))
        {
            return ((Sequence)element).copy();                          // create new Sequence object
        }
        else
        {
            System.err.println("unrecognized Element type: "+element.Type);
            System.exit(1);
            MyInteger newelement = new MyInteger();
            return newelement;
        }
    }
}


// Class Node
class Node
{
    public Element data;
    public Node next;
    
    //constructor 1
    public Node()
    {
        next = null;
        data = null;
    }
    
    //constructor 2
    public Node(Element element,Node n)
    {
        data = element;
        next = n;
    }
    
    //set data method 
    public void SetData(Element element)
    {
        data = element;
    }
    
    //set next method 
    public void SetNext(Node n)
    {
        next = n;
    }
}
 /*           if(ptr.data.Type.equals("Char"))
            {
                ptr.data.Print();
                ptr = ptr.next;
            }// element is Char
            else if (ptr.data.Type.equals("Integer"))
            {
                ptr.data.Print();
                ptr = ptr.next;
            }// element is Integer
            else if(ptr.data.Type.equals("Sequence"))
            {
                ptr.data.Print();
                ptr = ptr.next;
            }// element is Sequence
            else
            {
                System.err.println("unrecognized Element type");
            }*/
