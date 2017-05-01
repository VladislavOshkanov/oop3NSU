#include "Factory.h"

int main() {
 srand ( time ( 0 ) );
 Container <Shape*> figures;
 for ( int i = 0; i < 100; i++ ) {
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

 Container<Shape *> :: iterator iter = figures.begin();
 Container<Shape *> :: iterator end = figures.end();
 for ( ; !( iter == end );  ) {
   Shape * sh = *iter;
   std::cout << sh->print();
   delete sh;
   ++iter;
 }

 std::cout << "Quantity of figures after:" << Shape::getCount() << '\n';

}
