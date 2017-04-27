#include <cstddef>
#include <iostream>
using namespace std;

const int DEBUG = 0;

template<class T> class Node {
public:

  Node() {}
  Node ( T el ) {
    element = el;
    next = 0;
  }
  T element;
  Node * next;
};

template<class T> class Container {
public:
  Container () {
    _first = 0;
    _last = 0;
    size = 0;
  }

  virtual ~Container () {
    while ( size != 0 ) {
      deleteFirst();
    }

#ifdef DEBUG
    std::cout << "destructor of Container" << '\n';
#endif

  }

  void pushFirst( T element ) {
    if ((_first == 0)) {
      Node<T> * node = new Node<T>( element );
      _first = node;
      _last = node;
    }
    else {
      Node<T> * node = new Node<T>( element );
      node->next = _first;
      _first = node;
    }
    size++;
  }

  void pushLast ( T element ) {
    if ((_first == 0)) {
      Node<T> * node = new Node<T>( element );
      _first = node;
      _last = node;
    }
    else{
        Node<T> * node = new Node<T>( element );
        _last->next = node;
        _last = node;
    }
    size++;
  }

  void deleteFirst() {
    if ( _first == 0 ) throw "Container is empty";
    if ( _first == _last ) {
      delete _first;
      _first = 0;
      _last = 0;
    }
    else{
      Node<T> * temp = _first;
      _first = _first->next;
      delete temp;
    }
    size--;
  }

  void deleteLast() {
    if ( _first == 0 ) throw "Container is empty";
    if ( _first == _last ) {
      delete _first;
      _first = 0;
      _last = 0;
    }
    else {
      Node<T> * temp = _first;
      while ( temp->next != _last ) {
        temp = temp->next;
      }
      delete _last;
      _last = temp;
      _last->next = 0;
    }
    size--;
  }

  T getFirst() {
    if ( _first == 0 ) throw "Container is empty";
    return _first->element;
  }

  T getLast() {
    if ( _first == 0 ) throw "Container is empty";
    return _last->element;
  }

  T getNth ( int n ) {
    if ( size < n ) throw "Container doesn't have so many elements";
    Node<T> * p = _first;
    for ( int i = 0; i < n; i++ ) {
      p = p->next;
    }
    return p->element;
  }

  int getSize() {
    return size;
  }

  bool isEmpty() {
    if ( size == 0 ) return true;
      else return false;
  }

  void empty() {
    while ( size != 0 ) {
      deleteFirst();
    }
  }

  void print() {
    if ( _first != 0 ) {
      Node<T> * temp;
      temp = _first;
      while ( temp != 0 ) {
        cout << temp->element << endl;
        temp = temp->next;
      }
    }
  }

private:
  int size;
  Node<T> * _first, * _last;
};
