//Haozhe Gu 999200555
#include<iostream>
#include<fstream>
#include"CPUTimer.h"
#include"LinkedList.h"
#include"StackAr.h"
#include"dsexceptions.h"
#include"CursorList.h"
#include"QueueAr.h"
#include"StackLi.h"
#include"vector.h"
#include"SkipList.h"
vector<CursorNode<int> > cursorSpace(250000);
using namespace std;

int getChoice();
void RunList(char* filename);
void RunCursorList(char* filename);
void RunStackAr(char* filename);
void RunStackLi(char* filename);
void RunQueueAr(char* filename);
void RunSkipList(char* filename);

int main()
{
char filename[80];
CPUTimer ct;
cout<<"Filename >>";
cin>>filename;
int choice;
do {
choice = getChoice();
ct.reset();
//cout<<"      "<<"ADT Menu"<<endl;
switch (choice)
{
  case 1: RunList(filename); break;
  case 2: RunCursorList(filename); break;
  case 3: RunStackAr(filename); break;
  case 4: RunStackLi(filename); break;
  case 5: RunQueueAr(filename); break;
  case 6: RunSkipList(filename); break;
}
     cout << "CPU time: " << ct.cur_CPUTime() << endl;
} while(choice > 0);
}

int getChoice()
{
    int choice;
    cout<<"      "<<"ADT Menu"<<endl;
    cout<<"0. Quit \n1. Linkedlist \n2. CursorList \n3. StackAr \n4. StackLi \n5. QueueAr \n6. SkipList "<<endl;
    cout<<"Your choice >> ";
    cin>>choice;
    return choice;         
}
void RunQueueAr(char* filename)
{
    char com,ary[1000];
    int value;
    Queue<int> queue(250000);
   // cout<<filename;
    ifstream inputfile(filename);
    inputfile.getline(ary,1000);
    while(inputfile>>com>>value)
    {
        if(com=='i')
        {queue.enqueue(value);}
        else if (com=='d')
        {queue.dequeue();}

    }
    
}
void RunSkipList(char* filename)
{
    char com,ary[1000];
    int value;
    SkipList<int> list(-1,250000);;
    ifstream inputfile(filename);
   // getline(inputfile,ary);
    inputfile.getline(ary,1000);
    while(inputfile>>com>>value)
    {
        if(com=='i')
        {list.insert(value);}	       
        else if (com=='d')
        {list.deleteNode(value);}

    }
}
void RunCursorList(char* filename)
{
    char com,ary[1000];
    int value;
    CursorList<int> cur(cursorSpace);
    CursorListItr<int> itr=cur.zeroth();
    ifstream inputfile(filename);
//    getline(inputfile,ary);
     inputfile.getline(ary,1000); 
    while(inputfile>>com>>value)
    {
        if(com=='i')
        {cur.insert(value,itr);}
	
        else if (com=='d')
        {cur.remove(value);}

    }

}
void RunStackAr(char* filename)
{
    char com,ary[1000];
    int value;
    StackAr<int> stack(250000);
    ifstream inputfile(filename);
    inputfile.getline(ary,1000);
 //   getline(inputfile,ary);
     while(inputfile>>com>>value)
    {
        if(com=='i')
        {stack.push(value);}

        else if (com=='d')
        {stack.pop();}

    }

}
void RunStackLi(char* filename)
{
    char com,ary[1000];
    int value;
    StackLi<int> stack;
    ifstream inputfile(filename);
    inputfile.getline(ary,1000);
//    getline(inputfile,ary);
    while(inputfile>>com>>value)
    {
        if(com=='i')
        {stack.push(value);}
        else if (com=='d')
        {stack.pop();}

    }      
}

void RunList(char* filename)
{
    char com,ary[1000];
    int value;
    List<int> list;
    ListItr<int> itr=list.zeroth();
    ifstream inputfile(filename);
    inputfile.getline(ary,1000);
//    getline(inputfile,ary);
    while(inputfile>>com>>value)
    {
	if(com=='i')
	{list.insert(value,itr);}
        else if (com=='d')
	{list.remove(value);}
   
    }

}






































