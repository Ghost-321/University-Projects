#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

class Graph {
 private:
  std::vector<std::unordered_map<int, double> > adjList {};
  int numVertices {};

 public:
  // create an empty graph with N vertices
  explicit Graph(int N);

  // construct graph from edge list in filename
  explicit Graph(const std::string& filename);

  void addEdge(int i, int j, double weight);
  int size() const;

  // alias a const iterator to our adjacency list type to iterator
  using iterator = 
  std::vector<std::unordered_map<int, double> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator neighbours(int a) const {
    return adjList.begin() + a;
  }
};

std::vector<double> singleSourceShortestPaths(const Graph& G, int source);

#endif      // GRAPH_HPP_
