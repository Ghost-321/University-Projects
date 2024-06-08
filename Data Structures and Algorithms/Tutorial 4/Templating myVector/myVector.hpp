#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <initializer_list>

template <typename T>
class MyVector {
 private:
  T* arrayPointer_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;

 public:
  // Default Constructor
  MyVector();

  // Construct a vector of size n where all entries are 0
  explicit MyVector(int n);

  // Copy Constructor
  MyVector(const MyVector<T>&);

  // Construct a vector from an initializer list
  MyVector(std::initializer_list<T>);

  // Destructor
  ~MyVector();

  // Copy Assignment Operator
  MyVector<T>& operator=(MyVector<T>);

  void push_back(T);
  void pop_back();
  T& back();
  bool empty();

  // Getter for the size
  int size() const;

  // Getter for the capacity
  int capacity() const;

  // Indexing operator.  Return by reference so entry can be modified.
  T& operator[](int);
  // const version so we can access (but not modify) an entry in a
  // const MyVector
  const T& operator[](int) const;

};
#endif      // MY_VECTOR_HPP
