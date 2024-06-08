#ifndef MY_INTEGER_HPP_
#define MY_INTEGER_HPP_

class myInteger {
 private:
  int value {};

 public:
  // default constructor
  myInteger();

  // constructor taking an integer
  // explicit means we don't allow myInteger x = 3
  // the constructor has to be explicitly called
  explicit myInteger(int);

  // copy constructor
  // create a copy constructor with the same value as another myInteger
  myInteger(const myInteger&);

  // assignment operator
  // this enables myInteger x {3}; myInteger y {5}; x = y;
  myInteger& operator=(const myInteger&);

  // destructor
  ~myInteger();

  // determine if two myIntegers are equal
  friend bool operator==(const myInteger&, const myInteger&);

  // determine if one myInteger is less than another
  friend bool operator<(const myInteger&, const myInteger&);
};

#endif  // MY_INTEGER_HPP_
