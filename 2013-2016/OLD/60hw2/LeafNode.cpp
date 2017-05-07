#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()

LeafNode* LeafNode::removewithleft()
{
  if(leftSibling->getCount()-1>= (leafSize+1)/2)
    {// cout<<"borrow left"<<endl;
      insert(leftSibling->getMaximum());
      leftSibling->remove(leftSibling->getMaximum());
      if(parent){parent->resetMinimum(this);}
      return NULL;
    } //just borrowing
  else//merge
    {
      for(int i=0;i<count ; i++)
      {
	leftSibling->insert(values[i]);
      //  remove(values[0]); infinite loop
      }
      
      if(rightSibling)
      {
	leftSibling->setRightSibling(rightSibling);
        rightSibling->setLeftSibling(leftSibling);
      }//if we have rightSibling
      else//no rightSibling
      {
	leftSibling->setRightSibling(NULL);//to NULL
      }
      return this;
    }//remove at left and merge
}

LeafNode* LeafNode::removewithright()
{    //  cout<<rightSibling->getCount()-1<<endl;

  if(rightSibling->getCount()-1>= (leafSize+1)/2)
    {
   //         cout<<"ok1"<<endl;
    //        cout<<rightSibling->getMinimum();
      insert(rightSibling->getMinimum());
      //      cout<<"ok2"<<endl;
      rightSibling->remove(rightSibling->getMinimum());
//      cout<<"right borrow ok"<<endl;
      if(parent){parent->resetMinimum(this);}
      return NULL;
    } //just borrowing
  else//merge
    {//cout<<"okmerge"<<endl;
      for(int i=0; i<count ; i++)
      {
//	cout<<values[i]<<endl;
        rightSibling->insert(values[i]);  
      }
     // cout<<"ok2"<<endl;
   //  cout<<"this"<<getMinimum()<<getMaximum()<<endl<<"right"<<rightSibling->getMinimum()<<getMaximum()<<endl;
      if(leftSibling)
      {
        rightSibling->setLeftSibling(leftSibling);
        leftSibling->setRightSibling(rightSibling);
      }//if we have leftSilbling
      else//no leftSilbling
      {
        rightSibling->setLeftSibling(NULL);//to NULL
      } 
   //   cout<<"this"<<getMinimum()<<getMaximum()<<endl<<"right"<<rightSibling->getMinimum()<<getMaximum()<<endl;
                                                                                                         
      return this;
    }
    
}
void LeafNode::removewiththis(int value,int pos)
{
  int i;
//  cout<<"count"<<count<<endl<<"position"<<pos;
  for(i=pos;i < count-1 ;i++)
    {
      values[i]=values[i+1];
    }
  
  values[count-1]=0;
  count--;

  if(pos==0 && parent)
  {
    parent->resetMinimum(this);
  } 
}

void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;//insert to right
  else//insert to middle need to shift right
  {
    last = values[count - 1];//last value

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1,where we insert at top
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;
 // cout<<"OK"
  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

LeafNode* LeafNode::remove(int value)
{
  int pos;

  for(pos=0; pos<count-1&&values[pos]!=value;pos++);
  removewiththis(value,pos);
//  cout<<"leaf count"<<count<<endl;

  if(count < ((leafSize+1)/2) ) 
  {
   // cout<<"enter here"<<leftSibling <<endl<< rightSibling<<endl;
    if(leftSibling)
      {
//	cout<<"left"<<leftSibling<<endl;
        return removewithleft();
       
      }else
      if(rightSibling)
      {
//	cout<<"right"<<rightSibling<<endl;
       	return removewithright();
      }
  }
 
  if(pos==0 && parent)
    {parent->resetMinimum(this);} 
  return NULL;
}
void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()




LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

