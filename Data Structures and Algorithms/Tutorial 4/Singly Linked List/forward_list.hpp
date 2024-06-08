#ifndef FORWARD_LIST_HPP_
#define FORWARD_LIST_HPP_

#include <algorithm>

class ForwardList {
 public:
  struct Node {
    int data {};
    Node* next = nullptr;
    Node(){}
    Node(int input_data, Node* next_node= nullptr) : 
      data {input_data}, next {next_node} {}
  };

 private:
  int size_ = 0;
  Node* head_ = nullptr;

 public:
  ForwardList();

  // Destructor 
  ~ForwardList();
  
  // Constructor from initializer list
  ForwardList(std::initializer_list<int> input);
  
  // Add an element to the front of the list
  void push_front(int data);
  
  // Remove the first element of the list
  void pop_front();
  
  // Return the data held in the first item of the list
  int front() const;

  // Return the data held in the first item of the list by reference
  int& front();
  
  // Print out all the data in the list in sequence
  void display() const;
  
  // Outputs if the list is empty or not
  bool empty() const;
  
  // outputs the size of the list
  int size() const;
};

#endif    // FORWARD_LIST_HPP_
