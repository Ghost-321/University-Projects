#include <iostream>
#include <initializer_list>
#include "myVector.hpp"

MyVector::MyVector() {}

MyVector::MyVector(int n) {
  if (n < 0) {
    std::cout << "Error, size should be non-negative\n";  
    return;
  }
  arrayPointer_ = new int[n] {}; 
  size_ = capacity_ = n;
}

// We write this constructor for you to serve as an example
// An initializer_list is a very lightweight container 
// which is used to initialize a vector with a list of values
// std::vector<int> vec {1, 2, 3, 4};
// This constructor implements the same functionality for MyVector.
MyVector::MyVector(std::initializer_list<int> vals) {
  size_ = capacity_ = vals.size();
  arrayPointer_ = new int[size_]; 
  int i = 0;
  for (int x : vals) {
    arrayPointer_[i++] = x;
  }
}

MyVector::~MyVector() {
  delete[] arrayPointer_;
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
    temp[size_++] = val;
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

int& MyVector::operator[](int i) {
  return arrayPointer_[i];
}
