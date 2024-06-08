#include <gtest/gtest.h>
#include <iostream>
#include <vector>

void printVec(const std::vector<int>& vec) {
  for (int x : vec) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int square(int a) {
  return a*a;
}

// practice with pointers
// implement swap with pointer parameters
void swap(int* ptr1, int* ptr2) {
  int temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp; 
}

// Unit Tests
TEST(passby, swapValues) {
  int x {3};
  int y {5};
  swap(x,y);
  EXPECT_EQ(x, 5);
  EXPECT_EQ(y, 3);
}

TEST(passby, square) {
  int x {3};
  EXPECT_EQ(square(x), 9);
}

TEST(passby, swapWithPointers) {
  int x {3};
  int y {5};
  swap(&x, &y);
  EXPECT_EQ(x, 5);
  EXPECT_EQ(y, 3);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();
}
