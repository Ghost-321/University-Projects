#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include "genericCycle.hpp"

// Setup for linked list
struct Node {
  int num {};
  Node* next {nullptr};
  Node* operator()(Node* x) const {return x->next;}
};

struct AdditiveOrder {
  int increment {};
  int modulus {};
  int operator()(int x) const {return (x + increment) % modulus;}
};

struct MultiplicativeOrder {
  int multiplier {};
  int modulus {};
  int operator()(int x) const {return (x * multiplier) % modulus;}
};


// helper functions for single linked list
std::pair<Node*, Node*> makeList(int size) {
  Node* tail = new Node {0};
  Node* nextNode = tail;
  for (int i = 1; i < size; ++i) {
    nextNode = new Node {0, nextNode};
  }
  return {nextNode, tail};
}

void addCycle(Node* head, Node*& tail, int start) {
  Node* current = head;
  for (int i = 1; i < start; ++i) {
    current = current->next;
  }
  tail->next = current;
}

void cleanUp(Node* head, int size) {
  for (int i = 0; i < size; ++i) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}

// Small Linked List Tests
TEST(CycleTest, smallPShape) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &b;
  // pass function using a lambda
  EXPECT_EQ(findCycleLength(&a, [](Node* x) {return x->next;}), 3);
}

TEST(CycleTest, anotherSmallP) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &c;
  // pass function using operator() in Node struct
  EXPECT_EQ(findCycleLength(&a, Node {}), 2);
}

TEST(CycleTest, selfLoop) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &d;
  EXPECT_EQ(findCycleLength(&a, Node {}), 1);
}

TEST(CycleTest, smallCycle) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &a;
  EXPECT_EQ(findCycleLength(&a, Node {}), 4);
}

TEST(CycleTest, fiveCycle) {
  Node e {0};
  Node d {0, &e};
  Node c {0, &d};
  Node b {0, &c};
  Node a {0, &b};
  e.next = &a;
  EXPECT_EQ(findCycleLength(&a, Node {}), 5);
}

TEST(CycleTest, fiveNodes) {
  Node e {0};
  Node d {0, &e};
  Node c {0, &d};
  Node b {0, &c};
  Node a {0, &b};
  e.next = &b;
  EXPECT_EQ(findCycleLength(&a, Node {}), 4);
}

// larger linked list tests
// helper function
void Ptester(const int N, int cycleTo) {
  auto [head, tail] = makeList(N);
  addCycle(head, tail, cycleTo);
  EXPECT_EQ(findCycleLength(head, Node {}), N - cycleTo + 1);
  cleanUp(head, N);
}

TEST(CycleTest, biggerPshape1) {
  Ptester(100, 21);
}

TEST(CycleTest, biggerPshape2) {
  Ptester(120, 84);
}

TEST(CycleTest, biggerPshape3) {
  Ptester(278, 103);
}

TEST(CycleTest, biggerPshape4) {
  Ptester(1'000, 898);
}

TEST(CycleTest, biggerPshape5) {
  Ptester(1'000, 1);
}

TEST(CycleTest, biggerPshape6) {
  Ptester(10'000, 3);
}

// does a std::list contain a cycle???
void listTester(const int N) {
  std::list v(N, 1);
  EXPECT_EQ(findCycleLength(v.begin(), [](auto it) {return ++it;}), N + 1);
}

TEST(CycleTest, listTestSize5) {
  listTester(5);
}

TEST(CycleTest, listTestSize100) {
  listTester(100);
}

TEST(CycleTest, listTestSize1000) {
  listTester(1'000);
}

TEST(CycleTest, listTestSize10000) {
  listTester(10'000);
}

TEST(CycleTest, listTestSize15000) {
  listTester(15'000);
}

TEST(CycleTest, listTestSize100000) {
  listTester(100'000);
}

// Look at 2 mod 7, 2 + 2 mod 7, 2 + 2 + 2 mod 7, ...
// when do we get back to 2?
TEST(CycleTest, additive72) {
  EXPECT_EQ(findCycleLength(2, AdditiveOrder {2, 7}), 7);
}

TEST(CycleTest, additive93) {
  EXPECT_EQ(findCycleLength(3, AdditiveOrder {3, 9}), 3);
}

TEST(CycleTest, additive511) {
  EXPECT_EQ(findCycleLength(5, AdditiveOrder {5, 11}), 11);
}

TEST(CycleTest, additive412) {
  EXPECT_EQ(findCycleLength(4, AdditiveOrder {4, 12}), 3);
}

TEST(CycleTest, additive321) {
  EXPECT_EQ(findCycleLength(3, AdditiveOrder {3, 21}), 7);
}

TEST(CycleTest, additive521) {
  EXPECT_EQ(findCycleLength(5, AdditiveOrder {5, 21}), 21);
}

// Look at 2 mod 7, 2 * 2 mod 7, 2 * 2 * 2 mod 7, ...
// when do we get back to 2?
TEST(CycleTest, Multiplicative27) {
  EXPECT_EQ(findCycleLength(2, MultiplicativeOrder {2, 7}), 3);
}

TEST(CycleTest, Multiplicative37) {
  EXPECT_EQ(findCycleLength(3, MultiplicativeOrder {3, 7}), 6);
}

TEST(CycleTest, Multiplicative313) {
  EXPECT_EQ(findCycleLength(3, MultiplicativeOrder {3, 13}), 3);
}

TEST(CycleTest, Multiplicative421) {
  EXPECT_EQ(findCycleLength(4, MultiplicativeOrder {4, 21}), 3);
}

TEST(CycleTest, Multiplicative521) {
  EXPECT_EQ(findCycleLength(5, MultiplicativeOrder {5, 21}), 6);
}

TEST(CycleTest, Multiplicative621) {
  EXPECT_EQ(findCycleLength(6, MultiplicativeOrder {6, 21}), 2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
