// longInt.h Haozhe Gu 999200555
#ifndef _LongInt
#define _LongInt
 
#include<iostream>
#include<iomanip>
#include "StackLi.h"
#include "LinkedList.h"
#include<cctype>
using namespace std;

class LongInt
{
     friend   ostream &operator<<( ostream &, LongInt &);
     friend   istream &operator>>( istream &, LongInt &);
     friend        LongInt &operator+( LongInt &, LongInt &);
	public:
    

//        ostream &operator<<( ostream &, LongInt &);
 //       istream &operator>>( istream &, LongInt &);
  //      LongInt &operator+( LongInt &, LongInt &);
   //     LongInt &operator=(const LongInt &);
       
	private:
	StackLi<int> digit;
	StackLi<int> digit2;
    
        
};



#endif
