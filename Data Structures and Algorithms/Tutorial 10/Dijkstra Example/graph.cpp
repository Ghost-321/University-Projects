#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <limits>
#include "graph.hpp"

Graph::Graph(int N) : adjList(N), numVertices {N} {}

Graph::Graph(const std::string& inputFile) {
  std::ifstream infile {inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // first line has number of vertices
  infile >> numVertices;
  adjList.resize(numVertices);
  int i {};
  int j {};
  double weight {};
  // assume each remaining line is of form
  // origin dest weight
  while (infile >> i >> j >> weight) {
    addEdge(i, j, weight);
  }
}

void Graph::addEdge(int i, int j, double weight) {
  // check vertices are valid
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    adjList.at(i).insert({j, weight});
  }
}

int Graph::size() const {
  return numVertices;
}

std::ostream& operator<<(std::ostream& out, const Graph& G) {
  for (int i = 0; i < G.size(); ++i) {
    out << i << ':';
    for (const auto& [neighbour, weight] : *(G.neighbours(i))) {
      out << " (" << i << ", " << neighbour << ")[" << weight << ']';
    }
    out << '\n';
  }
  return out;
}

// A struct to hold the distance to a vertex and the name of the vertex
// This is the type we can use in our priority queue
// The dist member variable comes first so this will be the first
// thing compared by operator< or operator>.  Ties are broken
// by the name of the vertex.
struct DistAndVertex {
  double dist {};
  int v {};
  auto operator<=>(const DistAndVertex& other) const = default;
};

// alias the long name for a minimum priority queue holding
// objects of type DistAndVertex
using minPQ = std::priority_queue<DistAndVertex,
                                  std::vector<DistAndVertex>,
                                  std::greater<DistAndVertex> >;

std::vector<double> singleSourceShortestPaths(const Graph& G, int source) {
  // Our priority queue will store {distance, vertex} pairs.
  // we give pairs of this type the name DistAndVertex for clarity 
  using DistAndVertex = std::pair<double, int>;
  // now we want a minimum priority queue holding type DistAndVertex
  // we shorten this super long type name to minPQ
  using minPQ = std::priority_queue<DistAndVertex,
                                  std::vector<DistAndVertex>,
                                  std::greater<DistAndVertex> >;
  // Ah, now that is nice and simple
  minPQ queue {};
  // Distance to the source is 0
  queue.push({0.0, source});
  // record best distance to vertex found so far
  std::vector<double> bestDistanceTo(G.size(),
                                    std::numeric_limits<double>::infinity());
  bestDistanceTo.at(source) = 0;
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::vector<bool> visited(G.size());
  while (!queue.empty()) {
    auto [dist, current] = queue.top();
    queue.pop();
    // as we use a lazy version of Dijkstra a vertex can appear multiple
    // times in the queue.  If we have already visited the vertex we
    // take out of the queue we just go on to the next one
    if (visited[current]) {
      continue;
    }
    visited[current] = true;
    // relax all outgoing edges of current
    for (const auto& [neighbour, weight] : *G.neighbours(current)) {
      double distanceViaCurrent = bestDistanceTo.at(current) + weight;
      if (bestDistanceTo.at(neighbour) > distanceViaCurrent) {
        bestDistanceTo.at(neighbour) = distanceViaCurrent;
        // lazy dijkstra: nextPoint could already be in the queue
        // we don't update it with better distance just found.
        queue.push({distanceViaCurrent, neighbour});
      }
    }
  }
  return bestDistanceTo;
}
