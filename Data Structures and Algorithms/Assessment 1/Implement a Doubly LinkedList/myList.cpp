#include <iostream>
#include <utility>
#include <string>
#include "myList.hpp"
#include "myInteger.hpp"

// default constructor
template <typename T>
MyList<T>::MyList(): head_(nullptr), tail_(nullptr), size_(0) {}

// copy constructor
template <typename T>
MyList<T>::MyList(const MyList& other) : MyList() {
    for (Node* currentNode = other.head_; currentNode != nullptr; currentNode = currentNode -> next) {
        push_back(currentNode -> data);
    }
}

// assignment operator
template <typename T>
MyList<T>& MyList<T>::operator=(MyList other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);

    return *this;
}


// destructor
template <typename T>
MyList<T>::~MyList() {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_ -> next;
        delete temp;
    }
}

// constructor from an initializer list
template <typename T>
MyList<T>::MyList(std::initializer_list<T> vals) : MyList() {
    for (const T& val : vals) {
        push_back(val);
    }
}

// push back
template <typename T>
void MyList<T>::push_back(T val) {
    Node* newNode = new Node(val);
    newNode -> prev = tail_;
    if (tail_ != nullptr) {
        tail_ ->next = newNode;
    }

    tail_ = newNode;
    if (head_ == nullptr) {
        head_ = newNode;
    }

    size_++;
}

// pop back
template <typename T>
void MyList<T>::pop_back() {
    if (tail_ == nullptr) return;

    Node* temp = tail_;
    tail_ = tail_ -> prev;

    if (tail_ != nullptr) {
        tail_ -> next = nullptr;
    }

    else {
        head_ = nullptr;
    }

    delete temp;
    size_--;
}

template <typename T>
void MyList<T>::push_front(T val) {
    Node* newNode = new Node(val);
    newNode -> next = head_;
    if (head_ != nullptr) {
        head_ ->prev = newNode;
    }

    head_ = newNode;
    if (tail_ == nullptr) {
        tail_ = newNode;
    }

    size_++;
}

template <typename T>
void MyList<T>::pop_front() {
    if (head_ == nullptr) return;

    Node* temp = head_;
    head_ = head_ -> next;

    if (head_ != nullptr) {
        head_ -> prev = nullptr;
    }

    else {
        tail_ = nullptr;
    }

    delete temp;
    size_--;
}

// return the first element by reference
template <typename T>
T& MyList<T>::front() {
    return head_ -> data;
}

// return the first element by const reference
template <typename T>
const T& MyList<T>::front() const {
    return head_ -> data;
}

// return the last element by reference
template <typename T>
T& MyList<T>::back() {
    return tail_ -> data;
}

// return the last element by const reference
template <typename T>
const T& MyList<T>::back() const {
    return tail_ -> data;
}

// is the list empty?
template <typename T>
bool MyList<T>::empty() const {
    return size_ == 0;
}

// return the number of elements in the list
template <typename T>
int MyList<T>::size() const {
    return size_;
}

// These lines let the compiler know with which types we will be
// instantiating MyList
template class MyList<int>;
template class MyList<std::string>;
template class MyList<MyInteger>;
