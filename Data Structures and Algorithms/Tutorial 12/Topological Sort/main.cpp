#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#include "topo.hpp"

// generic function to print out elements of a container
// thanks C++20!
void print(const auto& container) {
  for (const auto& x : container) {
    std::cout << x << ' ';
  }
}

// check that an ordering is a topological sort
// if there is an edge (order[i], order[j]) then must have i < j
void checkOrder(const std::vector<std::string>& order, const Graph& G) {
  for (Graph::iterator vertexIt = G.begin();
                        vertexIt != G.end(); ++vertexIt) {
    auto vertexPosition = std::find(order.begin(), order.end(),
                                    vertexIt->first);
    for (const std::string& neighbour : vertexIt->second) {
      auto neighbourPosition = std::find(order.begin(), order.end(),
                                          neighbour);
      // compare the iterators
      EXPECT_LE(vertexPosition, neighbourPosition);
    }
  }
}

TEST(TopoTest, triangle) {
  // A->B, A->C, B->C
  Graph G;
  G.addEdge("A", "B");
  G.addEdge("A", "C");
  G.addEdge("B", "C");
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  // should be A B C
  print(order);
  std::cout << '\n';
}

TEST(TopoTest, smallGraph) {
  Graph G {"small.txt"};
  // look at the graph
  std::cout << G << '\n';
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  print(order);
  std::cout << '\n';
}

TEST(TopoTest, AI) {
  Graph G {"ai.txt"};
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  print(order);
  std::cout << '\n';
}

TEST(TopoTest, Games) {
  Graph G {"games.txt"};
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  print(order);
  std::cout << '\n';
}

TEST(TopoTest, IT) {
  Graph G {"it.txt"};
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  print(order);
  std::cout << '\n';
}

TEST(TopoTest, Enterprise) {
  Graph G {"enterprise.txt"};
  TopoOrder topo {};
  topo.computeTopoOrder(G);
  std::vector<std::string> order = topo.getOrder();
  EXPECT_EQ(order.size(), G.numVertices());
  checkOrder(order, G);
  print(order);
  std::cout << '\n';
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
