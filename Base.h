#include <iostream>
#include <string>

class Printable {
public:
  Printable (){};

  virtual void print( std::ostream & out ) = 0;

  friend std::ostream & operator << ( std::ostream & out, Printable & shape ){
    shape.print( out );
    return out;
  }
  
  ~Printable (){};
};

class Named : virtual public Printable{
public:
  Named ( std::string const name ) : Printable() {
    this->_name = name;
  };

  void print ( std::ostream & out ) {
    out << this->getName();
  }

  std::string const & getName() {
    return _name;
  }

protected:
  std::string _name;

};

class Shape : virtual public Printable {
public:
  Shape () : Printable() {
    _quantity++;
  };

  virtual ~Shape() {
    _quantity--;

  }

  static int getCount() {
    return _quantity;
  }

  virtual void print ( std::ostream & out ) = 0;

protected:
  static int _quantity;

};

int Shape::_quantity = 0;
