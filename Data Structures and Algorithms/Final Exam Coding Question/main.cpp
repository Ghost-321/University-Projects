#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <random>
#include "graph.hpp"

TEST(longestLeg, distanceToSelfIsMinusInfinity) {
  Graph<int> G {2};
  G.addEdge(0, 1, 1);
  // sources vertex is 0
  std::vector<int> output = longestLegDistance(G, 0);
  // Important: the max distance from 0 to itself should be "minus infinity"
  // Use std::numeric_limits<int>::min() to represent minus infinity.
  std::vector<int> solution {std::numeric_limits<int>::min(), 1};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, unreachableDistanceIsInfinity) {
  Graph<int> G {2};
  G.addEdge(0, 1, 1);
  // sources vertex is now 1
  std::vector<int> output = longestLegDistance(G, 1);
  // 0 is not reachable from 1.  The max distance from 1 to 0 is "infinity".
  // Use std::numeric_limits<int>::max() to represent infinity.
  std::vector<int> solution {std::numeric_limits<int>::max(),
                              std::numeric_limits<int>::min()};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, allEdgeWeightsOne) {
  Graph<int> G {3};
  G.addEdge(0, 1, 1);
  G.addEdge(1, 2, 1);
  G.addEdge(2, 1, 1);
  std::vector<int> output = longestLegDistance(G, 0);
  // when all edge weights are 1 and every vertex is reachable from 0 then
  // the max distance from 0 to every other vertex will be 1
  std::vector<int> solution {std::numeric_limits<int>::min(), 1, 1};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, lineGraph) {
  Graph<int> G {8};
  G.addEdge(0, 1, 1);
  G.addEdge(1, 2, 2);
  G.addEdge(2, 3, 3);
  G.addEdge(3, 4, 4);
  G.addEdge(4, 5, 5);
  G.addEdge(5, 6, 6);
  G.addEdge(6, 7, 1);
  std::vector<int> output = longestLegDistance(G, 0);
  std::vector<int> solution
    {std::numeric_limits<int>::min(), 1, 2, 3, 4, 5, 6, 6};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, lineGraphSourceInMiddle) {
  Graph<int> G {8};
  G.addEdge(0, 1, 1);
  G.addEdge(1, 2, 2);
  G.addEdge(2, 3, 3);
  G.addEdge(3, 4, 4);
  G.addEdge(4, 5, 5);
  G.addEdge(5, 6, 6);
  G.addEdge(6, 7, 1);
  std::vector<int> output = longestLegDistance(G, 3);
  int inf = std::numeric_limits<int>::max();
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution
    {inf, inf, inf, minusInf, 4, 5, 6, 6};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, severalPathsToVertex) {
  Graph<int> G {5};
  G.addEdge(3, 4, -1);
  G.addEdge(4, 0, -2);
  G.addEdge(3, 0, 1);
  G.addEdge(0, 3, -3);
  G.addEdge(0, 1, 5);
  G.addEdge(1, 2, 2);
  G.addEdge(2, 1, 1);
  G.addEdge(4, 2, 0);
  G.addEdge(2, 4, -2);
  std::vector<int> output = longestLegDistance(G, 3);
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution {-1, 1, 0, minusInf, -1};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, sameGraphDifferentSource) {
  Graph<int> G {5};
  G.addEdge(3, 4, -1);
  G.addEdge(4, 0, -2);
  G.addEdge(3, 0, 1);
  G.addEdge(0, 3, -3);
  G.addEdge(3, 4, 4);
  G.addEdge(0, 1, 5);
  G.addEdge(1, 2, 2);
  G.addEdge(2, 1, 1);
  G.addEdge(4, 2, 0);
  G.addEdge(2, 4, -2);
  std::vector<int> output = longestLegDistance(G, 4);
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution {-2, 1, 0, -2, minusInf};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, fourVertexExample) {
  Graph<int> G {4};
  G.addEdge(0, 1, 3);
  G.addEdge(0, 2, 1);
  G.addEdge(2, 1, 2);
  G.addEdge(1, 3, 5);
  G.addEdge(2, 3, 1);
  G.addEdge(3, 2, -1);
  G.addEdge(0, 3, 4);
  std::vector<int> output = longestLegDistance(G, 0);
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution {minusInf, 2, 1, 1};
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, gridGraph) {
  Graph<int> G {10};
  std::vector<int> target {0, -5, -4, -5, -1, -2, -6, -7, -4, -6};
  G.addEdge(0, 1, target.at(1));
  G.addEdge(1, 2, target.at(2));
  G.addEdge(1, 4, target.at(4));
  G.addEdge(2, 1, target.at(1));
  G.addEdge(2, 5, target.at(5));
  G.addEdge(2, 3, target.at(3));
  G.addEdge(3, 2, target.at(2));
  G.addEdge(3, 6, target.at(6));
  G.addEdge(4, 1, target.at(1));
  G.addEdge(4, 5, target.at(5));
  G.addEdge(4, 7, target.at(7));
  G.addEdge(5, 2, target.at(2));
  G.addEdge(5, 4, target.at(4));
  G.addEdge(5, 6, target.at(6));
  G.addEdge(5, 8, target.at(8));
  G.addEdge(6, 3, target.at(3));
  G.addEdge(6, 5, target.at(5));
  G.addEdge(6, 9, target.at(9));
  G.addEdge(7, 4, target.at(4));
  G.addEdge(7, 8, target.at(8));
  G.addEdge(8, 5, target.at(5));
  G.addEdge(8, 7, target.at(7));
  G.addEdge(8, 9, target.at(9));
  G.addEdge(9, 6, target.at(6));
  G.addEdge(9, 8, target.at(8));
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution {minusInf, -5, -4, -4, -1, -2, -4, -4, -4, -4};
  std::vector<int> output = longestLegDistance(G, 0);
  EXPECT_EQ(output, solution);
}

TEST(longestLeg, gridGraph2) {
  Graph<int> G {10};
  std::vector<int> target {0, -5, 3, -10, -8, -2, -12, 2, -3, -3};
  G.addEdge(0, 1, target.at(1));
  G.addEdge(1, 2, target.at(2));
  G.addEdge(1, 4, target.at(4));
  G.addEdge(2, 1, target.at(1));
  G.addEdge(2, 5, target.at(5));
  G.addEdge(2, 3, target.at(3));
  G.addEdge(3, 2, target.at(2));
  G.addEdge(3, 6, target.at(6));
  G.addEdge(4, 1, target.at(1));
  G.addEdge(4, 5, target.at(5));
  G.addEdge(4, 7, target.at(7));
  G.addEdge(5, 2, target.at(2));
  G.addEdge(5, 4, target.at(4));
  G.addEdge(5, 6, target.at(6));
  G.addEdge(5, 8, target.at(8));
  G.addEdge(6, 3, target.at(3));
  G.addEdge(6, 5, target.at(5));
  G.addEdge(6, 9, target.at(9));
  G.addEdge(7, 4, target.at(4));
  G.addEdge(7, 8, target.at(8));
  G.addEdge(8, 5, target.at(5));
  G.addEdge(8, 7, target.at(7));
  G.addEdge(8, 9, target.at(9));
  G.addEdge(9, 6, target.at(6));
  G.addEdge(9, 8, target.at(8));
  int minusInf = std::numeric_limits<int>::min();
  std::vector<int> solution {minusInf, -5, 3, -2, -5, -2, -2, 2, -2, -2};
  std::vector<int> output = longestLegDistance(G, 0);
  EXPECT_EQ(output, solution);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
