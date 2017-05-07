#include<iostream>


using namespace std;

int main()
{ 
    char score[10][10]; 
    cout<<"  ";
    for(char x=97 ; x<107 ; x++)
    {
        cout<< x <<" ";
    }
    cout<<endl;

    cout<<" "<<"+"<<"-------------------"<<"+"<<endl;

    for (int i=0;i<10;i++)
    {
        cout<<i<<"|";
        for(int j=0;j<10;j++)
        {   
	    if(j==9)
	    {cout<<" ";}
	    else{cout<<"  ";}
        }
        cout<<"|"<<endl;
    }

    cout<<" "<<"+"<<"-------------------"<<"+"<<endl;
    char x=99;
    int i=x-97;
    cout<<i;
}
