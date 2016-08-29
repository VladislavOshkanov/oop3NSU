#include <iostream>
#include <string>

class Printable {
public:
  Printable (){};
  virtual void print(std::ostream & out) = 0;
  void doSomething(){
  }
  friend std::ostream & operator << (std::ostream & out, Printable& shape){
    shape.print(out);
    return out;
  }
  ~Printable (){};
};

class Named : public Printable{
public:
  Named (std::string const  name) : Printable(){
    this->_name = name;
  };
  void print (std::ostream & out){
    out << this->getName();
  }


  std::string const & getName() {
    return _name;
  }
private:
  std::string _name;

};
