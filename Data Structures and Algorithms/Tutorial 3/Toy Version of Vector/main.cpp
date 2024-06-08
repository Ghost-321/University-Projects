#include <gtest/gtest.h>
#include <initializer_list>
#include "myVector.hpp"

TEST(Vector, defaultConstructSizeZero) {
  MyVector vec {};
  EXPECT_EQ(vec.size(), 0);
}

TEST(Vector, constructZeroVector) {
  int n = 3;
  MyVector vec(n);
  EXPECT_EQ(vec.size(), n);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(Vector, getAndSet) {
  int n = 3;
  MyVector vec(n);
  vec[1] = 2;
  EXPECT_EQ(vec[1], 2);
}

TEST(Vector, arrayDoubling) {
  MyVector vec(2);
  vec.push_back(3); 
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 4);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
