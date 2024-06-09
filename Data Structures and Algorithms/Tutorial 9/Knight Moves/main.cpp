#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "knight.hpp"

TEST(knightTest, zeroMoves) {
  Point target {0, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 0u);
}

TEST(knightTest, oneMove) {
  Point target {1, 2};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 1u);
}

TEST(knightTest, twoMoves) {
  Point target {3, 3};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 2u);
}

TEST(knightTest, move31) {
  Point target {3, 1};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 2u);
}

TEST(knightTest, vertical2) {
  Point target {2, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 2u);
}

TEST(knightTest, vertical3) {
  Point target {3, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 3u);
}

TEST(knightTest, vertical5) {
  Point target {5, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 3u);
}

TEST(knightTest, vertical1) {
  Point target {1, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 3u);
}

TEST(knightTest, move11) {
  Point target {1, 1};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 2u);
}

TEST(knightTest, move53) {
  Point target {5, 3};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 4u);
}

TEST(knightTest, move55) {
  Point target {5, 5};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 4u);
}

TEST(knightTest, move22) {
  Point target {2, 2};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 4u);
}

TEST(knightTest, move80) {
  Point target {8, 0};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 4u);
}

TEST(knightTest, move78) {
  Point target {7, 8};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 5u);
}

TEST(knightTest, move62) {
  Point target {6, 2};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 4u);
}

TEST(knightTest, move88) {
  Point target {8, 8};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 6u);
}

TEST(knightTest, move4940) {
  Point target {-49, 40};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 31u);
}

TEST(knightTest, move4746) {
  Point target {-47, -46};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 31u);
}

TEST(knightTest, move5050) {
  Point target {50, 50};
  std::vector<Point> path = minKnightMoves(target);
  EXPECT_EQ(path.size() - 1, 34u);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
