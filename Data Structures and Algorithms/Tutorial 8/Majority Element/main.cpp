#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include "majority.hpp"

TEST(MajorityTest, sizeOne) {
  std::vector<int> vec {5};
  EXPECT_EQ(majorityElement(vec), 5);
}

TEST(MajorityTest, sizeThree) {
  std::vector<int> vec {3, 2, 3};
  EXPECT_EQ(majorityElement(vec), 3);
}

TEST(MajorityTest, sizeFour) {
  std::vector<int> vec {1, 2, 1, 1};
  EXPECT_EQ(majorityElement(vec), 1);
}

TEST(MajorityTest, sizeFive) {
  std::vector<int> vec {1, 2, 1, 2, 1};
  EXPECT_EQ(majorityElement(vec), 1);
}

TEST(MajorityTest, majorityComesAtEnd) {
  std::vector<int> vec {-5, -5, -5, 3, 3, 3, 3};
  EXPECT_EQ(majorityElement(vec), 3);
}

TEST(MajorityTest, majorityComesAtBeginning) {
  std::vector<int> vec {3, 3, 3, 3, -5, -5, -5};
  EXPECT_EQ(majorityElement(vec), 3);
}

// random tests
void
twoValues(int n, unsigned seed, int val1, int val2) {
  std::mt19937 mt {seed};
  std::vector<int> vec(n + 1, val1);
  std::vector<int> other(n, val2);
  vec.insert(vec.end(), other.begin(), 
                        other.end());
  std::shuffle(vec.begin(), vec.end(), mt);
  EXPECT_EQ(majorityElement(vec), val1);
}

TEST(MajorityTest, randomBoolean0) {
  twoValues(100'000, 4'984'398, 0, 1);
}

TEST(MajorityTest, randomBoolean1) {
  twoValues(100'000, 8'239'823, 1, 0);
}

TEST(MajorityTest, randomVector1) {
  const int n = 100'000;
  std::mt19937 mt {8'239'823};
  int val = mt();
  std::vector<int> vec(n + 1, val);
  std::vector<int> randomVec(n);
  std::generate(randomVec.begin(), randomVec.end(),
    [&mt](){return mt();});
  vec.insert(vec.end(), randomVec.begin(), 
                        randomVec.end());
  std::shuffle(vec.begin(), vec.end(), mt);
  EXPECT_EQ(majorityElement(vec), val);
}

TEST(MajorityTest, twoRandomValues) {
  const int n = 100'000;
  unsigned seed = 10'383'883;
  std::mt19937 mt {seed};
  int val1 = mt();
  int val2 = mt();
  while (val2 == val1) {
    val2 = mt();
  }
  twoValues(n, seed, val1, val2); 
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
