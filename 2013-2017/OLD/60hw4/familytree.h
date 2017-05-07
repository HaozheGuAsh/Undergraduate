#ifndef FAMILYTREE_H
#define	FAMILYTREE_H

#include "familyRunner.h"
#include "QuadraticProbing.h"
#include "LinkedList.h"
//#include "QueueAr.h"
class FamilyTree {
  
public:
  FamilyTree(Family *families, int familyCount);
  void runQueries(Query *queries, Person *answers, int queryCount);
  
  QuadraticHashTable<Human> table;
//  List<int>list;
//  ListItr<int>itr;
//  Queue<Human> first;
//  Queue<Human> second;
  Human ancestors1[50000];
  Human ancestors2[50000];
  int findindex(Person *person);
  int fillarray(int i, int index);
  int posarray;
  Human findminancestor(int pos1,int pos2);
};
/*class Human : public Person {

public:

//short year;
//char lastName[12];
//char firstName[12];
//char gender;
Person *spouse;
Person *children;
int value;//year+lastname+firstname
int index;//pos in hash table
Person *dad;
Person *mum;
short childCount;
};*/

#endif	/* FAMILYTREE_H */

