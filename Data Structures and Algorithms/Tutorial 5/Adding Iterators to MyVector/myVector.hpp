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

  // Construct a vector of size n where all entries are
  // the default value of T
  explicit MyVector(int n);

  // Construct a vector from an initializer list
  MyVector(std::initializer_list<T>);

  // Copy Constructor
  MyVector(const MyVector<T>&);

  // Copy Assignment Operator
  MyVector<T>& operator=(MyVector<T>);

  // Destructor
  ~MyVector();

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
  const T& operator[](int) const;

  class Iterator {
   private:
    T* ptr {};
   public:
    explicit Iterator(T* input = nullptr);

    T& operator*();

    Iterator& operator++();

    Iterator& operator--();

    friend bool operator==(const Iterator& x, const Iterator& y) {
      return x.ptr == y.ptr;
    }

    friend bool operator!=(const Iterator& x, const Iterator& y) {
      return not (x == y);
    }
  };

  Iterator begin() const;

  Iterator end() const;
};
#endif      // MY_VECTOR_HPP
