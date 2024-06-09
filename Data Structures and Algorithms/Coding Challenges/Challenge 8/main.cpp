#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "is_edge.hpp"

TEST(maze, noSelfLoop) {
  std::vector<std::string> maze {
    "#####",
    "#   #",
    "#   #",
    "#####"};
  EXPECT_FALSE(isEdge(maze, {1, 1}, {1, 1}));
  EXPECT_FALSE(isEdge(maze, {2, 2}, {2, 2}));
  EXPECT_FALSE(isEdge(maze, {1, 2}, {1, 2}));
  EXPECT_FALSE(isEdge(maze, {2, 3}, {2, 3}));
  EXPECT_TRUE(isEdge(maze, {2, 3}, {2, 2}));
  EXPECT_TRUE(isEdge(maze, {2, 2}, {2, 3}));
}

TEST(maze, outOfBounds) {
  std::vector<std::string> maze {
    "## ##",
    "#   #",
    "#    ",
    "## ##"};
  EXPECT_FALSE(isEdge(maze, {0, 2}, {-1, 2}));
  EXPECT_TRUE(isEdge(maze, {0, 2}, {1, 2}));
  EXPECT_FALSE(isEdge(maze, {2, 4}, {2, 5}));
  EXPECT_TRUE(isEdge(maze, {2, 4}, {2, 3}));
  EXPECT_FALSE(isEdge(maze, {3, 2}, {4, 2}));
  EXPECT_TRUE(isEdge(maze, {3, 2}, {2, 2}));
  EXPECT_TRUE(isEdge(maze, {2, 2}, {3, 2}));
}

TEST(maze, noEdgeWithWall) {
  std::vector<std::string> maze {
    "########",
    "# #    #",
    "#   #  #",
    "########"};
  EXPECT_FALSE(isEdge(maze, {1, 1}, {1, 2}));
  EXPECT_FALSE(isEdge(maze, {2, 5}, {2, 4}));
  EXPECT_FALSE(isEdge(maze, {1, 4}, {2, 5}));
  EXPECT_FALSE(isEdge(maze, {0, 1}, {0, 2}));
  EXPECT_TRUE(isEdge(maze, {2, 6}, {2, 5}));
  EXPECT_TRUE(isEdge(maze, {1, 6}, {1, 5}));
}

TEST(maze, rowVsCol) {
  std::vector<std::string> maze {
    "## ##",
    "#   #",
    "#    ",
    "## ##"};
  EXPECT_TRUE(isEdge(maze, {1, 2}, {0, 2}));
  EXPECT_FALSE(isEdge(maze, {2, 1}, {2, 0}));
}

TEST(maze, edgesOnBorder) {
  std::vector<std::string> maze {
    "##  #",
    "#   #",
    "#    ",
    "## # "};
  EXPECT_TRUE(isEdge(maze, {0, 3}, {0, 2}));
  EXPECT_TRUE(isEdge(maze, {2, 4}, {3, 4}));
  EXPECT_FALSE(isEdge(maze, {3, 2}, {3, 3}));
  EXPECT_FALSE(isEdge(maze, {0, 2}, {0, 1}));
}

TEST(maze, noDiagonals) {
  std::vector<std::string> maze {
    "########",
    "# #    #",
    "#   #  #",
    "########"};
  EXPECT_FALSE(isEdge(maze, {1, 6}, {2, 5}));
  EXPECT_FALSE(isEdge(maze, {2, 2}, {1, 3}));
  EXPECT_TRUE(isEdge(maze, {2, 2}, {2, 3}));
  EXPECT_FALSE(isEdge(maze, {2, 6}, {1, 5}));
}

TEST(maze, twoHop) {
  std::vector<std::string> maze {
    "########",
    "# #    #",
    "#   #  #",
    "########"};
  EXPECT_FALSE(isEdge(maze, {1, 3}, {1, 5}));
  EXPECT_FALSE(isEdge(maze, {1, 3}, {1, 6}));
  EXPECT_TRUE(isEdge(maze, {1, 3}, {1, 4}));
  EXPECT_FALSE(isEdge(maze, {1, 6}, {3, 6}));
  EXPECT_FALSE(isEdge(maze, {1, 5}, {3, 5}));
  EXPECT_TRUE(isEdge(maze, {1, 5}, {2, 5}));
}

TEST(maze, longDistance) {
  std::vector<std::string> maze {
    "########",
    "# #    #",
    "#   #  #",
    "########"};
  EXPECT_FALSE(isEdge(maze, {1, 3}, {3, 2}));
  EXPECT_FALSE(isEdge(maze, {1, 3}, {2, 6}));
  EXPECT_FALSE(isEdge(maze, {1, 3}, {-1, 4}));
  EXPECT_FALSE(isEdge(maze, {1, 5}, {3, 6}));
  EXPECT_FALSE(isEdge(maze, {7, 5}, {3, 2}));
  EXPECT_TRUE(isEdge(maze, {2, 2}, {2, 3}));
}

TEST(maze, fourByFive) {
  std::vector<std::string> maze {
    "#####",
    "# # #",
    "# # #",
    "#####"};
  EXPECT_TRUE(isEdge(maze, {1, 1}, {2, 1}));
  EXPECT_TRUE(isEdge(maze, {2, 1}, {1, 1}));
  EXPECT_FALSE(isEdge(maze, {1, 1}, {0, 1}));
  EXPECT_FALSE(isEdge(maze, {1, 1}, {1, 2}));
  EXPECT_FALSE(isEdge(maze, {-1, 1}, {0, 1}));
}

TEST(maze, fourByThree) {
  std::vector<std::string> maze {
    "###",
    "# #",
    "# #",
    "###"};
  EXPECT_TRUE(isEdge(maze, {1, 1}, {2, 1}));
  EXPECT_TRUE(isEdge(maze, {2, 1}, {1, 1}));
  EXPECT_FALSE(isEdge(maze, {1, 1}, {0, 1}));
  EXPECT_FALSE(isEdge(maze, {1, 1}, {1, 2}));
  EXPECT_FALSE(isEdge(maze, {-1, 1}, {0, 1}));
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
