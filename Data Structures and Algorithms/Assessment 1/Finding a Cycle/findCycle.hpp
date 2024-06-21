#ifndef FIND_CYCLE_HPP_
#define FIND_CYCLE_HPP_

// Setup for linked list
struct Node {
  int num {};
  Node* next {nullptr};
};

int findCycleLength(Node*);

#endif    // FIND_CYCLE_HPP_
