#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "mergesort.hpp"

TEST(mergeTest, vectorOfSizeOne) {
  std::vector<int> vec {3};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, vectorOfSizeTwoSwap) {
  std::vector<int> vec {5, 3};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, vectorOfSizeTwoSorted) {
  std::vector<int> vec {10, 20};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, reverseSorted) {
  std::vector<int> vec {10, 5, 3, -2, -100};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, vectorOfStrings) {
  std::vector<std::string> vec {"good", "day", "how", "are", "you"};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, vectorOfChars) {
  std::vector<char> vec {'s', 't', 'r', 'i', 'p', 'e', 'd', 'z', 'e', 'b', 'r', 'a'};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, maxAtFront) {
  std::vector<int> vec {1000, 23, -10, 59, 32, -20, 5, 1};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, alternating) {
  std::vector<int> vec {5, 8, 2, 10, 4, 12, 1, 15};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, upAndDown) {
  std::vector<int> vec {1, 2, 3, 4, 4, 3, 2, 1};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(mergeTest, repeatedEntries) {
  std::vector<int> vec {1, 1, -1, 5, 8, -1, 1, 2};
  mergesort(vec.begin(), vec.end());
  EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
