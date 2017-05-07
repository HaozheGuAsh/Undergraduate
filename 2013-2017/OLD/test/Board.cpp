// Filename: Board.cpp
// Student ID: 999200555
// Name: Haozhe Gu

#include<iostream>
#include<stdexcept>
#include<vector>
#include"Board.h"
#include"Ship.h"
using namespace std;


Board::Board(void)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            score[i][j]=' ';
	}
    }
}


void Board::addShip(char type,int x1,int y1,int x2,int y2)
{
    Ship *shipptr;   
    if(shipList.size()<=10)
    {     
        shipptr=Ship::makeShip(type,x1,y1,x2,y2);
	shipList.push_back(shipptr);  
    }  
}


void Board::print(void)
{
    cout<<"   ";
    for(char x=97 ; x<107 ; x++)
    {
	cout<< x <<" ";
    }
    cout<<endl;
   
    cout<<"  "<<"+"<<"-------------------"<<"+"<<endl;
    
    for (int i=0;i<10;i++)
    {
	cout<<" "<<i<<"|";
	for(int j=0;j<10;j++)
        {   
	    if(j==9)
	    {cout<<score[i][j];}
	    else{cout<<score[i][j]<<" ";}	    
	}
        cout<<"|"<<endl;
    }   
    
    cout<<"  "<<"+"<<"-------------------"<<"+"<<endl; 
}

void Board::hit(char c, int i)
{ 
    int x,y;
    y=i;
    x=c-97;
    if(y>9 || y<0 ||x>9 ||x<0){throw invalid_argument("invalid input");}
    if(score[x][y]!=' ')
    {
	if(shipAt(x,y))
        {   
	    shipAt(x,y)->decreaseLevel(); 
	    score[x][y]='*';
            if(shipAt(x,y)->level()==0){cout<<shipAt(x,y)->name()<<" sunk"<<endl;}
            
        }else
	{
	    score[x][y]='x';
	}
        	
    }
         
} 

int Board::level(void)
{
    int total=30;
    int hit=0;
    for(int i=0;i<10;i++)
    {
	for(int j=0;j<10;j++)
        {
	    if(score[i][j]=='*'){hit++;}
        }	
    }
    total=total-hit;
    return  total;
}

Ship *Board::shipAt(int x, int y)
{
    Ship *shipptr=0;
    vector<Ship*>::iterator list;
    for(list=shipList.begin();list!=shipList.end();list++)
    {
	if((*list)->includes(x,y))
        {
	    shipptr=*list;
	    break;
        }
    }
    return shipptr;
}




