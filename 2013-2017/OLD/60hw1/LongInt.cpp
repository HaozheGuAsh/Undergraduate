//Filename: LongInt.cpp
//HaozheGu 999200555 

#include<iostream>
#include<iomanip>
#include"LongInt.h"
#include "StackLi.h"
#include "LinkedList.h"
using namespace std;



istream &operator>>(istream &input,LongInt & a)
{
    char c,x;
    int  i;
    while(input>>c)
    {
//	x=input.peek();
//	if((x-'0')<0||(x-'0')>9){break;}
        i=c-'0';		
	a.digit.push(i);
        x=input.peek();
        if((x-'0')<0||(x-'0')>9){break;}

	
    }
    return input;
}
ostream &operator<<(ostream &output,LongInt &a)
{
    while(! (a.digit2.isEmpty()) )
    {
        output<<a.digit2.topAndPop();
    }
    return output;
}


LongInt &operator+( LongInt &a,LongInt&b)
{
    int add=0;
    int  c,d;
    while(  (!a.digit.isEmpty())  ||  (!b.digit.isEmpty())  )
    {  // cout<<a.digit.top();
	if(a.digit.isEmpty())
	{//  cout<<"a empty";
	    if(b.digit.top()+add>9)
	    {a.digit2.push(b.digit.topAndPop()+add-10);
	     add=1;}else{
	    a.digit2.push(b.digit.topAndPop()+add);
	    add=0;}
	}
	else if(b.digit.isEmpty())
	{ //  cout<<"b empty";
	    if(a.digit.top()+add>9)
	    {a.digit2.push(a.digit.topAndPop()+add-10);
	     add=1;}else{
	    a.digit2.push(a.digit.topAndPop()+add);
//	    cout<<a.digit2.top();
            add=0;}
	}
	else
	{   	    
            c=a.digit.topAndPop();
	    d=b.digit.topAndPop();
	    if( (c+d)>9)
	    {
		a.digit2.push(c+d-10+add);
		
	        add=1;
//	        cout<<a.digit2.top();
	    }
	    else
	    {
	        a.digit2.push(c+d+add);
//		cout<<a.digit2.top();
	        add=0;
	    }
	}
    }
    if(add==1){a.digit2.push(1);}
    return a;    
}
//LongInt::LongInt()
/*ostream &operator<<( ostream &output,LongInt &a)
{
    while(! (a.isEmpty()) )
    {
	cout<<a.pop();
    }
}
*/

