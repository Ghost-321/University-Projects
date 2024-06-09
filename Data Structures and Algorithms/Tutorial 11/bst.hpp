#ifndef BST_HPP_
#define BST_HPP_

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 public:
  class Node {
   public:
    T key {};
    Node* left {nullptr};
    Node* right {nullptr};
    Node* parent {nullptr};
    // Default constructor
    Node() {}
    // Constructor that sets key and parent node
    // You can also call this constructor with just
    // the first argument and the second argument will default
    // to nullptr
    explicit Node(T k, Node* node = nullptr) : key {k}, parent {node} {}
  };

 private:
  // We indicate these are private member variables by using
  // a trailing underscore
  Node* root_ = nullptr;
  int size_ = 0;

 public:
  // Default constructor--no need to do anything with this
  BST();

  BST(const std::initializer_list<T>&);

  // Destructor
  // ***For you to implement
  ~BST();


  // insert a new key into the tree.  We will maintain a set of keys,
  // if the argument k is already in the tree then no action is taken
  // ***For you to implement
  void insert(const T& k);

  // Search the tree for key k
  // Return a pointer to the node holding the key if it is in the tree
  // and nullptr otherwise
  // ***For you to implement
  Node* find(const T& k) const;

  // Return a pointer to the node holding the smallest key larger than k.
  // Return nullptr if k is not in the tree or k is the maximum element
  Node* successor(const T& k) const;

  // return a pointer to the node holding the minimum key in the tree
  // ***For you to implement
  Node* min() const;

  // make a vector with all keys in the tree ordered from smallest to largest
  // i.e. push back keys to the vector while doing an in-order traversal of
  // the tree
  // ***For you to implement
  std::vector<T> makeVector() const;

  // return the number of elements in the tree
  // implemented for you
  int size() const;

  // return whether or not the tree is empty
  // implemented for you
  bool empty() const;

 private:
  // Some helper functions we found useful in our solution
  void deleteSubtree(Node* node);
  void makeVector(Node* node, std::vector<T>& vec) const;
  Node* min(Node* node) const;
};

#endif      // BST_HPP_
