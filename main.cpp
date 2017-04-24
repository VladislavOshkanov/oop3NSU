#include "Factory.h"

int main() {
 srand ( time ( 0 ) );
 Container <Shape*> figures;
 for ( int i = 0; i < 50; i++ ) {
   int type = rand() % 6;
   Shape * sh;
   try{
     sh = newFigure ( type );
     figures.pushLast( sh );
   }
   catch ( char const * str ) {
      std::cout << str << std::endl;
   }
 }

 std::cout << "Quantity of figures before:" << Shape::getCount() << '\n';

 for (int i = 0; i < figures.getSize(); i++) {
   Shape * sh = figures.getNth ( i );
   sh->print( std::cout );
   delete sh;
 }
 
 std::cout << "Quantity of figures after:" << Shape::getCount() << '\n';

}

