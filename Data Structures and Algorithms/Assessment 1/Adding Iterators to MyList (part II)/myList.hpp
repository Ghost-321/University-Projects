#ifndef MY_LIST_HPP_
#define MY_LIST_HPP_

#include <initializer_list>
#include <cassert>

template <typename T>
class MyList  {
 public:
  struct Node {
    T data {};
    Node* prev {nullptr};
    Node* next {nullptr};
    Node(T input_data = T {}, Node* prevNode = nullptr, 
      Node* nextNode = nullptr) : data {input_data}, prev {prevNode}, 
                                  next {nextNode} {} 
  };

  class Iterator {
    // useful reference
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
   private: 
    Node* current_;
    friend class MyList<T>;

   public:
    // construct an Iterator from a pointer to a Node
    Iterator(Node* node = nullptr) : current_(node) {}
    // advance an iterator to the next Node (pre-increment)
    Iterator& operator++() {
            assert(current_ && "Attempts to increment end iterator");
            current_ = current_->next;
            return *this;
        }
    // move iterator to previous node (pre-decrement)
    Iterator& operator--() {
            assert(current_ && "Attempts to decrement begin iterator");
            current_ = current_->prev;
            return *this;
        }
    // return value at the node pointed to by the iterator
    T& operator*() const {
            assert(current_ && "Attempts to dereference end iterator");
            return current_->data;
        }

    // test if two iterators are equal
        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
  };

  // TODO: add the member variables you need for your solution
 private:
  Node* head_;
  Node* tail_;
  Node* sentinel_;
  int size_;

 public:
  // Default Constructor
  // Do some setup of your list architecture?
  MyList(); 

  // Construct a list from an initializer list
  // This lets us create a list with the ints 1,2,3,4 by saying
  // MyList<int> li {1,2,3,4};
  MyList(std::initializer_list<T> vals);

  // Copy Constructor
  MyList(const MyList& other); 

  // Operator=
  MyList& operator=(MyList other); 

  // Destructor
  // free all memory allocated with new
  ~MyList();
 
  // return the first element by reference
  T& front();
  // return the first element by const reference
  // this one can be used on a const MyList
  const T& front() const;

  // return the last element by reference
  T& back();
  // return the last element by const reference
  // this one can be used on a const MyList
  const T& back() const;

  void clear();
  // add an element to the front of the list
  void push_front(T value);
  // remove the first element
  void pop_front();
  // add an element to the back of the list
  void push_back(T value);
  // remove the last element
  void pop_back();

  // add an element to the list before the node pointed to by the Iterator
  void insert(const Iterator& pos, const T& value);
  // remove the element of the list pointed to by the Iterator
  void erase(const Iterator& pos);

  // does the list have any elements?
  bool empty() const {return size_ == 0; }
  // return the number of elements in the list
  int size() const {return size_; }

  // return an Iterator pointing to the first element

  Iterator begin() const { return Iterator(head_); }
  // return an Iterator that does not point to any element in the list.
  // This serves as a sentinel for having reached past the end of the list

  Iterator end() const { return Iterator(sentinel_); }
};

#endif    // MY_LIST_HPP_
