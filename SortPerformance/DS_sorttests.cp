
#include <iostream>
#include <vector>
#include <algorithm>

#include "timer.h" 
#include "timetable.h"

// Print a vector of integers:

std::ostream& operator << ( std::ostream& out, const std::vector< int > & vect )
{
   for( size_t i = 0; i != vect. size( ); ++ i )
      out << i << " : " << vect[i] << "\n";

   return out;
}


// Create a vector of size k filled with random ints:

std::vector< int > randomvector( size_t k )
{
   std::vector< int > res;
   for( size_t i = 0; i != k; ++ i )
      res. push_back( rand( ));
   return res;
}


void bubble_sort( std::vector< int > & vect )
{
   if( vect. size( ) < 2 ) return;
      // Every shorter vector is sorted.

   bool sorted = false;
   while( !sorted ) 
   {
      sorted = true; 
      for( size_t i = 0; i + 1 != vect. size( ); ++ i )
      {
         if( vect[i] > vect[i+1] )
         {
            std::swap( vect[i], vect[i+1] );
            sorted = false;
         }
      }
   }
}

void restore_heap( std::vector< int > & vect, size_t s )
{
   size_t p = 0;
   while( 2 * p + 1 < s )
   {
      if( 2 * p + 2 == s )
      {
         if( vect[p] < vect[ 2 * p + 1 ] )
            std::swap( vect[p], vect[ 2 * p + 1 ] );
         return; 
      }
      else
      {
         if( vect[p] < vect[ 2 * p + 1 ] || vect[p] < vect[ 2 * p + 2 ] )
         {
            if( vect[ 2 * p + 1 ] < vect[ 2 * p + 2 ] )
            {
               std::swap( vect[p], vect[ 2 * p + 2 ] );
               p = 2 * p + 2;
            }
            else
            { 
               std::swap( vect[p], vect[ 2 * p + 1 ] );
               p = 2 * p + 1;
            }
         }
         else
            return; 
      }
   }
}


void heap_sort( std::vector< int > & vect )
{
   if( vect. size( ) < 2 ) return;
      // Every shorter vector is sorted.

   // In the first pass, we establish the heap condition:

   for( size_t i = 1; i != vect. size( ); ++ i )
   {
      for( size_t p = i; p != 0; p = ( p - 1 ) / 2 )
      {
         if( vect[p] > vect[ ( p-1 ) / 2 ] )
            std::swap( vect[p], vect[ ( p - 1 ) / 2 ] );
      }      
   }

   size_t i = vect. size( );
   while(i)
   {
      --i;
      std::swap( vect[0], vect[i] );
     
      // And we restore heap condition between 0 and i: 

      restore_heap( vect, i ); 
   }

}


void quick_sort( std::vector< int > & vect )
{
   std::sort( vect. begin( ), vect. end( ));   
}


std::list< int > :: iterator 
findmin( std::list< int > :: iterator p1,
         std::list< int > :: iterator p2 )
{
   if( p1 == p2 ) 
      return p2;

   auto min = p1 ++ ;
   while( p1 != p2 )
   {
      if( *p1 < *min )
         min = p1;
      ++ p1;
   }

   return min; 
}


void insertion_sort( std::list< int > & lst ) 
{
   for( auto p = lst. begin( ); p != lst. end( ); ++ p ) 
   {
      auto m = findmin( p, lst. end( )); 
      std::swap( *p, *m ); 
   }
}


int main (int argc, char* argv[]) {

  timetable alg1 ("Bubble_sort");
  timetable alg2 ("Heap_sort");
  timetable alg3 ("Quick_sort");
  timetable alg4 ("Insertion_sort");
  
  for (size_t sz = 1000;sz < 100000;sz *= 2) {
    std::vector < int > test1 = randomvector (sz);
    auto test2 = test1;
    auto test3 = test1;
    std::list < int > test4 (test1.begin (), test1.end ());

    timer cur_t;
    bubble_sort (test1);
    alg1.insert (sz, cur_t.time ());
    cur_t.clear ();
    heap_sort (test2);
    alg2.insert (sz, cur_t.time ());
    cur_t.clear ();
    quick_sort (test3);
    alg3.insert (sz, cur_t.time ());
    cur_t.clear ();
    insertion_sort (test4);
    alg4.insert (sz, cur_t.time ());
  }
  std::cout << alg1 << std::endl;
  std::cout << alg2 << std::endl;
  std::cout << alg3 << std::endl;
  std::cout << alg4 << std::endl;
  /*
  Answer question 2 in the comments:
    Is there a difference between compilation with optimization 
    on and compilation with optimization off?
  
  Question 2: Yes, of course, there is difference between them!
    I have measured running time for every algorithm. To give more details:
    Code without optimization works 10.11230 slower than the same code without optimization
   
   
  Answer question 3 in the comments:  
    Establish which sorting algorithms have O(n^2) performance, and which ones have O(n. log(n)) performance.  
    
  Question 3: 
    Bubble Sort and Insertion sort algorithms are O (n^2) algorithms
    Heap Sort and Quick sort algorithms are O (n.logn) algorithms
  

  Answer question 4 in the comments:
    Among those with O(n^2), which one is faster?
  
  Question 4:
    By the theory, insertion sort does n * (n - 1) / 2 operations, while bubble sort
    does n * (n - 1) operations in worst cases. So, according to theory, insertion sort
    is faster than bubble sort. By the running time of this code: 
    In average, Insertion Sort algorithm worked 9.2393 seconds, while Bubble Sort worked
    10.7730 seconds.
    So, Insertion Sort is faster than Bubble Sort.
  
  Answer question 4 in the comments:
    Among those with O(n^2), which one is faster?
  
  Question 5: 
    By the theory, quick sort does no more than n.logn operations, while heap sort
    does (logn) operations for every insertion, and initially builds heap tree for n.logn time. 
    By the running time of this code: In average, Quick Sort algorithm worked 0.0033 seconds, 
    while Heap Sort worked 0.0092 seconds.
    So, Quick sort is faster than Heap Sort.

  */
  std::cout << "have a nice day\n";
}
 