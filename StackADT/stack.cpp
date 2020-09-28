
#include "stack.h"

// Use this method for all your reallocations:

void stack::ensure_capacity( size_t c ) 
{
   if( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if( c < 2 * current_capacity )
         c = 2 * current_capacity;

      double* newdata = new double[ c ];
      for( size_t i = 0; i < current_size; ++ i )
          newdata[i] = data[i];

      current_capacity = c;
      delete[] data;
      data = newdata;
   }
}

stack::stack () :
    data (new double [5]),      
    current_size (0),
    current_capacity (5)
{
}

stack::stack (const stack &s) : 
    current_size (s.current_size),
    current_capacity (s.current_capacity),
    data (new double [s.current_capacity])
{
    for (size_t it = 0;it < s.current_size;it ++) 
        data[it] = s.data[it];
}

stack::~stack () {
    delete [] data;         
}

const stack& stack::operator = ( const stack& s ) {
    if (s.current_size != current_size) {
        delete[] data;
        data = new double[s.current_capacity];
        current_capacity = s.current_capacity;
    }         
    current_size = s.current_size;
    for (size_t it = 0;it < s.current_size;it ++) 
        data[it] = s.data[it];
    return *this;
}
 
stack::stack (std::initializer_list < double > init_values) :
    current_size (init_values.size ()),
    current_capacity (init_values.size ()),
    data (new double [init_values.size()])   
{
    size_t len = 0;
    for (auto it : init_values)
        data[len ++] = it;                            
}

void stack::push (double num) {
    if (current_size == current_capacity)
        ensure_capacity (current_size + 1);
    data[current_size] = num;    
    current_size ++;
}

void stack::pop () {
    if (current_size == 0) 
        throw std::runtime_error ("Stack is empty, can not pop!");
    current_size --;
}

void stack::clear () {
    current_size = 0;
}

void stack::reset (size_t new_size) {   
    if (new_size > current_size) 
        throw std::runtime_error ("Size can not be greater than current_size!");     
    current_size = new_size;
}

double stack::peek () const {
    if (current_size == 0) 
        throw std::runtime_error ("Stack is empty, can not access peek!");
    return data[current_size - 1];
}

size_t stack::size () const {
    return current_size;
}

bool stack::empty () const {
    return (current_size == 0 ? 1 : 0);
}

std::ostream& operator << (std::ostream& out, const stack &s) {
    out << "[";
    for (int it = 0;it < s.current_size;it ++) {
        out << s.data[it];   
        if (it != s.current_size - 1) 
            out << ", ";
    }
    out << "]";
    return out;
}



