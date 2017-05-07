// Filename:rpn.cpp
// Student ID: 999200555
// Name: Haozhe Gu

#include<iostream>
#include<sstream>
#include<string>
#include<stack>
#include<deque>
using namespace std;

int main()
{
    double doub;
    char ch;
    string input,s;
    deque <string> list;
    stack<double> stack1;
//    istringstream is(s);    

    while(cin>>input)
    {
        list.push_back(input);
    }
    
    int size=list.size() ; 
 //   cout<<"ok1"<<endl;
    for( int num=0 ;num < size;num++)
    {
//	istringstream is(s);
        s=list[num];
	istringstream is(s);
    //    cout<<"s is"<<s<<endl;
        if(is>>doub&&is.eof())
        { 
	    stack1.push(doub);
//	    cout<<"number is"<<doub<<endl;
	}
    
        else
        {
	    is.clear();
            is.str(s);
 	    is>>ch;
//	    cout<<"ch is"<<ch<<endl;
//   	    double a=stack1.top()*1.0;
//	    stack1.pop();
//	    double b=stack1.top()*1.0;
//	    stack1.pop();
	    if(stack1.size()<2)
	    {
		cout<<"stack underflow"<<endl;
	        return 0;
	    }
	    if(ch=='*')
   	    { 
		double a=stack1.top()*1.0;
                stack1.pop();
                double b=stack1.top()*1.0;
                stack1.pop();
	        double c=a*b*1.0; 
		stack1.push(c);
 //               cout<<"c is"<< c <<endl;
	    }
	    else if(ch=='/')
	    {
		double a=stack1.top()*1.0;
                stack1.pop();
                double b=stack1.top()*1.0;
                stack1.pop(); 
	        if(a==0)
		{
		    cout<<"division by zero"<<endl;
		    return 0;
		}
		double c=(1.0*b)/a;
		stack1.push(c);
//	        cout<<"c is"<< c <<endl;
	    }
	    else if (ch=='+')
	    {
	        double a=stack1.top()*1.0;
                stack1.pop();
                double b=stack1.top()*1.0;
                stack1.pop();
		double c=a+b;
		stack1.push(c);
//	        cout<<"c is"<< c <<endl;
	    }
	    else if (ch=='-')
  	    { 
   	    	double a=stack1.top()*1.0;
                stack1.pop();
                double b=stack1.top()*1.0;
                stack1.pop();
		double c=b-a;
		stack1.push(c);
//	        cout<<"c is"<< c <<endl;
	    }
	    else
	    {
        	cout<<"invalid input"<<endl;
                return 0;
	    }           
 //           cout<<"c is"<< c <<endl;
        }
    }
    size=stack1.size();
    for (int i=0; i< size;i++)
    {
        cout<<stack1.top()<<endl;
        stack1.pop();
    }
}





















