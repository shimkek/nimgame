
#include "state.h"
#include <string>

state::state( std::initializer_list< unsigned int > init ) {
   for (auto stickNum : init) {
      sticks.push_back(stickNum);
   }
}

state::state( unsigned int i1, unsigned int i2 ) {
   for(size_t i = i1; i <= i2; i++) {
      sticks.push_back(i);
   }
}

unsigned int state::sum( ) const {
   int counter = 0;
   for(int i = 0; i < sticks.size(); i++) {
      counter+= sticks[i];
   }
   return counter;
}

optional_move state::removelastmorethantwo() const {
   int bigrowsnum = 0, onestickrownum = 0, bigrowindex;
   for(int i = 0; i < sticks.size(); i++) {
      if(sticks[i] > 1) 
         bigrowsnum++;
   }

   if(bigrowsnum != 1) {
      return optional_move();
   }

   for(int i = 0; i < sticks.size(); i++) {
      if(sticks[i] == 1) 
         onestickrownum++;
      if(sticks[i] > 1) 
         bigrowindex = i;
   }
   //if even
   if((onestickrownum % 2) == 0){
      move m(bigrowindex, 1);
      return optional_move(m);
   } else {
      move m(bigrowindex, 0);
      return optional_move(m);
   }
}

unsigned int state::nimber() const {
   unsigned int sticksrow = sticks[0];
   for(size_t i = 1; i < sticks.size(); i++) { 
      sticksrow = sticksrow ^ sticks[i];
   }
   return sticksrow;
}

optional_move state::makenimberzero() const {
   int nimnum = nimber();
   if(nimnum == 0) {
      return optional_move();
   }
   for(size_t i = 0; i < sticks.size(); i++) { 
      int tempnimber = nimnum ^ sticks[i];
      if(tempnimber < sticks[i]) {
         move m(i, tempnimber);
         return optional_move(m);
      }
   }
   std::__throw_logic_error("cannot make nimber zero");
   return optional_move();
}

optional_move state::randommove( ) const  {
   if(sum()) {
      unsigned int row, remaining;
      row = rand() % sticks.size();
      while( sticks[row] == 0) {
         row = rand() % sticks.size();
      };
      remaining = rand() % sticks[row];
      move valid_move(row, remaining);
      optional_move m(valid_move);
      return m;
   } else {
      optional_move m;
      return m;
   }
}

void state::make( move m ) {
   if(m.remaining < sticks[m.row] && m.row < sticks.size()) {
      sticks[m.row] = m.remaining;
   } else {
      std::abort();
   }
}

void state::print( std::ostream& out ) const {
   for(size_t i = 0; i < sticks.size(); i++) {
      out << i+1 << "   :";
      for(size_t z = 0; z < sticks[i]; z++) {
         out << " 1"; 
      }
      out << std::endl;
   }
}

optional_move state::usermove( std::ostream& out, std::istream& in ) const
{

   if( sum( ))
   {
      while( true )
      {
         std::string inp;
         try
         {
            out << "row? "; out. flush( );
            in >> inp; 

            unsigned int row = std::stoul( inp ); inp. clear( );

            if( row > 0 && row <= sticks. size( )) 
            {
               unsigned int row1 = row - 1;
               if( sticks[ row1 ] )
               {
                  out << "how many remaining? "; out. flush( );
                  in >> inp; 
                  unsigned int remain = std::stoul( inp ); inp. clear( ); 

                  if( remain < sticks[ row1 ] )
                     return move( row1, remain );
                  else
                  {
                     out << "having " << remain 
                         << " remaining is not possible, "
                         << "you have to remove at least one stick\n";
                  }
               }
               else 
               {
                  out << "row " << row << " is already empty\n";
               }
            }
            else
            {
               out << "row " << row << " is not a valid row, ";
               out << "rows are between 1 and " << sticks. size( ) << "\n";
            }
            
         }
         catch( std::invalid_argument& inv )
         {
            out << inp << " is not a number\n";
         }
         catch( std::out_of_range& r )
         {
            out << inp << " is too big\n";
         }
      }
   }
   else
      return optional_move( ); 
}

