#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <vector>
#include <algorithm>

template <typename T>
class Heap {
 private:
  std::vector<T> vec {};
  int size_ = 0;

 public:
  Heap();
  void push(const T& key);
  void pop();
  const T& top() const;
  int size() const;
  bool empty() const;

 private:
  void swim(int i);
  void sink();
};

// Useful helper functions
int leftChild(int i) {
  return 2*i;
}

int rightChild(int i) {
  return 2*i + 1;
}

int parent(int i) {
  return i/2;
}

// Heap member functions
// store dummy element in vec[0]
template <typename T>
Heap<T>::Heap() {
  vec.push_back(T {});
}

template <typename T>
void Heap<T>::push(const T& key) {
  ++size_;
  vec.push_back(key);
  swim(size_);
}

template <typename T>
void Heap<T>::pop() {
  if (size_ == 0) {
    std::cerr << "no elements in the heap" << '\n';
    return;
  }
  vec.at(1) = vec.at(size_);
  vec.pop_back();
  --size_;
  sink();
}

template <typename T>
const T& Heap<T>::top() const {
  if (size_ > 0) {
    return vec.at(1);
  }
  std::cerr << "no elements in the heap" << '\n';
  return vec.at(0);
}

template <typename T>
int Heap<T>::size() const {
  return size_;
}

template <typename T>
bool Heap<T>::empty() const {
  return size_ == 0;
}

template <typename T>
void Heap<T>::swim(int i) {
  for (int p = parent(i); p > 0; p = parent(p)) {
    if (vec.at(i) >= vec.at(p)) {
      return;
    }
    std::swap(vec.at(i), vec.at(p));
    i = p;
  }
}

template <typename T>
void Heap<T>::sink() {
  for (int current = 1; leftChild(current) <= size_;) {
    int left = leftChild(current);
    int toSwap = left;
    // check that left + 1 is valid index before
    // accessing it
    if (left + 1 <= size_ and vec.at(left) > vec.at(left + 1)) {
      ++toSwap;
    }
    if (vec.at(current) <= vec.at(toSwap)) {
      return;
    }
    std::swap(vec.at(current), vec.at(toSwap));
    current = toSwap;
  }
}

#endif      // HEAP_HPP_
