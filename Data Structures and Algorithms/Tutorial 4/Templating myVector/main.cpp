#include <gtest/gtest.h>
#include <initializer_list>
#include <algorithm>
#include <random>
#include <vector>
#include "myVector.hpp"

TEST(Vector, allZeroVectorOfDoubles) {
  int n = 3;
  MyVector<double> vec(n);
  EXPECT_EQ(vec.size(), n);
  for (int i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(vec[i], 0.0);
  }
}

TEST(Vector, getAndSetFloats) {
  int n = 3;
  MyVector<float> vec(n);
  vec[1] = 2.2;
  EXPECT_FLOAT_EQ(vec[1], 2.2);
}

TEST(Vector, copyConstructorValues) {
  MyVector<float> vec1 {1.1, 2.2, 3.3};
  MyVector<float> vec2 {vec1};
  EXPECT_EQ(vec2.size(), vec1.size());
  for (int i = 0; i < vec2.size(); ++i) {
    EXPECT_FLOAT_EQ(vec2[i], vec1[i]);
  } 
}

TEST(Vector, copyConstructorDeep) {
  MyVector<double> vec1 {1.1, 2.2, 3.3};
  MyVector<double> vec2 {vec1};
  vec2[1] = 5.5;
  EXPECT_DOUBLE_EQ(vec1[1], 2.2);
  EXPECT_DOUBLE_EQ(vec2[1], 5.5);
}

TEST(Vector, copyAssignmentValues) {
  MyVector<int> vec1 {1, 2, 3, 4, 5};
  MyVector<int> vec2 {-1, -2, -3};
  vec1 = vec2;
  EXPECT_EQ(vec1.size(), vec2.size());
  for (int i = 0; i < vec1.size(); ++i) {
    EXPECT_EQ(vec1[i], vec2[i]);
  }
}

TEST(Vector, copyAssignmentDeep) {
  MyVector<int> vec1 {1, 2, 3, 4, 5};
  MyVector<int> vec2 {-1, -2, -3};
  vec1 = vec2;
  vec1[1] = 42;
  EXPECT_EQ(vec1[1], 42);
  EXPECT_EQ(vec2[1], -2);
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
