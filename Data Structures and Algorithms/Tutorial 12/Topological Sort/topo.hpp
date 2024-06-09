#ifndef TOPO_HPP_
#define TOPO_HPP_

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

class Graph {
 private:
  std::unordered_map<std::string, std::unordered_set<std::string> > adjList {};

 public:
  // default constructor
  Graph();
  // construct graph from file
  explicit Graph(const std::string&);

  // adds strings as vertices if they are not already present
  void addEdge(const std::string&, const std::string&);
  void addVertex(const std::string&);

  bool isEdge(const std::string&, const std::string&) const;
  bool isVertex(const std::string&) const;
  std::size_t numVertices() const;

  // this time we let the user interface with the graph via a const iterator
  // const so they can't change our graph with the iterator
  using iterator = std::unordered_map<std::string,
            std::unordered_set<std::string> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator find(const std::string& a) const {
    return adjList.find(a);
  }
};

class TopoOrder {
  std::unordered_set<std::string> visited {};
  std::unordered_set<std::string> onStack {};
  std::vector<std::string> order {};
  std::vector<std::string> cycle {};
  std::unordered_map<std::string, std::string> arrivedFrom {};

 public:
  TopoOrder();
  bool computeTopoOrder(const Graph&);
  std::vector<std::string> getOrder() const;
  std::vector<std::string> getCycle() const;

 private:
  bool dfsVisit(const std::string&, const Graph&);
};

std::ostream& operator<<(std::ostream&, const Graph&);

#endif      // TOPO_HPP_
