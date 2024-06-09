#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.hpp"

TEST(DijkstraTest, distanceFrom0Tiny) {
  Graph G {"tinyEWD.txt"};
  std::vector<double> result = singleSourceShortestPaths(G, 0);
  EXPECT_DOUBLE_EQ(result[0], 0);
  EXPECT_DOUBLE_EQ(result[1], 1.05);
  EXPECT_DOUBLE_EQ(result[2], 0.26);
  EXPECT_DOUBLE_EQ(result[3], 0.99);
  EXPECT_DOUBLE_EQ(result[4], 0.38);
  EXPECT_DOUBLE_EQ(result[5], 0.73);
  EXPECT_DOUBLE_EQ(result[6], 1.51);
  EXPECT_DOUBLE_EQ(result[7], 0.6);
}

TEST(DijkstraTest, distanceFrom0Medium) {
  Graph G {"mediumEWD.txt"};
  std::vector<double> result = singleSourceShortestPaths(G, 0);
  EXPECT_DOUBLE_EQ(result[0], 0);
  EXPECT_NEAR(result[1], 0.71178, 0.01);
  EXPECT_NEAR(result[2], 0.65237, 0.01);
  EXPECT_NEAR(result[3], 0.46262, 0.01);
  EXPECT_NEAR(result[4], 0.42292, 0.01);
  EXPECT_NEAR(result[5], 0.31728, 0.01);
  EXPECT_NEAR(result[47], 1.05899, 0.01);
  EXPECT_NEAR(result[149], 0.09659, 0.01);
  EXPECT_NEAR(result[247], 0.87806, 0.01);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
