#include <ctime>
#include "Shapes.h"
#include <cstdlib>
enum{
  POINT,
  CIRCLE,
  RECT,
  SQUARE,
  POLYLINE,
  POLYGON
};

Point * makePoint () {
  int x = rand() % 100;
  int y = rand() % 100;
  Point * point = new Point ( "noname", x, y );
  return point;
}

Shape * newFigure ( int type ) {
  Shape * shape = 0;
  switch ( type ) {
    case POINT:{
      shape = makePoint();
      break;
    }

    case CIRCLE: {
      int radius = rand() % 100;
      Point * center = makePoint();
      shape = new Circle( "noname",  * center, radius );
      delete center;
      break;
    }

    case RECT: {
      int side1 = rand() % 100;
      int side2 = rand() % 100;
      Point * ul = makePoint();
      Point * dr = new Point ( "noname", ul->getX() + side1, ul->getY() - side2 );
      shape = new Rect ( "noname", * ul, * dr );

      delete ul;
      delete dr;
      break;
    }

    case SQUARE: {
      int side = rand() % 100;
      Point * ul = makePoint();
      Point * dr = new Point ( "noname", ul->getX() + side, ul->getY() - side );
      shape = new Square( "noname", *ul, *dr );
      delete ul;
      delete dr;
      break;
    }

    case POLYLINE: {
      int n =  100;
      Polyline * pol = new Polyline( "noname" );
      for (int i = 0; i < n; i++) {
        Point * p = makePoint();
        pol -> AddPoint ( * p );
        delete p;
      }
      shape = pol;
      break;
    }

    case POLYGON: {
      int n =  100;
      Polyline * pol = new Polyline( "noname" );
      for ( int i = 0; i < n; i++ ) {
        Point * p = makePoint();
        pol->AddPoint ( * p );
        delete p;
      }
      shape = pol;
      break;
    }
  }
  return shape;
}
