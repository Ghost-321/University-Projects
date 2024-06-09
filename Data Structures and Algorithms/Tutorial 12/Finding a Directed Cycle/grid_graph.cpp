#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include "grid_graph.hpp"

// construct empty grid graph
GridGraph::GridGraph(int m, int n) :
  adjList {std::vector<std::unordered_set<int> >(m * n)},
  numRows {m},
  numCols {n} {}


void GridGraph::addEdge(int a, int b) {
  if (a >= 0 && b >= 0 && a < numVertices() && b < numVertices()) {
    adjList.at(a).insert(b);
  }
}

void GridGraph::addEdge(std::pair<int, int> a, std::pair<int, int> b) {
  addEdge(pairToInt(a), pairToInt(b));
}

bool GridGraph::isEdge(int a, int b) const {
  if (a < 0 || b < 0 || a >=  numVertices() || b >= numVertices()) {
    return false;
  }
  return adjList.at(a).contains(b);
}

bool GridGraph::isEdge(std::pair<int, int> a, std::pair<int, int> b) const {
  return isEdge(pairToInt(a), pairToInt(b));
}

int GridGraph::numVertices() const {
  return numRows * numCols;
}

std::unordered_set<int> GridGraph::neighbours(int a) const {
  return adjList.at(a);
}

int GridGraph::pairToInt(const std::pair<int, int>& p) const {
  return p.first * numCols + p.second;
}

std::pair<int, int> GridGraph::intToPair(int a) const {
  return {a/numCols, a % numCols};
}

// Member functions for DirectedCycle

DirectedCycle::DirectedCycle() = default;

// helper function to construct vertices on a cycle if we find one.
std::vector<std::pair<int, int> >
DirectedCycle::createCycle(int first, int last, const GridGraph& G) const {
  std::vector<std::pair<int, int> > outputCycle {};
  for (int current = last; current != first;
                          current = arrivedFrom.at(current)) {
    outputCycle.push_back(G.intToPair(current));
  }
  outputCycle.push_back(G.intToPair(first));
  std::reverse(outputCycle.begin(), outputCycle.end());
  return outputCycle;
}

std::vector<std::pair<int, int> > DirectedCycle::getCycle() const {
  return cycle;
}

bool DirectedCycle::dfsVisit(int p, const GridGraph& G) {
  onStack.at(p) = true;
  visited.at(p) = true;
  for (int neighbour : G.neighbours(p)) {
    if (onStack.at(neighbour)) {
      cycle = createCycle(neighbour, p, G);
      return true;
    }
    if (!visited.at(neighbour)) {
      arrivedFrom[neighbour] = p;
      bool existsCycle = dfsVisit(neighbour, G);
      if (existsCycle) {
        return true;
      }
    }
  }
  // as dfsVisit(p) ends p goes off the stack
  onStack.at(p) = false;
  return false;
}

bool DirectedCycle::containsCycle(const GridGraph& G) {
  visited = std::vector<bool>(G.numVertices());
  arrivedFrom.clear();
  for (int i = 0; i < G.numVertices(); ++i) {
    if (!visited.at(i)) {
      // clear onStack for each running of dfsVisit
      onStack = std::vector<bool> (G.numVertices());
      onStack.at(i) = true;
      bool existsCycle = dfsVisit(i, G);
      if (existsCycle) {
        return true;
      }
    }
  }
  return false;
}
