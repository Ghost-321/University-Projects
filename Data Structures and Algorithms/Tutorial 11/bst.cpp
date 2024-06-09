#include <vector>
#include <algorithm>
#include <string>
#include "bst.hpp"

// Default constructor
// No need to do anything here
template <typename T>
BST<T>::BST() {}

template <typename T>
BST<T>::BST(const std::initializer_list<T>& input) {
  for (const auto& x : input) {
    insert(x);
  }
}

// Destructor
// ***For you to implement
template <typename T>
BST<T>::~BST() {
  deleteSubtree(root_);
}

// insert
// ***For you to implement
template <typename T>
void BST<T>::insert(const T& key) {
  // First handle case when root_ is nullptr
  if (root_ == nullptr) {
    root_ = new Node(key);
    ++size_;
    return;
  }
  // previousNode will hold node's parent
  Node* previousNode {};
  for (Node* node = root_; node != nullptr;) {
    previousNode = node;
    if (key < node->key) {
      node = node->left;
    } else if (key > node->key) {
      node = node->right;
    } else {
      return;
    }
  }
  // new node is either left or right child of previousNode
  if (key > previousNode->key) {
    previousNode->right = new Node(key, previousNode);
  } else {
    previousNode->left = new Node(key, previousNode);
  }
  ++size_;
}

// find
// ***For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::find(const T& k) const {
  for (Node* node = root_; node != nullptr;) {
    if (k == node->key) {
      return node;
    }
    node = k < node->key ? node->left : node->right;
  }
  return nullptr;
}

template <typename T>
typename BST<T>::Node* BST<T>::successor(const T& k) const {
  // begin as in find, but remember the last left turn on the 
  // way to the node with key k
  Node* node {root_};
  // important to initialise lastLeft to nullptr for case k is maximum key
  Node* lastLeft {nullptr};
  while (node != nullptr && node->key != k) {
    if (k < node->key) {
      lastLeft = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  // case 1: key is not in the tree
  if (node == nullptr) {
    return node;
  }
  // case 2: node has a right child
  if (node->right != nullptr) {
    return min(node->right);
  } 
  // case 3: no right child
  return lastLeft;
}

// min
// ***For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::min() const {
  if (root_ == nullptr) {
    return root_;
  }
  return min(root_);
}

// makeVector
// ***For you to implement
template <typename T>
typename std::vector<T> BST<T>::makeVector() const {
  std::vector<T> vec;
  vec.reserve(size_);
  makeVector(root_, vec);
  return vec;
}

template <typename T>
int BST<T>::size() const {
  return size_;
}

template <typename T>
bool BST<T>::empty() const {
  return (size_ == 0);
}

template <typename T>
void BST<T>::deleteSubtree(Node* node) {
  if (node == nullptr) {
    return;
  }
  deleteSubtree(node->left);
  deleteSubtree(node->right);
  delete node;
}


template <typename T>
void BST<T>::makeVector(Node* node, std::vector<T>& vec) const {
  if (node == nullptr) {
    return;
  }
  makeVector(node->left, vec);
  vec.push_back(node->key);
  makeVector(node->right, vec);
}


template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node) const {
  for (; node->left != nullptr; node = node->left) {}
  return node;
}

// please do not change the lines below.
// they tell the compiler with what template types
// the BST will be instantiated
template class BST<int>;
template class BST<double>;
template class BST<char>;
template class BST<std::string>;
