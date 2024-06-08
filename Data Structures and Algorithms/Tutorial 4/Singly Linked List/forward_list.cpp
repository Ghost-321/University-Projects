#include <iostream>
#include <initializer_list>
#include <string>
#include "forward_list.hpp"

// Default Constructor
ForwardList::ForwardList() {}

// Destructor
// The destructor is implemented for you
ForwardList::~ForwardList() {
  for (Node* cur = head_; cur != nullptr;) {
    Node* tmp = cur;
    cur = cur->next;
    delete tmp;
    --size_;
  }
}

// Constructor from initializer list
ForwardList::ForwardList(std::initializer_list<int> input) {
  for (auto it = std::rbegin(input); it != std::rend(input); ++it) {
    push_front(*it);
  }
}


// Add element to front of list
void ForwardList::push_front(int data) {
  head_ = new Node(data, head_);
  ++size_;
}

// Remove the front element of the list 
void ForwardList::pop_front() {
  if (empty()) {
    std::cout << "Error: calling pop front on an empty list\n";
    return;
  }
  Node* temp = head_;
  head_ = head_->next;
  delete temp;
  --size_;
}

// Return the data in the front element of the list by value
int ForwardList::front() const {
  return head_->data;
}

// Return the data in the front element of the list by reference
int& ForwardList::front() {
  return head_->data;
}

// Print out the list
void ForwardList::display() const {
  if (head_ != nullptr) {
    std::cout << head_->data;
  }
  for (Node* cur = head_->next; cur != nullptr; cur = cur->next) {
    std::cout << ' ' << cur->data;
  }
}

// Outputs if the list is empty or not
bool ForwardList::empty() const {
  return size_ == 0;
}

// Note that std::forward_list actually does not have a size function
int ForwardList::size() const {
  return size_;
}
