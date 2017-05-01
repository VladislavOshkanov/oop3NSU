#include <iostream>
#include <string>

class Printable {
public:

  virtual std::string print() const = 0;

  friend std::ostream & operator << ( std::ostream & out, Printable & printable ){
    printable.print();
    return out;
  }

  virtual ~Printable (){};
};

class Named : virtual public Printable {
public:
  Named ( std::string const name ) : Printable() {
    this->_name = name;
  };

  void print ( std::ostream & out ) {
    out << this->getName();
  }

  std::string const & getName() const {
    return _name;
  }

protected:
  std::string _name;

};

class Shape : virtual public Printable {
public:
  Shape () {
    _quantity++;
  };

  virtual ~Shape() {
    _quantity--;

  }

  static int getCount() {
    return _quantity;
  }

  virtual std::string print() const = 0;


protected:
  static size_t _quantity;

};

size_t Shape::_quantity = 0;
