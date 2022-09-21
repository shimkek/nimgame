
#ifndef STATE_
#define STATE_  1

#include <vector>
#include <iostream>

#include "move.h"

struct state 
{

   std::vector< unsigned int > sticks; 

   state( std::initializer_list< unsigned int > init ); 
   state( unsigned int i1, unsigned int i2 );

   unsigned int sum( ) const; 

   unsigned int nimber() const;
   
   optional_move randommove( ) const;

   optional_move makenimberzero( ) const;

   optional_move removelastmorethantwo( ) const;

   void make( move m ); 

   optional_move usermove( std::ostream& out, std::istream& in ) const;

   void print( std::ostream& out ) const;
};


inline std::ostream& operator << ( std::ostream& out, const state& st )
{
   st. print( out );
   return out;
}

#endif

