// haozhe gu 999200555
// Filename: Fraction.cpp
// this is the implement of the Class Fraction

#include<iostream>
#include<string>
#include<iomanip>
#include<stdexcept>
#include"Fraction.h"

using namespace std;
Fraction temp;
ostream &operator<<( ostream &output, Fraction &num)
{   
    if ((num.denominator)<0)
    {
	num.setdenominator(-(num.denominator));
        num.setnumerator(-(num.numerator));
    }
    if (num.denominator ==1)
    {
	output << num.numerator;
    }
    else
    {
         output << num.numerator << "/" << num.denominator;
    }
    return output;
}


istream &operator>>( istream &input, Fraction &num)
{ char dummy; 
    input >> num.numerator; 
    input >> dummy;
    input >> num.denominator;
//    num.gcd(num.numerator,num.denominator);
    return input;
}


Fraction &operator+( Fraction &x, Fraction &y)
{   int n, d;
//    Fraction temp; 
    n = x.getnumerator() * y.getdenominator() + y.getnumerator() * x.getdenominator();
    d = x.getdenominator() * y.getdenominator();
  
 //   x.gcd(numerator,denominator);
    temp.setnumerator(n);
    temp.setdenominator(d);
    temp.gcd();
 //   cout<<temp.getnumerator()<<'/'<<temp.getdenominator()<<endl;
    return temp;
}

  
Fraction& operator-( Fraction &x, Fraction &y)
{   int n, d;
//    Fraction temp;  
    n = x.getnumerator() * y.getdenominator() - y.getnumerator() * x.getdenominator();
    d = x.getdenominator() * y.getdenominator();
//    temp.setnumerator(n);
//    temp.setdenominator(d);
    temp.setnumerator(n);
    temp.setdenominator(d);
    temp.gcd();
    
     return temp;  
}


//class

Fraction::Fraction( int n, int d)
{   numerator=n;
    denominator=d;
    gcd();
}
void Fraction::gcd()
{   int n1, n2, remainder;
    setdenominator(getdenominator());
    n1 = getnumerator();
    n2 = getdenominator();
    remainder = n1 % n2;
    while(remainder != 0 )
    {
	n1 = n2;
	n2 = remainder;
	remainder = n1 % n2;
    }
    setnumerator(getnumerator()/n2);
    setdenominator(getdenominator()/n2);
}

Fraction& Fraction::operator=(const Fraction &x)
{ 
   // cout<<temp.getnumerator()<<"  "<<temp.getdenominator();
    setnumerator(temp.getnumerator());
    setdenominator(temp.getdenominator());   
    return *this;
}
 
void Fraction::setnumerator(int n)
{numerator = n;}

void Fraction::setdenominator(int d)
{   
    if(denominator != 0)
     {
	denominator = d;
      }
    else
      throw invalid_argument("division by zero");
} 

int Fraction::getnumerator()
{return numerator;}

int Fraction::getdenominator()
{return denominator;}



