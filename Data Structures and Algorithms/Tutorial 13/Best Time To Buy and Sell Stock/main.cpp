#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include "stock.hpp"

TEST(stock, sizeOne) {
  std::vector<int> prices {5};
  EXPECT_EQ(maxProfit(prices), 0);
}

TEST(stock, sizeTwoIncreasing) {
  std::vector<int> prices {5, 8};
  EXPECT_EQ(maxProfit(prices), 3);
}

TEST(stock, sizeTwoDecreasing) {
  std::vector<int> prices {8, 5};
  EXPECT_EQ(maxProfit(prices), 0);
}

TEST(stock, notMaxMinusMin) {
  std::vector<int> prices {100, 5, 8, 3};
  EXPECT_EQ(maxProfit(prices), 3);
}

TEST(stock, buyDayOne) {
  std::vector<int> prices {3, 4, 8, 8, 4};
  EXPECT_EQ(maxProfit(prices), 5);
}

TEST(stock, sellLastDay) {
  std::vector<int> prices {6, 4, 8, 8, 6, 10};
  EXPECT_EQ(maxProfit(prices), 6);
}

TEST(stock, random0) {
  std::vector<int> prices {40, 52, 39, 85, 4, 65, 79, 97, 93, 34, 45, 59, 89, 65, 10};
  EXPECT_EQ(maxProfit(prices), 93);
}

TEST(stock, random1) {
  std::vector<int> prices {58, 51, 8, 84, 80, 41, 0, 44, 95, 52, 99, 82, 4, 40, 12};
  EXPECT_EQ(maxProfit(prices), 99);
}

TEST(stock, random2) {
  std::vector<int> prices {71, 2, 10, 43, 67, 20, 53, 32, 5, 14, 38, 36, 62, 26, 37};
  EXPECT_EQ(maxProfit(prices), 65);
}

TEST(stock, random3) {
  std::vector<int> prices {12, 41, 36, 62, 86, 71, 34, 90, 85, 14, 26, 7, 31, 91, 29};
  EXPECT_EQ(maxProfit(prices), 84);
}

TEST(stock, random4) {
  std::vector<int> prices {61, 40, 15, 4, 75, 91, 35, 34, 41, 23, 56, 4, 78, 55, 57};
  EXPECT_EQ(maxProfit(prices), 87);
}

TEST(stock, random5) {
  std::vector<int> prices {69, 62, 15, 78, 11, 68, 14, 28, 0, 41, 95, 72, 58, 86, 55};
  EXPECT_EQ(maxProfit(prices), 95);
}

TEST(stock, random6) {
  std::vector<int> prices {49, 33, 7, 26, 45, 0, 45, 77, 94, 21, 57, 58, 55, 11, 49};
  EXPECT_EQ(maxProfit(prices), 94);
}

TEST(stock, random7) {
  std::vector<int> prices {52, 81, 64, 57, 36, 59, 22, 89, 24, 74, 2, 41, 25, 79, 87};
  EXPECT_EQ(maxProfit(prices), 85);
}

TEST(stock, random8) {
  std::vector<int> prices {33, 14, 59, 4, 3, 54, 96, 42, 63, 82, 75, 29, 1, 25, 59};
  EXPECT_EQ(maxProfit(prices), 93);
}

TEST(stock, random9) {
  std::vector<int> prices {66, 16, 46, 20, 93, 32, 82, 83, 22, 53, 69, 6, 7, 41, 48};
  EXPECT_EQ(maxProfit(prices), 77);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
