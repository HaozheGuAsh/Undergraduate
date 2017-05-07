// haozhe gu 999200555
// Filename: Fraction.h
// this class will help to solve calculation involve fraction

#ifndef FRACTION_H
#define FRACTION_H

#include<iostream>

using namespace std;

class Fraction
{
    friend ostream &operator<<( ostream &, Fraction &);
    friend istream &operator>>( istream &, Fraction &);
    friend Fraction &operator+( Fraction &, Fraction &);
    friend Fraction &operator-( Fraction &, Fraction &);
    
    public:
        Fraction(int=10, int=10);//default constructor
	
	void gcd();
	void setnumerator(int);
	void setdenominator(int);
        
	int getnumerator();
        int getdenominator();

	Fraction &operator=(const Fraction &);
    private:
	int numerator;
	int denominator;
    
};
#endif
