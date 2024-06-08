#include <gtest/gtest.h>
#include <initializer_list>
#include "myVector.hpp"

TEST(CopyConstructor, copyConstructorEqualValues) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {vec};
  EXPECT_EQ(vec2, vec);
}

TEST(CopyAssignement, copyAssignmentEqualValues) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {6, 7, 8, 9};
  vec2 = vec;
  EXPECT_EQ(vec2, vec);
}

TEST(CopyAssignment, copyAssignmentEqualCapacities) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {6, 7, 8, 9};
  vec2 = vec;
  EXPECT_EQ(vec2.capacity(), vec.capacity());
}

TEST(CopyConstructor, copyConstructorDeepCopy) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {vec};
  vec2[0] = -1;
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec2[0], -1);
}

TEST(CopyAssignment, copyAssignmentDeepCopy) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {6, 7, 8, 9};
  vec2 = vec;
  vec2[0] = -1;
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec2[0], -1);
}

TEST(CopyAssignment, copyAssignmentChaining) {
  MyVector vec {1, 3, 4, 5};
  MyVector vec2 {};
  MyVector vec3 {};
  vec3 = vec2 = vec;
  EXPECT_EQ(vec2, vec);
  EXPECT_EQ(vec3, vec);
}

// helper function to print out a MyVector
void printMyVector(const MyVector& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << ' ';
  }
  std::cout << '\n';
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
