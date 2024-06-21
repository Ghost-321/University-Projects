#include <gtest/gtest.h>
#include <iostream>
#include "findCycle.hpp"

TEST(CycleTest, sizeOneNoCycle) {
  Node a {1};
  EXPECT_EQ(findCycleLength(&a), -1);
}

TEST(CycleTest, sizeTwoNoCycle) {
  Node b {2};
  Node a {1, &b};
  EXPECT_EQ(findCycleLength(&a), -1);
}

TEST(CycleTest, ValuesDontMatter) {
  Node c {0};
  Node b {0, &c};
  Node a {0, &b};
  EXPECT_EQ(findCycleLength(&a), -1);
}

TEST(CycleTest, smallPShape) {
  Node d {0};
  Node c {0, &d};
  Node b {0, &c};
  Node a {0, &b};
  d.next = &b;
  EXPECT_EQ(findCycleLength(&a), 3);
}

TEST(CycleTest, anotherSmallP) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &c;
  EXPECT_EQ(findCycleLength(&a), 2);
}

TEST(CycleTest, selfLoop) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &d;
  EXPECT_EQ(findCycleLength(&a), 1);
}

TEST(CycleTest, sizeOneSelfLoop) {
  Node a {1};
  a.next = &a;
  EXPECT_EQ(findCycleLength(&a), 1);
}

TEST(CycleTest, triangle) {
  Node c {3};
  Node b {2, &c};
  Node a {1, &b};
  c.next = &a;
  EXPECT_EQ(findCycleLength(&a), 3);
}

TEST(CycleTest, smallCycle) {
  Node d {4};
  Node c {3, &d};
  Node b {2, &c};
  Node a {1, &b};
  d.next = &a;
  EXPECT_EQ(findCycleLength(&a), 4);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
