#include "myInteger.hpp"

// default constructor
myInteger::myInteger() {}

// constructor from an int
myInteger::myInteger(int input) : value {input} {}

// copy constructor
myInteger::myInteger(const myInteger& x) : value {x.value} {}

// assignment operator
myInteger& myInteger::operator=(const myInteger& x) {
  value = x.value;
  return *this;
}

// destructor
myInteger::~myInteger() {}

bool operator==(const myInteger& x, const myInteger& y) {
    return x.value == y.value;
}

bool operator<(const myInteger& x, const myInteger& y) {
    return x.value < y.value;
}
