
#include "set.h"


void print( std::ostream& out, const treenode* n, size_t indent )
{

   for( size_t i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const int* lowerbound, const int* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> val )
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && n -> val >= *upperbound )
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checkbetween( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
} 


void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}


void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
   *to = nullptr;
}


void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}

size_t log_base2 (size_t s) {
	if (s == 0) return 0;
	size_t ans = 0;
	while (s > 0) {
		s /= 2;
		if (s == 0) break;
		ans ++;
	}
	return ans;
}

const treenode* find (const treenode* n, int i) {
	if (n == nullptr) return nullptr;
	if (n -> val == i) return n;
	if (n -> val < i) 
		return find (n -> right, i); 
	else 
		return find (n -> left, i);
}

treenode** find( treenode** n, int i ) {
	if (*n == nullptr) return n;
	if ((*n) -> val == i) return n;
	if ((*n) -> val < i)
		return find (&( (*n) -> right), i);
	else
		return find (&( (*n) -> left), i);	
}

bool set::insert (int i) {
	treenode** cur = find (&tr, i);
	if ((*cur) == nullptr) {
		*cur = new treenode (i);
		return true;
	} else 
		return false;
}

bool set::contains (int i) const {
	if (find (tr, i) == nullptr) 
		return false;
	else 
		return true;
}

treenode* removerightmost (treenode** from) {
	treenode** cur = &((*from) -> left);
	while ((*cur) -> right != nullptr) 
		cur = &((*cur) -> right);
	(*from) -> val = (*cur) -> val;
	treenode* bye = (*cur);
	if ((*cur) -> left == nullptr)
		(*cur) = nullptr;
	else 
		(*cur) = (*cur) -> left;
	delete bye;
	return *cur;
} 

bool set::remove (int i) {
	treenode** cur = find (&tr, i);
	if ((*cur) == nullptr) return false;
	if ((*cur) -> left == nullptr && (*cur) -> right == nullptr) {
		delete (*cur);
		*cur = nullptr;
	} 
	else if ((*cur) -> left != nullptr && (*cur) -> right == nullptr) {
		treenode *old = (*cur);                                 
		*cur = (*cur) -> left;
		delete old;
	}
	else if ((*cur) -> right != nullptr && (*cur) -> left == nullptr) {
		treenode *old = (*cur);
		(*cur) = (*cur) -> right;
		delete old;
	} 
	else {
		treenode* rightmost = removerightmost (cur);
	}
	return true;
}

void set::clear () {
	deallocate (tr);
	tr = nullptr;		
}

size_t size (const treenode* n) {
	if (n == nullptr) return 0;
	return (size (n -> left) + size (n -> right) + 1);
} 

bool set::isempty () {
	if (tr == nullptr) 
		return true;
	else
		return false;
}

size_t height (const treenode* n) {
	if (n == nullptr) return 0;
	size_t hl = height (n -> left) + 1;
	size_t hr = height (n -> right) + 1;
	if (hl > hr) return hl;
	return hr;
}

std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}


