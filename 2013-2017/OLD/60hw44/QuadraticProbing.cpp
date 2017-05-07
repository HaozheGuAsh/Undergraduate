        #include "QuadraticProbing.h"


        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isPrime( int n )
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        template <class HashedObj>
        Human QuadraticHashTable<HashedObj>::mycopy(Family *families)
{
          Human human;
	 // Person *person=families.person;
         // human.spouse=families[i].spouse;
          human.person=(families->person);
          human.spouse=(families->spouse);
          human.children=families->children;
          human.childCount=families->childCount;
          human.value=calvalue(human);
          human.parent=0;
          human.dad=0;
          human.mum=0;
       //  cout<<"hei!"<<currentSize<<endl;
      //   cout<<"in quadratic"<<human.person.year<<endl;
          return human; 
        
}
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::calvalue(Human human)
{       
	int value=0;
	for(int i =0;i<=10;i++)
        {
	  value=value+(human.person.lastName[i])* (human.person.firstName[i]);
     //     cout<<"current value "<<value<<"char"<<human.lastName<<human.firstName<<endl;
        }
        value=value+human.person.year;
      //  cout<<"year value"<<human.person.year<<endl;
        return value;
}

/*        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::setparent(Human human)
{
 	       
}*/

        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::nextPrime( int n ) 
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }

        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        QuadraticHashTable<HashedObj>::QuadraticHashTable(  HashedObj  notFound, int size )
          : array( nextPrime( size ) ), ITEM_NOT_FOUND( notFound )
        {
            makeEmpty( );
        }

        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::insert(  HashedObj  x )
        {
                // Insert x as active
            int currentPos = findPos( x );
        //   cout<<"in quadratic  position"<<currentPos<<"year"<<x.person.year<<"value"<<x.value<<endl;
            if( isActive( currentPos ) )
                return currentPos;
            array[ currentPos ] = HashEntry( x, ACTIVE );
            return currentPos;
                // Rehash; see Section 5.5
            if( ++currentSize > array.size( ) / 2 )
                rehash( );
        }

        /**
         * Expand the hash table.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::rehash( )
        {
            vector<HashEntry> oldArray = array;

                // Create new double-sized, empty table
            array.resize( nextPrime( 2 * oldArray.size( ) ) );
            for( int j = 0; j < array.size( ); j++ )
                array[ j ].info = EMPTY;

                // Copy table over
            currentSize = 0;
            for( int i = 0; i < oldArray.size( ); i++ )
                if( oldArray[ i ].info == ACTIVE )
                    insert( oldArray[ i ].element );
        }

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::findPos( HashedObj & x ) 
        {
/* 1*/      int collisionNum =0;
/* 2*/      int currentPos = hash( x, array.size( ) );
           // cout<<"in findpos  position"<<currentPos;
/* 3*/      while( array[ currentPos ].info == ACTIVE)
            {//cout<<"re find place"<<collisionNum;
/* 4*/         currentPos += 2* ++collisionNum - 1;  // Compute ith probe
/* 5*/         currentPos=currentPos % array.size();
            //   currentPos+=x.person.year;  
                    if( currentPos >= array.size( ) )
/* 6*/              currentPos-=array.size( );
            }

/* 7*/      return currentPos;
        }
        
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::hash(Human human, int size)
        {
          return(human.value) % size;
        }
        /**
         * Remove item x from the hash table.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::remove(  HashedObj & x )
        {
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                array[ currentPos ].info = DELETED;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
         HashedObj & QuadraticHashTable<HashedObj>::find(  HashedObj & x ) 
        {
            int currentPos = findPos( x );
            return isActive( currentPos ) ? array[ currentPos ].element : ITEM_NOT_FOUND;
        }

        /**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < array.size( ); i++ )
                array[ i ].info = EMPTY;
        }

        /**
         * Deep copy.
         */
        template <class HashedObj>
         QuadraticHashTable<HashedObj> & QuadraticHashTable<HashedObj>::
        operator=(  QuadraticHashTable<HashedObj> & rhs )
        {
            if( this != &rhs )
            {
                array = rhs.array;
                currentSize = rhs.currentSize;
            }
            return *this;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isActive( int currentPos ) 
        {
            return array[ currentPos ].info == ACTIVE;
        }

        /**
         * A hash routine for string objects.
         */
 /*       template <class HashedObj>
        int QuadraticHashTable<HashedObj>::hash( const string & key, int tableSize ) 
        {
            int hashVal = 0;

            for( int i = 0; i < key.length( ); i++ )
                hashVal = 37 * hashVal + key[ i ];

            hashVal %= tableSize;
            if( hashVal < 0 )
                hashVal += tableSize;

            return hashVal;
        }

*/
       
        // * A hash routine for ints.
         
         template <class HashedObj>
        int QuadraticHashTable<HashedObj>::hash( int key, int tableSize ) 
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }

