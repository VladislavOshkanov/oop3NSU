#include "Base.h"
#include "Container.h"
#include <cmath>


class Point : public Shape, public Named {
public:
  Point () : Shape (), Named( "" ) {};
  Point ( std::string const name, float x, float y ) : Shape(), Named ( name ) {
    _x = x;
    _y = y;
  }
  Point ( const Point & obj ): Shape(), Named( obj._name ) {
    _x = obj._x;
    _y = obj._y;

#ifdef DEBUG
      std::cout << "\nCopy constructor\n";
#endif

  }

  void print( std::ostream & out ) {
    out << "Point: \n \tName: " << this->getName() << "\n" << "\tCoordinates:(" << _x << "," << _y << ") \n";
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
  Circle ( std::string const name, Point * x, float radius ) : Shape(), Named ( name ) {
    _center = new Point ( * x );
    _radius = radius;
  }

  void print( std::ostream & out ) {
    out << "Circle:\n center:";
    _center->print(out);
    out << "\tradius:" << _radius << "\n";
    out << "\tspace:" << _radius * _radius * M_PI << "\n";
  }

  ~Circle () {
    delete  _center;

#ifdef DEBUG
    std::cout << "destructor of circle" << '\n';
#endif

  };
private:
  Point * _center;
  float   _radius;
};

class RectBase : public Shape, public Named {
public:
  RectBase ( std::string const name, Point * ul, Point * dr, bool isSquare ) : Shape(), Named ( name ) {
    if ( ul->getX() > dr ->getX() || ul->getY() < dr -> getY()) throw "Inverted rectangle or square";
    _ul = new Point( * ul );
    _dr = new Point( * dr );
    _isSquare = isSquare;
  };

  float calculateSpace() {
    return ( _ul->getY() - _dr->getY() ) * ( _dr->getX() - _dr->getY() );
  }

  ~RectBase () {

#ifdef DEBUG
    std::cout << "destructor of rect" << '\n';
#endif

    delete _ul;
    delete _dr;
  };

  void print( std::ostream & out ) {
      std::string figureType;
      figureType = ( _isSquare == true ) ? "Square" : "Rectangle";
      out << figureType << ":\n\tUp left:";
      _ul -> print( out );
      out << "\tDown right:";
      _dr -> print ( out );
  }

private:
  Point * _ul, * _dr;  //ul - up left, dr - down right
  bool _isSquare;
};



class Rect :  public RectBase {
public:
  Rect ( std::string const name, Point * ul, Point * dr ) : RectBase ( name, ul, dr, false ) {};
};

class Square :  public RectBase {
public:
  Square ( std::string const name, Point * ul, Point * dr ) : RectBase ( name, ul, dr, true ) {
    if ( ul->getY() - dr->getY() != dr->getX() - ul->getX() ) throw "Is not square";
  };
};





class PolylineBase : public Shape, public Named {
public:
  PolylineBase ( std::string const name, bool isClosed ) : Shape(), Named ( name ) {
    _isClosed = isClosed;
  };

  void print ( std::ostream & out ) {
    std::string figureType;
    figureType = (_isClosed == true) ? "Polygon" : "Polyline";
    out << figureType << std::endl;
    out << "\tLength:" << calculateLength() << std::endl;
  }

  void AddPoint ( Point const & point ) {
    points.pushLast( point );
  }

  Point getFirstPoint() {
    return points.getFirst();
  }

  float calculateLength() {
    int size = points.getSize();
    float length = 0;

    for ( int i = 0; i <  size - 1; i++ ) {
      Point a = points.getNth(i);
      Point b = points.getNth(i+1);
      length += calculateDistance ( a, b );
    }

    if ( _isClosed == true ) {
      Point a = points.getFirst();
      Point b = points.getLast();
      length += calculateDistance ( a, b );
    }

    return length;
  }

  virtual ~PolylineBase() {};

private:

  float calculateDistance( Point const& a, Point const& b) {
    float diff_x = a.getX() - b.getX();
    float diff_y = a.getY() - b.getY();
    return pow( ( pow( diff_x, 2 ) + pow( diff_y, 2 ) ), 0.5 );
  }

  Container<Point> points;
  bool _isClosed;
};

class Polyline: public PolylineBase{
public:
   Polyline ( std::string const name ) : PolylineBase ( name, false ) {};
};

class Polygon: public PolylineBase{
public:
   Polygon ( std::string const name ) : PolylineBase ( name, true ) {};
};
