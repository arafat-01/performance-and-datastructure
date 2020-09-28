
#ifndef SET_INCLUDED
#define SET_INCLUDED    1 

#include <iostream>

// It is good to have a look at the list-based implementation
// of stack again. This implementation is similar.

struct treenode
{
   int val;
   treenode* left;
   treenode* right;

   treenode( int val )
      : val( val ),
        left( nullptr ),
        right( nullptr )  
   { }

};


void deallocate( treenode* n ); 
   // Deallocate complete tree n.

void writecopy( treenode** to, treenode* from );
   // Write a copy of from into *to.

const treenode* find( const treenode* n, int i );
treenode** find( treenode** n, int i );

treenode* removerightmost( treenode** from ); 
   // Step to the right as long as possible. When we get
   // stuck, we are in the rightmost node. Remove it, and
   // return it. (Don't delete it.)
   // *from cannot be the empty tree!

void print( std::ostream& out, const treenode* n, size_t indent );
   // Print the tree as tree.

size_t size( const treenode* n ); 
   // Returns the total size of tree.

size_t height( const treenode* n );
   // Returns the height of the tree starting at n.

size_t log_base2( size_t s );

class set
{
   treenode* tr;

public: 
   set( ) 
      : tr( nullptr ) 
   { } 

   set( const set& s ) 
      : tr( nullptr ) 
   {
      writecopy( &tr, s. tr );
   }

   set& operator = ( const set& s ) 
   {
      if( tr != s. tr )
      {
         deallocate( tr );
         writecopy( &tr, s. tr );
      }
      return *this;
   }

   ~set( ) { deallocate( tr ); }


   set( std::initializer_list< int > init )
      : tr( nullptr ) 
   {
      for( int i : init ) 
         insert(i);
   } 
  
   int top( ) const { return tr -> val; }
      // Return element on top. The tree must be non empty.
 
   bool contains( int i ) const;

   bool insert( int i );
      // Returns true if the insertion took place.

   bool remove( int i );
      // Returns true if i was present. 

   size_t remove( const set& s );
      // Returns number of elements removed. (that were present).
 
   size_t size( ) const { return ::size( tr ); }
   size_t height( ) const { return ::height( tr ); }

   bool isempty( ); 

   void clear( ); 

   void checksorted( ) const;
      // Check if the tree is sorted, and throw an exception
      // if it is not. Call this function often to check your
      // trees. 

   std::ostream& print( size_t indent, std::ostream& out ) const;
};


inline std::ostream& operator << ( std::ostream& out, const set& s )
{
   return s. print( 0, out );
}

bool subset( const set& s1, const set& s2 );

inline bool equal( const set& s1, const set& s2 )
{
   return subset( s1, s2 ) && subset( s2, s1 );
}

#endif

