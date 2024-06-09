#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "knight.hpp"

// analytical solution
// helper function for the case x, y >= 0 and x >= 2*y
int lessThanHalf(int x, int y) {
  // special case
  if (x == 1 && y == 0) {
    return 3;
  }
  int mod = (x - 2 * y) % 4;
  if (mod == 0) {
    return x/2;
  } else if (mod == 3) {
    return x/2 + 2;
  } else {
    // mod == 1 or mod == 2
    return x/2 + 1;
  }
}

unsigned analytical(int x, int y) {
  x = std::abs(x);
  y = std::abs(y);
  if (y > x) {
    std::swap(x, y);
  }
  if (2 * y <= x) {
    return lessThanHalf(x, y);
  }
  // k is number of steps of form (1,2) we take to reduce to
  // the lessThanHalf case
  int k = std::ceil(static_cast<float>((2 * y - x))/3);
  return static_cast<unsigned>(k + lessThanHalf(x - k, y - 2 * k));
}

TEST(knightTest, bigTest) {
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      std::vector<Knight::Point> path = Knight::minKnightMoves({i, j});
      ASSERT_EQ(path.size() - 1, analytical(i, j));
    }
  }
}

TEST(knightTest, move4940) {
  Knight::Point target {-49, 40};
  std::vector<Knight::Point> path = Knight::minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 31u);
}

TEST(knightTest, move4746) {
  Knight::Point target {-47, -46};
  std::vector<Knight::Point> path = Knight::minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 31u);
}

TEST(knightTest, move5050) {
  Knight::Point target {50, 50};
  std::vector<Knight::Point> path = Knight::minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 34u);
}

TEST(knightTest, farAway) {
  Knight::Point target {270, 21};
  std::vector<Knight::Point> path = Knight::minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 135u);
}

TEST(knightTest, evenFurtherAway) {
  Knight::Point target {300, 271};
  std::vector<Knight::Point> path = Knight::minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, analytical(300, 271));
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
