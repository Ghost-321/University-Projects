#include <iostream>
#include <initializer_list>
#include "myVector.hpp"

template <typename T>
MyVector<T>::MyVector() {}

template <typename T>
MyVector<T>::MyVector(int n) :
  arrayPointer_ {n > 0 ? new T[n]{} : nullptr},
  size_ {n},
  capacity_ {n} {}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) 
    : arrayPointer_ {other.size_ > 0 ? new T[other.size_] : nullptr},
      size_ {other.size_},
      capacity_ {other.capacity_} {
  for (int i = 0; i < size_; ++i) {
    arrayPointer_[i] = other.arrayPointer_[i];
  }
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> vals) {
  size_ = capacity_ = vals.size();
  arrayPointer_ = new T[size_];
  int i = 0;
  for (T x : vals) {
    arrayPointer_[i++] = x;
  }
}

template <typename T>
MyVector<T>::~MyVector() {
  delete[] arrayPointer_;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T> other) {
  std::swap(arrayPointer_, other.arrayPointer_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  return *this;
}

template <typename T>
void MyVector<T>::push_back(T val) {
  if (size_ < capacity_) {
    arrayPointer_[size_++] = val;
  } else {
    capacity_ = (size_ == 0 ? 1 : 2*size_);
    T* temp = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
      temp[i] = arrayPointer_[i];
    }
    temp[size_++] = val;
    delete[] arrayPointer_;
    arrayPointer_ = temp;
    temp = nullptr;
  }
}

template <typename T>
void MyVector<T>::pop_back() {
  if (!empty()) {
    --size_;
  }
}

template <typename T>
T& MyVector<T>::back() {
  return arrayPointer_[size_-1];
}

template <typename T>
bool MyVector<T>::empty() {
  return size_ == 0;
}

template <typename T>
int MyVector<T>::size() const {
  return size_;
}

template <typename T>
int MyVector<T>::capacity() const {
  return capacity_;
}

template <typename T>
T& MyVector<T>::operator[](int i) {
  return arrayPointer_[i];
}

template <typename T>
const T& MyVector<T>::operator[](int i) const {
  return arrayPointer_[i];
}

template class MyVector<int>;
template class MyVector<float>;
template class MyVector<double>;
