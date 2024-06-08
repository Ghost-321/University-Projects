#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "kth_largest.hpp"

TEST(KthLargest, largest) {
  std::vector<int> vec {6, 2, 4, 7, 1, 9, 6};
  EXPECT_EQ(kthLargest(vec, 1),
    *max_element(vec.begin(), vec.end()));
}

TEST(KthLargest, smallest) {
  std::vector<int> vec {6, 2, 4, 7, 1, 9, 6};
  EXPECT_EQ(kthLargest(vec, static_cast<int>(vec.size())),
    *min_element(vec.begin(), vec.end()));
}

TEST(KthLargest, secondLargestIsDuplicate) {
  std::vector<int> vec {9, 3, 6, 2, 9, 8, 1};
  EXPECT_EQ(kthLargest(vec, 2), 9);
}

TEST(KthLargest, fifthLargest) {
  std::vector<int> vec {9, 3, 6, 2, 9, 8, 1};
  EXPECT_EQ(kthLargest(vec, 5), 3);
}

TEST(KthLargest, fifthLargestRepeats) {
  std::vector<int> vec {9, 3, 8, 3, 6, 6, 2, 9, 8, 1};
  EXPECT_EQ(kthLargest(vec, 5), 6);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
