//forgot to add sources
// https://web.eecs.utk.edu/~bvanderz/teaching/cs140Fa10/notes/Dllists/#:~:text=A%20sentinel%20node%20is%20a,do%20with%20singly%2Dlinked%20lists. - Sentinel Nodes explanation and idea is from discussion board
// https://www.geeksforgeeks.org/doubly-linked-list-using-sentinel-nodes/ Helped in implementation of Sentinel Nodes
// https://www.quora.com/Why-do-insert-erase-member-functions-of-vector-sequence-container-take-const_iterators-as-arguments-while-they-change-remove-elements-elements This Quora sub provided a lot of insight to the theory and assisted greatly near the end to realise my mess-ups
// There are a lot of mini-sources where I kind of went insane in trying to learn what tf is memory leaks and how to locate them which I can add if necessary.


#include <iostream>
#include <utility>
#include <string>
#include "myList.hpp"
#include "myInteger.hpp"

// default constructor
template <typename T>
MyList<T>::MyList() : size_(0) {
    sentinel_ = new Node(); 
    sentinel_->next = sentinel_->prev = sentinel_;
    head_ = tail_ = sentinel_;
}

// copy constructor
template <typename T>
MyList<T>::MyList(const MyList& other) : MyList() {
    for (Node* node = other.head_; node != other.sentinel_; node = node->next) {
        push_back(node->data);
    }
}

// assignment operator
template <typename T>
MyList<T>& MyList<T>::operator=(MyList other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(sentinel_, other.sentinel_);
    std::swap(size_, other.size_);
    return *this;
}

// destructor
template <typename T>
MyList<T>::~MyList() {
    clear();
    delete sentinel_;
}

// constructor from an initializer list
template <typename T>
MyList<T>::MyList(std::initializer_list<T> vals) : MyList() {
    for (const T& val : vals) {
        push_back(val);
    }
}
//clear
template <typename T>
void MyList<T>::clear() {
    Node* current = head_;
    while (current != sentinel_) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head_ = tail_ = sentinel_;
    sentinel_->next = sentinel_->prev = sentinel_;
    size_ = 0;
}
// push back
template <typename T>
void MyList<T>::push_back(T value) {
    Node* newNode = new Node(value, tail_, sentinel_);
    tail_->next = newNode;
    sentinel_->prev = newNode;
    tail_ = newNode;
    if (head_ == sentinel_) head_ = newNode;
    size_++;
}

// pop back
template <typename T>
void MyList<T>::pop_back() {
    assert(tail_ != sentinel_ && "Attempts to pop from empty list");
    Node* toDelete = tail_;
    tail_ = tail_->prev;
    tail_->next = sentinel_;
    sentinel_->prev = tail_;
    delete toDelete;
    size_--;
}

template <typename T>
void MyList<T>::push_front(T value) {
    Node* newNode = new Node(value, sentinel_, head_);
    head_->prev = newNode;
    sentinel_->next = newNode;
    head_ = newNode;
    if (tail_ == sentinel_) tail_ = newNode;
    size_++;
}

template <typename T>
void MyList<T>::pop_front() {
    assert(head_ != sentinel_ && "Attempts to pop from an empty list");
    Node* toDelete = head_;
    head_ = head_->next;
    head_->prev = sentinel_;
    sentinel_->next = head_;
    delete toDelete;
    size_--;
}

// return the first element by reference
template <typename T>
T& MyList<T>::front() {
    assert(!empty() && "Attempt to access the front upon an empty list");
    return head_->data;
}

// return the first element by const reference
//template <typename T>
//const T& MyList<T>::front() const {}

// return the last element by reference
template <typename T>
T& MyList<T>::back() {
    assert(!empty() && "Attempts to access the back upon an empty list");
    return tail_->data;
}

// return the last element by const reference
//template <typename T>
//const T& MyList<T>::back() const {}

// is the list empty?
//template <typename T>
//bool MyList<T>::empty() const {}

// return the number of elements in the list
//template <typename T>
//int MyList<T>::size() const {}

// return an iterator pointing to the first element
//template <typename T>
//typename MyList<T>::Iterator MyList<T>::begin() const {}

// return an iterator pointing to the last element
//template <typename T>
//typename MyList<T>::Iterator MyList<T>::end() const {}

// insert an element into the linked list before *it with the value val
template <typename T>
void MyList<T>::insert(const Iterator& pos, const T& value) {
    if (pos.current_ == sentinel_) {
        Node* newNode = new Node(value, sentinel_->prev, sentinel_);
        sentinel_->prev->next = newNode;
        sentinel_->prev = newNode;
        if (head_ == sentinel_) { 
            head_ = newNode;
        }
        size_++;
    } else {
        Node* newNode = new Node(value, pos.current_->prev, pos.current_);
        pos.current_->prev->next = newNode;
        pos.current_->prev = newNode;
        if (pos.current_ == head_) {
            head_ = newNode;
        }
        size_++;
    }
}

// remove *it from the list
template <typename T>
void MyList<T>::erase(const Iterator& pos) {
    assert(pos.current_ != sentinel_ && "Attempt to erase at the sentinel (end)");
    if (pos.current_ == head_) head_ = pos.current_->next;
    if (pos.current_ == tail_) tail_ = pos.current_->prev;
    pos.current_->prev->next = pos.current_->next;
    pos.current_->next->prev = pos.current_->prev;
    delete pos.current_;
    size_--;
}

// Iterator constructor
//template <typename T>
//MyList<T>::Iterator::Iterator(Node* node, const MyList<T>* list) : current_(node), myList_(list) {}

// (pre-)increment an iterator
//template <typename T>
//typename MyList<T>::Iterator& MyList<T>::Iterator::operator++() {}


// (pre-)decrement an iterator
//template <typename T>
//typename MyList<T>::Iterator& MyList<T>::Iterator::operator--() {}

// return the value pointed at by an iterator
//template <typename T>
//T& MyList<T>::Iterator::operator*() const {}

template class MyList<int>;
template class MyList<std::string>;
template class MyList<MyInteger>;
