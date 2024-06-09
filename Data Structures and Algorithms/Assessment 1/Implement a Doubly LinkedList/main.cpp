#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <list>
#include "myList.hpp"
#include "myInteger.hpp"

TEST(List, defaultConstructorInt) {
  MyList<int> li {};
}

TEST(List, defaultConstructorString) {
  MyList<std::string> li {};
}

TEST(List, defaultConstructorMyInt) {
  MyList<MyInteger> li {};
}

TEST(List, pushBackOne) {
  MyList<MyInteger> li {};
  li.push_back(MyInteger {5});
  EXPECT_EQ(li.size(), 1);
}

TEST(List, pushFrontOne) {
  MyList<MyInteger> li {};
  li.push_front(MyInteger {2});
  EXPECT_EQ(li.size(), 1);
}

TEST(List, initList) {
  MyList<int> li {1, 2, 3};
  EXPECT_EQ(li.size(), 3);
  EXPECT_EQ(li.front(), 1);
  EXPECT_EQ(li.back(), 3);
}

TEST(List, copyConstructor) {
  MyList<int> li {};
  li.push_front(5);
  li.push_front(2);
  li.push_back(14);
  MyList<int> li2 {li};
  EXPECT_EQ(li2.front(), 2);
  EXPECT_EQ(li2.back(), 14);
  EXPECT_EQ(li2.size(), 3);
}

TEST(List, copyConstructorAndPopFrontMyInt) {
  MyList<MyInteger> li {MyInteger {10}, MyInteger {32}, MyInteger {56}};
  MyList<MyInteger> li2 {li};
  EXPECT_EQ(li.front(), li2.front());
  EXPECT_EQ(li.back(), li2.back());
  EXPECT_EQ(li2.size(), 3);
  li.pop_front();
  li2.pop_front();
  EXPECT_EQ(li.front(), li2.front());
  EXPECT_EQ(li2.size(), 2);
}

TEST(List, popFrontOneInitList) {
  MyList<int> li {1};
  EXPECT_EQ(li.size(), 1);
  li.pop_front();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, modifyThroughFront) {
  MyList<int> li {1, 2, 3};
  li.front() = 0;
  EXPECT_EQ(li.front(), 0);
  EXPECT_EQ(li.back(), 3);
  EXPECT_EQ(li.size(), 3);
}

TEST(List, constFrontBack) {
  const MyList<std::string> li {"how", "are", "you"};
  EXPECT_EQ(li.front(), "how");
  EXPECT_EQ(li.back(), "you");
  EXPECT_EQ(li.size(), 3);
}

TEST(List, modifyThroughBack) {
  MyList<int> li {1, 2, 3};
  li.back() = 5;
  EXPECT_EQ(li.back(), 5);
  EXPECT_EQ(li.front(), 1);
  EXPECT_EQ(li.size(), 3);
}

TEST(List, popFrontOnePush) {
  MyList<std::string> li {};
  li.push_front("yada");
  li.pop_front();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, popBackOnePush) {
  MyList<std::string> li {};
  li.push_back("yada");
  li.pop_back();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, popBackOneInitList) {
  MyList<int> li {1};
  li.pop_back();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, pushFrontPopBack) {
  MyList<int> li {};
  li.push_front(15); 
  EXPECT_EQ(li.size(), 1);
  li.pop_back();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, pushBackPopFront) {
  MyList<int> li {};
  li.push_back(15); 
  EXPECT_EQ(li.size(), 1);
  li.pop_front();
  EXPECT_EQ(li.size(), 0);
}

TEST(List, copyConstructorNotShallow) {
  MyList<int> li {1, 2, 3};
  MyList<int> li2 {li};
  li.push_back(4);
  EXPECT_EQ(li2.size(), 3);
  EXPECT_EQ(li2.back(), 3);
  li2.pop_back();
  EXPECT_EQ(li.size(), 4);
}

TEST(List, assignmentTest) {
  MyList<int> v {5, 7, 9};
  MyList<int> w {11, 13, 15, 17};
  w = v;
  EXPECT_EQ(w.size(), 3); 
  EXPECT_EQ(w.front(), 5); 
  EXPECT_EQ(w.back(), 9); 
}

TEST(List, assignmentNotShallow) {
  MyList<int> v {2, 4, 6, 8};
  MyList<int> w {-1, -2, -8, 19, 22, 43};
  v = w;
  EXPECT_EQ(v.size(), 6); 
  w.pop_front();
  EXPECT_EQ(v.size(), 6); 
  EXPECT_EQ(v.front(), -1); 
  EXPECT_EQ(w.front(), -2); 
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
