// Author: Sean Davis

#include "familytree.h"
#include <cstring>
#include "QuadraticProbing.h"
#include "familyRunner.h"
#include <stdio.h>
#include <cstdlib>

using namespace std;
int compare(const void *p1,const void*p2);


FamilyTree::FamilyTree(Family *families, int familyCount): table (Human(),2*familyCount)
{ int pos;
  table.size=table.array.size();
   // cout<<familyCount;
 // cout<<"size is"<<table.size<<"actual size"<<table.array.size()<<endl;
  for(int i =0;i<familyCount;i++)
  {
    pos=table.insert( table.mycopy(&families[i]));
    table.array[pos].element.index=pos;
//    table.setparent(table.array[pos].element);
  //  cout<<"look!!"<<2*familyCount<<endl;
   // table.array[i].element.index=table.findPos(table.array[i].element);
    cout<<i<<table.array[pos].element.person.year<<"index"<<table.array[pos].element.index<<endl; 
  }

/* for(int i= 0;i<table.size;i++)
 {
   for(int k=0;k<table.size;k++)
   {
      if((table.array[i].element.value==table.array[k].element.value) && i!=k)
        {cout<<"value conlision!!!!!!!!!!!!!!!!!"<<table.array[i].element.value<<"  year  "<<table.array[i].element.person.year<<"firstname  "<<table.array[i].element.person.firstName<<"last name"<<table.array[i].element.person.lastName<<"    "<<table.array[k].element.value<<"  year "<<table.array[k].element.person.year<<"first name"<<table.array[k].element.person.firstName<<"lastname"<< table.array[k].element.person.lastName<<endl;}
   }
 }
 */

 
  //cout<<"enter!!!"<<table.currentSize<<endl;
  for(int i = 0;i<table.size;i++)//transverse table
  {
  //  cout<<"enter1";
  //  cout<<"hi"<<table.array[i].element.childCount<<endl;
    if((table.array[i].element.childCount>0))// && table.array[i].element.gender=='M')//find parent then set his children's parents
    {
    // cout<<"enter2"<<endl;
      for(int k=0;k<table.array[i].element.childCount ;k++)//transverse children
      {
//      cout<<"enter3";
       // pos=0;
       // if(i>40000){pos=i-40000;}
	for(int j=0;j<table.size;j++)
       	{//if(j=table.size-1){pos=0;}
      //cout<<"enter4";
	  if(table.array[j].element.person.year == ((table.array[i].element.children)+k)->year
 	     && strcmp(table.array[j].element.person.lastName, ((table.array[i].element.children)+k)->lastName)==0
             && strcmp(table.array[j].element.person.firstName, ((table.array[i].element.children)+k)->firstName)==0
	     && table.array[j].element.person.gender==((table.array[i].element.children)+k)->gender)
          { 
     // cout<<"enter5     ";
            table.array[j].element.parent=1;
	    if(table.array[i].element.person.gender=='M')
            {
   //   cout<<"enter6     ";
	      table.array[j].element.dadindex=table.array[i].element.index;
             // table.array[j].element.mum=table.array[i].element.spouse;
             //exit once set parents
            
  //           cout<<"dad index "<<i<<"child "<<j<<endl;
            }else if(table.array[i].element.person.gender=='F')
            {
     // cout<<"enter7      ";
	      table.array[j].element.mumindex=table.array[i].element.index;
             
  //         cout<<"mum index"<<table.array[j].element.mumindex<<endl; 
            }
           // if(j=table.size-1){j=0;}
            break;
                      
          }
        }
		
      } 
 
    }

  }
/* for(int i= 0;i<table.size;i++)
 {
   for(int k=0;k<table.size;k++)
   {
      if((table.array[i].element.value==table.array[k].element.value) && i!=k)
        {cout<<"value conlision!!!!!!!!!!!!!!!!!"<<table.array[i].element.value<<"    "<<table.array[k].element.value<<endl;}
   }
 }*/
// {cout<<"see parent value"<<table.array[i].element.parent<<endl;}
}  // FamilyTree()

void FamilyTree::runQueries(Query *queries, Person *answers, int queryCount)
{ Human human;
 // Queue<Human>first(100000);
 // Queue<Human>second(100000);
  for(int i=0;i<queryCount;i++)
  {//int pos1=0,pos2=0; 
 //   cout<<"enter runqueries!!!!!!!!!!!!!!!!!"<<"  "<<i<<"  "<<endl; 
    int pos1=fillarray(1,findindex(&( (queries+i)->person1) ));
 //   cout<<"middle fill"<<endl;
 
    posarray=0;
    cout<<"pos1"<<pos1<<endl;
//   cout<<findindex(& (queries+i)->person2);
    int pos2=fillarray(2,findindex(&( (queries+i)->person2) ));
    posarray=0;
//    cout<<"pos1"<<pos1<<"pos2"<<pos2<<endl;
    
    human = findminancestor(pos1,pos2);
   // cout<<"here"<<endl;
    *(answers+i)=human.person;
    cout<<"run quer  ans"<<human.person.year<<"  "<<human.person.lastName<<"  "<<human.person.firstName<<endl;
  } 
    for(int x=0;x<5000;x++)
     {ancestors1[x]=Human();
      ancestors2[x]=Human();
     } 
}  // runQueries()
int FamilyTree:: findindex(Person *person)
{
  for(int k=0;k<table.size;k++)
  {
    if(table.array[k].element.person.year == person->year
             && strcmp(table.array[k].element.person.lastName, person->lastName)==0
             && strcmp(table.array[k].element.person.firstName,person->firstName)==0
             && table.array[k].element.person.gender==person->gender)
    {
   //   cout<<"enter find"<<"index"<<k<<endl;
      return k;
    }
  }
  return 0;
}
Human FamilyTree::findminancestor(int pos1,int pos2)
{// cout<<"enter findmin  !!!!!"<<endl;
  int position1=0,position2=0;
  Human *ptr1=ancestors1;
  Human *ptr2=ancestors2;
 // cout<<"enter findmin"<<endl;
 //   cout<<"pos1"<<pos1<<"pos2"<<pos2<<endl;
  qsort( ptr1,pos1,sizeof(Human),compare);
  qsort( ptr2,pos2,sizeof(Human),compare);
 
 Human no;
  no.person.year=-1;
  no.person.lastName[0]=0;
  no.person.firstName[0]=0;
 
 // for(int f=0;f<pos1;f++)
  //{cout<<"check array1   "<<ancestors1[f].person.year<<"value"<<ancestors1[f].value<<ancestors1[f].person.firstName<<ancestors1[f].person.lastName<<endl;}
//  for(int l=0;l<pos2;l++)
//  {//cout<<"check array2   "<<ancestors2[l].person.year<<"value"<<ancestors2[l].value<<ancestors2[l].person.firstName<<ancestors2[l].person.lastName<<endl;}

  while(position1<pos1 || position2<pos2)
  {
  //  cout<<"position1  "<<position1<<"  pos1  "<<pos1<<"  position2  "<<position2<<"  pos2  "<<pos2<<endl;
    if(ancestors1[position1].person.year==ancestors2[position2].person.year)
    {
    //  cout<<"find common"<<ancestors1[position1].person.firstName<<endl;
    	if(strcmp(ancestors1[position1].person.lastName,ancestors2[position2].person.lastName)==0)
        {    
	    if(strcmp(ancestors1[position1].person.firstName,ancestors2[position2].person.firstName)==0)
	    {
                
	            if(ancestors1[position1].person.gender==ancestors2[position2].person.gender)
		    {   
		       // if(ancestors1[position1].person.year == ancestors2[position2].person.year
                    //	&& strcmp(ancestors1[position1].person.lastName,ancestors2[position2].person.lastName)==0
                    //	&& strcmp(ancestors1[position1].person.firstName,ancestors2[position2].person.firstName)==0
                    //	&& ancestors1[position1].person.gender==ancestors2[position2].person.gender)
		        
		            return ancestors1[position1];
		        
                       // else {position1++; break;}
cout<<"here!!"<<ancestors1[position1].person.lastName<<ancestors1[position1].person.firstName<<ancestors1[position1].person.gender<<"    "<<ancestors2[position2].person.lastName<<ancestors2[position2].person.firstName<<ancestors2[position2].person.gender;
		    }
		    else if(ancestors1[position1].person.gender > ancestors2[position2].person.gender)
		    {
			position1++;
			if(!(position1<pos1)){break;}
		    }
		    else if(ancestors1[position1].person.gender < ancestors2[position2].person.gender)
		    {
			position2++;
			if(!(position2<pos2)){break;}
		    }
	    
            }
	    else if(strcmp(ancestors1[position1].person.firstName,ancestors2[position2].person.firstName)>0)
            {
		    position1++;
		    if(!(position1<pos1)){break;}
	    }
            else if(strcmp(ancestors1[position1].person.firstName,ancestors2[position2].person.firstName)<0)
            {
		    position2++;
		    if(!(position2<pos2)){break;}
	    }
		
	}
	else if(strcmp(ancestors1[position1].person.lastName,ancestors2[position2].person.lastName)>0)
	{
		position1++;
		if(!(position1<pos1)){break;}
	}
	else if(strcmp(ancestors1[position1].person.lastName,ancestors2[position2].person.lastName)<0)
	{
		position2++;
		if(!(position2<pos2)){break;}	
	}
        
    } 
    else if(ancestors1[position1].person.year > ancestors2[position2].person.year)
    {// cout<<"pos1+"<<endl;
      position1++;
      if(!(position1<pos1)){break;}
    }else if(ancestors1[position1].person.year < ancestors2[position2].person.year)
    {// cout<<"pos2+"<<endl;
      position2++;
      if(!(position2<pos2)){break;}
    }
  }
 // cout<<"no common"<<endl;
 // Human no;
 // no.person.year=-1;
 // no.person.lastName[0]=0;
 // no.person.firstName[0]=0;
 // cout<<"no"<<no.person.year<<"  "<<no.person.lastName<<endl;
  return no;
}
int FamilyTree::fillarray(int i,int index)
{ //cout<<"index in fill"<<index<<endl; 
  if(i==1)
  {
    ancestors1[posarray]=(table.array[index].element);
//    cout<<"enter fillarray 1"<<"position"<<posarray<<"firstname"<<ancestors1[posarray].person.firstName<<endl;
    posarray++;
   // while(table.array[index].element.parent==1)
   // first.enqueue(table.array[index].element);
   // {
   //   setqueue(i,table.array[index].element.dadindex);
   //   setqueue(i,table.array[index].element.mumindex);
   // }  
  }
  else if(i==2)
  {// cout<<index<<endl;
    ancestors2[posarray]=(table.array[index].element);
   // cout<<"enter fillarray 2"<<"position"<<posarray<<"firstname"<<ancestors2[posarray].person.firstName<<endl;
    posarray++;
   // while(table.array[index].element.parent==1)
   // {
     
   // }
  }
  //cout<<"near if"<<table.array[index]<<endl;
  if(table.array[index].element.parent==1)
  {
   //   cout<<"have parent"<<endl;
      fillarray(i,table.array[index].element.dadindex);
      fillarray(i,table.array[index].element.mumindex);
  }
  return posarray;  
}
int compare(const void *p1,const void*p2)
{ 
  if((*(Human*)p1).person.year==(*(Human*)p2).person.year)
  {
    if(strcmp((*(Human*)p1).person.lastName,(*(Human*)p2).person.lastName)>0)
    {return -1;}
    else if(strcmp((*(Human*)p1).person.lastName,(*(Human*)p2).person.lastName)<0)
    {return 1;}
    else if(strcmp((*(Human*)p1).person.lastName,(*(Human*)p2).person.lastName)==0)
    {
	if(strcmp((*(Human*)p1).person.firstName,(*(Human*)p2).person.firstName)>0){return -1;}
        else if(strcmp((*(Human*)p1).person.firstName,(*(Human*)p2).person.firstName)<0){return 1;}
        else if(strcmp((*(Human*)p1).person.firstName,(*(Human*)p2).person.firstName)==0)
        {
	    if((*(Human*)p1).person.gender>(*(Human*)p2).person.gender){return -1;}
            else if((*(Human*)p1).person.gender<(*(Human*)p2).person.gender){return 1;}
            
 	    
        }   
    }
  }
  if((*(Human*)p1).person.year>(*(Human*)p2).person.year) return -1;
//  if(*(Human*)p1.person.year==*(Human*)p2.person.year) return 0;
  if((*(Human*)p1).person.year<(*(Human*)p2).person.year) return 1;
  return 0;
}






