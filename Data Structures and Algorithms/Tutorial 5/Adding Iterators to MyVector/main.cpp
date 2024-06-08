#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <vector>
#include <algorithm>
#include "myVector.hpp"

TEST(myVector, begin) {
  MyVector<std::string> vec {"hello", "how", "are", "you"};
  EXPECT_EQ(*vec.begin(), "hello");
}

TEST(myVector, increment) {
  MyVector<std::string> vec {"hello", "how", "are", "you"};
  auto it = vec.begin();
  ++it;
  EXPECT_EQ(*it, "how");
}

TEST(myVector, decrement) {
  MyVector<std::string> vec {"hello", "how", "are", "you"};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it, "you");
}

TEST(myVector, iteratorLoop) {
  MyVector<int> vec {1, 2, 3, 4};
  int i {1};
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, i);
    ++i;
  }
}

TEST(myVector, assigningFromIterator) {
  MyVector<int> vec {5, 2, 3, 4};
  *vec.begin() = 1;
  int i {1};
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, i);
    ++i;
  }
}

TEST(myVector, iteratorBackwards) {
  MyVector<int> vec {1, 2, 3, 4};
  int i {4};
  for (auto it = vec.end(); it != vec.begin();) {
    --it;
    EXPECT_EQ(*it, i);
    --i;
  }
}

TEST(myVector, rangeBasedForLoop) {
  MyVector<std::string> vec {"hello", "how", "are", "you"};
  std::vector<std::string> realVec {"hello", "how", "are", "you"};
  auto it = realVec.begin();
  for (const auto& x : vec) {
    EXPECT_EQ(x, *it);
    ++it;
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
