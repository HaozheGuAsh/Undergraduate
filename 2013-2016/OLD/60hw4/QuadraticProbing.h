        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "vector.h"
        #include "mystring.h"
        #include "familyRunner.h"
        #include "LinkedList.h"
	#include <cstring>
     //   #include "familytree.h"
        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings
class Human : public Person {

public:

//short year;
//char lastName[12];
//char firstName[12];
//char gender;
Person person;
Person spouse;
Person *children;
int value;//year+lastname+firstname
int index;//pos in hash table
bool parent;
int dadindex;
int mumindex;
short childCount;
};

        template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( HashedObj  notFound, int size );
            QuadraticHashTable(  QuadraticHashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ), currentSize( rhs.currentSize ) { }

             HashedObj & find(  HashedObj & x ) ;

            void makeEmpty( );
            int insert(  HashedObj  x );
            void remove(  HashedObj&  x );

             QuadraticHashTable & operator=(  QuadraticHashTable & rhs );

            enum EntryType { ACTIVE, EMPTY, DELETED };
   
//add function
            Human mycopy(Family *families);
	    void setparent(Human human);
            int calvalue(Human human);
            int hash(Human human,int size);
            int size;
            struct HashEntry
            {
                HashedObj element;
                EntryType info;

                HashEntry(  HashedObj  e = HashedObj( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };

            vector<HashEntry> array;
            int currentSize;
             HashedObj ITEM_NOT_FOUND;
            bool isPrime( int n ) ;
            int nextPrime( int n );
            bool isActive( int currentPos ) ;
            int findPos( HashedObj & x );
        //    int hash(  string & key, int tableSize ) ;
            int hash( int key, int tableSize );
            void rehash( );
    
        };

       #include "QuadraticProbing.cpp" 
        #endif
