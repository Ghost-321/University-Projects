#ifndef INDEX_PRIORITY_QUEUE_HPP_
#define INDEX_PRIORITY_QUEUE_HPP_

#include <vector>
#include <algorithm>

template <typename T>
class IndexPriorityQueue {
 private:
  // vector to hold priorities.  
  // priorities.at(i) is the priority associated to index i
  // the heap will only contain indices, we look up priorities
  // in this vector as needed
  std::vector<T> priorities {};
  // priorityQueue stores indices: priorityQueue.at(i) is an index
  // priorityQueue functions as the heap and is heap ordered: 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i)) 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i) + 1) 
  std::vector<int> priorityQueue {};
  // indexToPosition.at(i) is the position in priorityQueue of index i
  // priorityQueue.at(indexToPosition.at(i)) = i
  // indexToPosition.at(priorityQueue.at(j)) = j
  std::vector<int> indexToPosition {};
  int size_ = 0;

 public:
  explicit IndexPriorityQueue(int);
  void push(const T&, int);
  void pop();
  void erase(int);
  bool contains(int) const;
  void changeKey(const T&, int);
  std::pair<T, int> top() const;
  bool empty() const;
  int size() const;

 private:
  // TODO: you may want to add your own member functions. swim? sink?
  void swim(int k);
  void sink(int k);
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

// IndexPriorityQueue member functions
template <typename T>
IndexPriorityQueue<T>::IndexPriorityQueue(int N) {
  priorities.resize(N);
  priorityQueue.resize(N);
  indexToPosition.resize(N, -1);
  size_ = 0;
}

template <typename T>
bool IndexPriorityQueue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
int IndexPriorityQueue<T>::size() const {
  return size_;
}

template <typename T>
void IndexPriorityQueue<T>::push(const T& priority, int index) {
  if (contains(index)) return;
  priorities[index] = priority;
  priorityQueue[size_] = index;
  indexToPosition[index] = size_;
  swim(size_);
  size_++;
}

template <typename T>
void IndexPriorityQueue<T>::pop() {
  if (empty()) return;
  int minIndex = priorityQueue[0];
  std::swap(priorityQueue[0], priorityQueue[size_ - 1]);
  indexToPosition[priorityQueue[0]] = 0;
  size_--;
  sink(0);
  indexToPosition[minIndex] = -1;
}

template <typename T>
void IndexPriorityQueue<T>::erase(int index) {
  if (!contains(index)) return;
  int pos = indexToPosition[index];
  std::swap(priorityQueue[pos], priorityQueue[size_ -1]);
  indexToPosition[priorityQueue[pos]] = pos;
  size_--;
  swim(pos);
  sink(pos);
  indexToPosition[index] = -1;
}

template <typename T>
std::pair<T, int> IndexPriorityQueue<T>::top() const {
    if (empty()) throw std::runtime_error("Queue Empty");
    int minIndex = priorityQueue[0];
    return {priorities[minIndex], minIndex};
  }

// if vertex i is not present, insert it with key
// otherwise change the associated key value of i to key
template <typename T>
void IndexPriorityQueue<T>::changeKey(const T& key, int index) {
  if (!contains(index)) {
    push(key, index);
  } else {
    priorities[index] = key;
    swim(indexToPosition[index]);
    sink(indexToPosition[index]);
  }
}

template <typename T>
bool IndexPriorityQueue<T>::contains(int index) const {
  return index >= 0 && index < indexToPosition.size() && indexToPosition[index] != -1;
}

// These are the additional member functions

template <typename T>
void IndexPriorityQueue<T>::swim(int k) {
  while (k > 0 && priorities[priorityQueue[k]] < priorities[priorityQueue[(k-1) / 2]]) {
    std::swap(priorityQueue[k], priorityQueue[(k - 1) / 2]);
    indexToPosition[priorityQueue[k]] = k;
    indexToPosition[priorityQueue[(k - 1) / 2]] = (k - 1) / 2;
    k = (k - 1) / 2;
  }
}


template <typename T>
void IndexPriorityQueue<T>::sink(int k) {
  while (2 * k + 1 < size_) {
    int j = 2 * k + 1;
    if (j + 1 < size_ && priorities[priorityQueue[j + 1]] < priorities[priorityQueue[j]]) j++;
    if (priorities[priorityQueue[k]] <= priorities[priorityQueue[j]]) break;
    std::swap(priorityQueue[k], priorityQueue[j]);
    indexToPosition[priorityQueue[k]] = k;
    indexToPosition[priorityQueue[j]] = j;
    k = j;
  }
}

#endif      // INDEX_PRIORITY_QUEUE_HPP_
