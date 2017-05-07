#include<iostream>
#include<vector>
using namespace std;

void print(vector<int>& v)
{
  for ( int i = 0; i < v.size(); i++ )
    cout << v[i] << " ";
  cout << endl;
}

int main()
{
  vector<int> v(10);
  print(v);

  // insert 3 at position 0
    vector<int>::iterator iter;
       iter = v.begin();
        cout << "insert 3 at position 0" << endl;
           v.insert(iter,3);
             print(v);
 
               // insert 7 at position 5
                 iter = v.begin()+5;
                   cout << "insert 7 at position 5" << endl;
                    v.insert(iter,7);
                       print(v);
  
                         // insert 8 at end
                           iter = v.end();
                             cout << "insert 8 at end" << endl;
                               v.insert(iter,8);
                                 print(v);
  
                                   // insert 9 at beginning using push front
                                     cout << "insert 9 using push_front" << endl;
//                                       v.push_front(9);
  //                                       print(v);
  
                                           // resize the vector
                                             cout << "resize(5)" << endl;
                                               v.resize(5);
                                                 print(v);
                                                 }
