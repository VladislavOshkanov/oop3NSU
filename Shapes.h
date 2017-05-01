#include "Base.h"
#include "Container.h"
#include <cmath>


class Point : public Shape, public Named {
public:
  Point () : Shape (), Named( "" ) {}
  Point ( std::string const & name, float x, float y )
    : Shape(), Named ( name ), _x( x ), _y ( y ) {}

  Point ( const Point & obj )
    : Shape(), Named( obj._name ), _x ( obj._x ), _y ( obj._y ) {
#ifdef DEBUG
      std::cout << "\nCopy constructor\n";
#endif

  }

  std::string print() const {
    std::string const out = "Point: \n \tName: " + this->getName() + "\n" +
      "\tCoordinates:(" + std::to_string( _x) + "," + std::to_string(_y) + ") \n";
    return out;
  }

  float getX() const{
    return _x;
  }

  float getY() const{
    return _y;
  }

  ~Point () {

#ifdef DEBUG
    std::cout << "destructor of point" << '\n';
  #endif

  };

private:
  float _x, _y;
};

class Circle : public Shape, public Named {
public:
  Circle ( std::string const & name, Point & center, float radius )
    : Shape(), Named ( name ), _center ( center ), _radius( radius ) {}

  std::string print () const {
    std::string const out =  "Circle:\n center:" +
    _center.print() +
    "\tradius:" + std::to_string( _radius ) + "\n" +
    "\tspace:" + std::to_string( _radius * _radius * M_PI ) + "\n";
    return out;
  }

  ~Circle () {

#ifdef DEBUG
    std::cout << "destructor of circle" << '\n';
#endif

  };
private:
  Point  _center;
  float   _radius;
};

class RectBase : public Shape, public Named {
public:
  RectBase ( std::string const & name, Point & ul, Point & dr, bool isSquare )
    : Shape(), Named ( name ), _ul( ul ), _dr ( dr ), _isSquare ( isSquare ) {

    if ( ul.getX() > dr.getX() || ul.getY() < dr.getY()) throw "Inverted rectangle or square";
  };

  float calculateSpace() {
    return ( _ul.getY() - _dr.getY() ) * ( _dr.getX() - _dr.getY() );
  }

  ~RectBase () {

#ifdef DEBUG
    std::cout << "destructor of rect" << '\n';
#endif

  };

  std::string print() const  {
      std::string figureType;
      figureType = ( _isSquare == true ) ? "Square" : "Rectangle";
      std::string const out = figureType + ":\n\tUp left:" +
      _ul.print() + "\tDown right:" + _dr.print ();
      return out;
  }

private:
  Point _ul, _dr;  //ul - up left, dr - down right
  bool _isSquare;
};



class Rect :  public RectBase {
public:
  Rect ( std::string const name, Point & ul, Point & dr ) : RectBase ( name, ul, dr, false ) {};
};

class Square :  public RectBase {
public:
  Square ( std::string const & name, Point & ul, Point & dr ) : RectBase ( name, ul, dr, true ) {
    if ( ul.getY() - dr.getY() != dr.getX() - ul.getX() ) throw "Is not square";
  };
};





class Polyline : public Shape, public Named {
public:
  Polyline ( std::string const & name ) : Shape(), Named ( name ) {}

  std::string print () const {
    std::string figureType = "Polyline";
    std::string const out = figureType + ":\n" +
    "\tLength:" + std::to_string(calculateLength()) + "\n";
    return out;
  }

  void AddPoint ( Point  & point ) {
    points.pushLast( point );
  }

  Point * getFirstPoint() {
    return points.getFirst();
  }

  float calculateLength() const {
    int size = points.getSize();
    float length = 0;
    Container<Point> :: iterator iter = points.begin();
    Container<Point> :: iterator end = points.end();
    for ( ; !( iter == end );  ) {
      Point a = *iter;
      ++ iter;
      if (!(iter == end)){
        Point b = *iter;
        length += calculateDistance ( & a, & b );
      }
    }

    return length;
  }

  virtual ~Polyline() {};
  Container<Point> points;

protected:

  float calculateDistance( Point const * a, Point const * b) const {
    float diff_x = a->getX() - b->getX();
    float diff_y = a->getY() - b->getY();
    return pow( ( pow( diff_x, 2 ) + pow( diff_y, 2 ) ), 0.5 );
  }

};

class Polygon: public Polyline{
public:
   Polygon ( std::string const & name ) : Polyline ( name ) {};
   std::string print () const {
     std::string figureType = "Polygon";
     std::string const out = figureType + ":\n" +
     "\tLength:" + std::to_string(calculateLength()) + "\n";
     return out;
   }
   float calculateLength () const {
     Point * a = points.getFirst();
     Point * b = points.getLast();
     float length = calculateDistance ( a, b );
     return Polyline::calculateLength() + length;
   }

};
