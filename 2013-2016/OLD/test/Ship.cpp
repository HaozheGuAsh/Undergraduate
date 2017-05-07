// Filename: Ship.cpp
// Student ID: 999200555
// Name: Haozhe Gu

#include <iostream>
#include "Ship.h"
#include <stdexcept>
using namespace std;

//class ship implement

//Ship::Ship(){}
//virtual Ship::~Ship(){}

int Ship::getX(int i)const
{
    if (i==0){return x1;}
    if (i==size()-1){return x2;}
    if (x1==x2){return x1;}
    if (x1>x2){return x1-i;}
    return x1+i;
}

int Ship::getY(int i)const
{
    if (i==0){return y1;}
    if (i==size()-1){return y2;}
    if (y1==y2){return y1;}
    if (y1>y2){return y1-i;}
    return y1+i;
}

void Ship::print()const
{
    cout<<name()<<" "<<"from"<<" "<<"("<<getX(0)<<","<<getY(0)<<")"<<" to "
        <<"("<<getX(size()-1)<<","<<getY(size()-1)<<")"<<endl;
}

bool Ship::includes(int x,int y)
{
    if ((( (x<=x1) && (x>=x2) )||( (x>=x1) && (x<=x2) ) )   &&   (( (y<=y1) && (y>=y2) )||( (y>=y1) && (y<=y2) ) )) 
    {
        return true;	 
    }
    return false;
}

int Ship::level()const
{   
    return lev;
}

void Ship::decreaseLevel()
{
    if(lev>0)
    {
	lev--;
    }
} 

Ship*  Ship::makeShip(char ch,int x1,int y1,int x2,int y2)
{
    Ship *ptr;
    if (ch=='A')
    {ptr = new  AircraftCarrier(x1,y1,x2,y2);}

    else if(ch=='B')
    {ptr = new BattleShip(x1,y1,x2,y2);}

    else if(ch=='C')
    {ptr = new Cruiser(x1,y1,x2,y2);}

    else if(ch=='D')
    {ptr = new Destroyer(x1,y1,x2,y2);}
    
    else{throw invalid_argument("invalid configuration");}
    
    return ptr; 
}

void Ship::setPos(int a1,int b1,int a2,int b2)
{   
    if(checkConfig(a1,b1,a2,b2)==true)
    {
     x1=a1;
     x2=a2;
     y1=b1;
     y2=b2;
    }
    else{throw invalid_argument("invalid configuration");}
}

bool Ship::checkConfig(int x1,int y1,int x2,int y2)
{
    if((x1==x2) || (y1==y2))
    { 
	if(((x1-x2)==size()-1 || (x2-x1)==size()-1) || ((y1-y2)==size()-1 || (y2-y1)==size()-1))
	{ 
            return true;
        }
    }
    return false;      
}

//derived class

AircraftCarrier::AircraftCarrier(int x1,int y1,int x2,int y2)
{
    setPos(x1,y1,x2,y2);
    lev=size();
}

const char* AircraftCarrier::name()const
{
    const string name="AircraftCarrier";
    const char *ptr = &name[0];
    return ptr;
}

int AircraftCarrier::size()const
{return 5;}

//derived class

BattleShip::BattleShip(int x1,int y1,int x2,int y2)
{
    setPos(x1,y1,x2,y2);
    lev=size();
}

const char* BattleShip::name()const
{
    const string name="BattleShip";
    const char *ptr = &name[0];
    return ptr;
}

int BattleShip::size()const
{return 4;}

//derived class

Cruiser::Cruiser(int x1,int y1,int x2,int y2)
{
    setPos(x1,y1,x2,y2);
    lev=size();
}

const char* Cruiser::name()const
{
    const string name="Cruiser";
    const char *ptr = &name[0];
    return ptr;
}

int Cruiser::size()const
{return 3;}

//derived class

Destroyer::Destroyer(int x1,int y1,int x2,int y2)
{
    setPos(x1,y1,x2,y2);
    lev=size();
}

const char* Destroyer::name()const
{
    const string name="Destroyer";
    const char *ptr = &name[0];
    return ptr;
}

int Destroyer::size()const
{return 2;}

