#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include "heap.hpp"
#include "my_integer.hpp"

TEST(HeapTest, pushOneElement) {
  Heap<int> heap {};
  heap.push(1);
  EXPECT_EQ(heap.top(), 1);
}

TEST(HeapTest, pushAFewElements) {
  Heap<int> heap {};
  heap.push(1);
  heap.push(2);
  heap.push(3);
  heap.push(4);
  EXPECT_EQ(heap.top(), 1);
  EXPECT_EQ(heap.size(), 4);
}

TEST(HeapTest, pushAndPop) {
  Heap<int> heap {};
  heap.push(4);
  heap.push(2);
  heap.push(1);
  heap.push(3);
  EXPECT_EQ(heap.size(), 4);
  EXPECT_EQ(heap.top(), 1);
  heap.pop();
  EXPECT_EQ(heap.top(), 2);
  heap.pop();
  EXPECT_EQ(heap.top(), 3);
  heap.pop();
  EXPECT_EQ(heap.top(), 4);
  heap.pop();
  EXPECT_TRUE(heap.empty());
}

TEST(HeapTest, sortedOrder) {
  Heap<int> heap {};
  std::vector<int> vec {23, 5, -10, 23, 8};
  for (int x : vec) {
    heap.push(x);
  }
  std::sort(vec.begin(), vec.end());
  for (int x : vec) {
    EXPECT_EQ(x, heap.top());
    heap.pop();
  }
  EXPECT_TRUE(heap.empty());
}

TEST(HeapTest, repeatedKeys) {
  Heap<int> heap {};
  std::vector<int> vec {23, 5, 5, -10, 8, 23, 8, 23};
  for (int x : vec) {
    heap.push(x);
  }
  std::sort(vec.begin(), vec.end());
  for (int x : vec) {
    EXPECT_EQ(x, heap.top());
    heap.pop();
  }
  EXPECT_TRUE(heap.empty());
}

void sortTest(const int N, unsigned seed = 42) {
  std::mt19937 mt {seed};
  std::uniform_int_distribution<int> dist {};
  std::vector<int> keys(N);
  std::generate(keys.begin(), keys.end(), [&mt, &dist](){return dist(mt);});
  Heap<int> heap {};
  for (int i = 0; i < N; ++i) {
    heap.push(keys.at(i));
  }
  std::sort(keys.begin(), keys.end());
  for (int x : keys) {
    EXPECT_EQ(x, heap.top());
    heap.pop();
  }
}

TEST(HeapTest, sortTest1) {
  sortTest(100, 894'398);
}

TEST(HeapTest, sortTest2) {
  sortTest(200, 999'283);
}

TEST(HeapTest, sortTest3) {
  sortTest(1'000, 9'231'783);
}

TEST(HeapTest, sortTest4) {
  sortTest(100'000, 3'773'828);
}

TEST(HeapTest, sortTest5) {
  sortTest(100'000, 2'783'282);
}

TEST(HeapTest, sortTest6) {
  sortTest(3'000, 38'923);
}

void myIntegerTest(const int N, unsigned seed = 42) {
  std::mt19937 mt {seed};
  std::uniform_int_distribution<int> dist {};
  std::vector<MyInteger> keys(N);
  std::generate(keys.begin(), keys.end(), [&mt, &dist](){return MyInteger {dist(mt)};});
  Heap<MyInteger> heap {};
  MyInteger::clearCounts();
  for (int i = 0; i < N; ++i) {
    heap.push(keys.at(i));
  }
  std::cout << "operation counts for pushes\n";
  MyInteger::printCounts();
  std::sort(keys.begin(), keys.end());
  MyInteger::clearCounts();
  for (const MyInteger& x : keys) {
    EXPECT_EQ(x, heap.top());
    heap.pop();
  }
  std::cout << "operation counts for pops\n";
  MyInteger::printCounts();
}

TEST(HeapTest, myIntegerTest1) {
  myIntegerTest(1'000, 223'895);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
