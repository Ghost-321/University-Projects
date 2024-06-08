#include <iostream>
#include <initializer_list>
#include "myVector.hpp"

// default constructor
MyVector::MyVector() {}

// construct a zero-initialized vector of size n
MyVector::MyVector(int n) {
  if (n < 0) {
    std::cout << "Error, size should be non-negative\n";  
    return;
  }
  arrayPointer_ = new int[n] {}; 
  size_ = capacity_ = n;
}

// Constructor from initializer list
MyVector::MyVector(std::initializer_list<int> vals) {
  size_ = capacity_ = vals.size();
  arrayPointer_ = new int[size_]; 
  int i = 0;
  for (int x : vals) {
    arrayPointer_[i++] = x;
  }
}

// Copy Constructor
// For you to implement
MyVector::MyVector(const MyVector& other) 
    : arrayPointer_ {other.size_ > 0 ? new int[other.size_] : nullptr},
      size_ {other.size_},
      capacity_ {other.capacity_} {
  for (int i = 0; i < size_; ++i) {
    arrayPointer_[i] = other.arrayPointer_[i];
  }
}

MyVector::~MyVector() {
  delete[] arrayPointer_;
}

// Copy assignment operator
// For you to implement
MyVector& MyVector::operator=(MyVector other) {
  std::swap(arrayPointer_, other.arrayPointer_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  return *this;
}

void MyVector::push_back(int val) {
  if (size_ < capacity_) {
    arrayPointer_[size_++] = val;
  } else {
    capacity_ = (size_ == 0 ? 1 : 2*size_);
    int* temp = new int[capacity_];
    for (int i = 0; i < size_; ++i) {
      temp[i] = arrayPointer_[i];
    }
    temp[size_] = val;
    ++size_;
    delete[] arrayPointer_;
    arrayPointer_ = temp;
    temp = nullptr;
  }
}

void MyVector::pop_back() {
  --size_;
}

int MyVector::back() {
  return arrayPointer_[size_-1];
}

bool MyVector::empty() {
  return size_ == 0;
}

int MyVector::size() const {
  return size_;
}

int MyVector::capacity() const {
  return capacity_;
}

bool MyVector::operator==(const MyVector& other) const {
  if (size_ != other.size_) {
    return false;
  }
  for (int i = 0; i < size_; ++i) {
    if (arrayPointer_[i] != other.arrayPointer_[i]) {
      return false;
    }
  }
  return true;
}

int& MyVector::operator[](int i) {
  return arrayPointer_[i];
}

int MyVector::operator[](int i) const {
  return arrayPointer_[i];
}
