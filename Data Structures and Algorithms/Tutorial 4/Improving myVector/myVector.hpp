#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <initializer_list>

class MyVector {
 private:
  int* arrayPointer_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;

 public:
  // Default Constructor
  MyVector();

  // Construct a vector of size n where all entries are 0
  explicit MyVector(int n);

  // Construct a vector from an initializer list
  MyVector(std::initializer_list<int> vals);

  // Copy Constructor: initialize a MyVector
  // from to be a copy of an existing MyVector
  //*** Implement this in the cpp file 
  MyVector(const MyVector&);

  // Destructor
  ~MyVector();

  // Copy assignment operator
  //*** Implement this in the cpp file 
  MyVector& operator=(MyVector);

  void push_back(int);
  void pop_back();
  int back();
  bool empty();

  // Getter for the size
  int size() const;

  // Getter for the capacity
  int capacity() const;

  // Check if two MyVectors are equal
  bool operator==(const MyVector&) const;

  // Indexing operator.  Return by reference so entry can be modified.
  int& operator[](int);
  // We need the next version when we 
  // want to access the ith element 
  // of a const MyVector, 
  // as in our usual print function
  int operator[](int i) const;
};
#endif      // MY_VECTOR_HPP
