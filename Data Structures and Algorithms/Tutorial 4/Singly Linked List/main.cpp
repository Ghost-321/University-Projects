#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "forward_list.hpp"

TEST(ForwardListTest, defaultConstructor) {
  ForwardList intList;
  EXPECT_EQ(intList.size(), 0);
}

TEST(ForwardListTest, initializerListConstructor) {
  ForwardList intList {1, 2, 3, 4};
  EXPECT_EQ(intList.size(), 4); 
  EXPECT_EQ(intList.front(), 1); 
  intList.pop_front();
  EXPECT_EQ(intList.front(), 2); 
  intList.pop_front();
  EXPECT_EQ(intList.front(), 3); 
  intList.pop_front();
  EXPECT_EQ(intList.front(), 4); 
  intList.pop_front();
  EXPECT_TRUE(intList.empty()); 
}

TEST(ForwardListTest, toggleSize0and1) {
  ForwardList intList {};
  const int n {100};
  for (int i = 0; i < n; ++i) {
    intList.push_front(i);
    EXPECT_EQ(intList.size(), 1);
    intList.pop_front();
    EXPECT_TRUE(intList.empty());
  }
}

TEST(ForwardListTest, pushFront) {
  ForwardList intList {};
  const int n {100};
  for (int i = 0; i < n; ++i) {
    intList.push_front(i);
    EXPECT_EQ(intList.size(), i + 1);
  }
  for (int i = n-1; i >= 0; --i) {
    EXPECT_EQ(intList.front(), i);
    intList.pop_front();
  }
}

TEST(ForwardListTest, modifyViaFront) {
  ForwardList intList {1, 2, 3, 4};
  intList.front() = -1;
  EXPECT_EQ(intList.front(), -1);
  intList.pop_front();
  intList.front() = 23;
  EXPECT_EQ(intList.front(), 23);
}

TEST(ForwardListTest, displayInts) {
  ForwardList intList {1, 2, 3};
  testing::internal::CaptureStdout();
  intList.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "1 2 3");
}

TEST(ForwardListTest, displayAndModifyInts) {
  ForwardList intList {1, 2, 3};
  intList.front() = 10;
  testing::internal::CaptureStdout();
  intList.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "10 2 3");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
