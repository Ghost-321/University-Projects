#include <gtest/gtest.h>
#include <iostream>
#include "findCycle.hpp"

int findCycleLength(Node* start) {
  if (start == nullptr) return -1;

    Node* tortoise = start;
    Node* hare = start;

    do {
      tortoise = tortoise->next;
      hare = hare->next;
      if (hare == nullptr || hare->next == nullptr) {
        return -1;
      }
      hare = hare->next;
    }
    while (tortoise != hare);
    int cycle_length = 0;
    do {
      hare = hare->next;
      cycle_length++;
    } while (tortoise != hare);
    return cycle_length;
}
