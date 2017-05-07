#include<iostream>
#include"Ship.h"
#include"Board.h"
#include<vector>
#include<iterator>
#include<stdexcept>


using namespace std;


Board::Board()
{
  int i;
  int k;
  for(i=0;i<=9;i++)
  {
   for(k=0;k<=9;k++)
    {
     score[i][k]=' ';
    }
   }
}

void Board::addShip(char type, int x1, int y1, int x2, int y2)
{ if(shipList.size()<=10)
 { Ship* shipptr;
  shipptr=Ship::makeShip(type,x1,y1,x2,y2);
  shipList.push_back(shipptr);
 }
}

void Board::print()
{
  cout<<"   "<<"a b c d e f g h i j"<<endl;
  cout<<"  +";
  for(int m=1;m<=19;m++)
    cout<<"-";
  cout<<"+"<<endl;
  for(int k=0;k<=9;k++)
  { cout<<" "<<k<<"|";
    for(int i=0;i<=9;i++)
      {//if((score[i][k]=='*')||(score[i][k]=='x'))
       cout<<score[i][k];
      // else
      // cout<<' ';
       if(i==9)
         break;
       cout<<" ";
      }
    cout<<"|"<<endl;
   }
  cout<<"  "<<"+";
  for(int m=1;m<=19;m++)
    cout<<"-";
  cout<<"+"<<endl;
}

void Board::hit(char c, int i)
{ int a= c;
  Ship *ptr;
  if(c<97||c>106)
    throw invalid_argument("invalid input");
  if(i<0||i>9)
    throw invalid_argument("invalid input");
  if(shipAt(a-97,i))
   {ptr=shipAt(a-97,i);
   if(score[a-97][i]!='*')
      ptr->decreaseLevel(); 
   if(ptr->level()==0)
      cout<<ptr->name()<<" sunk"<<endl;   
      score[a-97][i]='*';}
  else{
    score[a-97][i]='x';
     }
}

int Board::level()
{ int level=30;
  int count=0;
  for(int i=0;i<=9;i++)
  { for(int k=0;k<=9;k++)
    { if((score[i][k])=='*')
        count++;
    }
  }
  level=level-count;
  return level;
}

Ship* Board::shipAt(int x , int y)
{ 
  Ship* ptr=0;
  vector<Ship*>::iterator it;
  for(it=shipList.begin();it!=shipList.end();it++)
  { if( (*it)->includes(x,y))
    { ptr=*it;
      break;
    }
  } 
 return ptr;
}
      
