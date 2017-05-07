// class matrix
public class Matrix extends Sequence
{
    Sequence matrix;
    int matrowsize;
    int matcolsize;
    
    // constructor
    public Matrix(int rowsize,int colsize)
    {
        matrix = new Sequence();
        matrowsize = rowsize;
        matcolsize = colsize;
        for(int row = 0; row < rowsize; row++)
        {
            Sequence column = new Sequence();                       // create sequence for each column
            matrix.add(column,row);
            
            for(int col = 0; col < colsize; col++)
            {
                MyInteger value = new MyInteger(); 
                ((Sequence)matrix.index(row)).add(((Element)value),col);
            }
        }
        //Print();
    }
    
    // method set
    public void Set(int row, int col, int value)
    {
        Element element = ((Sequence)matrix.index(row)).index(col);
        ((MyInteger)element).Set(value);
    }
    
    // method get 
    public int Get(int row, int col)
    {
        Element element = ((Sequence)matrix.index(row)).index(col);
        return ((MyInteger)element).Get();
    }
    
    // method matrix sum 
    public Matrix Sum(Matrix mat)
    {
        if (matrowsize!=mat.matrowsize || matcolsize!=mat.matcolsize)
        {
            System.out.println("Incompatible Matrix Size");
            System.exit(1);
        }
        for(int row = 0; row < matrowsize; row++)
        {
            for(int col = 0; col < matcolsize; col++)
            {
                int val1 = Get(row,col);
                int val2 = mat.Get(row,col);
                Set(row,col,val1+val2);
            }
        }
        return this;
    }
    
    // method matrix product
    public Matrix Product(Matrix mat)
    {
        if(matcolsize!=mat.matrowsize)                                // matrix multiplication rule
        {
            System.out.println("Matrix dimensions incompatible for Product");
            System.exit(1);
        }
        
        Matrix product = new Matrix(matrowsize,mat.matcolsize);       // matrix multiplication rule 
        
        for(int i =0; i< matrowsize;i++)
        {
            for(int j = 0; j< mat.matcolsize;j++)
            {
                int sum = 0;
                
                for(int k = 0;k<matcolsize;k++)
                {
                    sum += Get(i,k)*mat.Get(k,j);
                }
                product.Set(i,j,sum);
            }
        }
        
        return product;
    }
    
    // method print 
    public void Print()
    {
        for(int i = 0;i<matrowsize;i++)
        {
            matrix.index(i).Print();
            System.out.println();
        }
    }
}











