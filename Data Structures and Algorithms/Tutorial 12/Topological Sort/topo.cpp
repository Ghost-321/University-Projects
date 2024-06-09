#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include "topo.hpp"

// helper functions to make graph from a file

// given a string of comma separated values return a vector of the values
// "example, string, like, this" -> {"example", "string", "like", "this"}
// uses second solution from here:
// https://stackoverflow.com/questions/1894886/
// parsing-a-comma-delimited-stdstring
std::vector<std::string> parseCSV(const std::string& input) {
  if (input.empty()) {
    return {};
  }
  std::stringstream stream {input};
  std::vector<std::string> values {};
  while (stream.good()) {
    std::string value;
    // skip whitespace
    stream >> std::ws;
    // read until ','
    getline(stream, value, ',');
    values.push_back(value);
  }
  return values;
}

std::string extractNumber(const std::string& vertex) {
  std::stringstream stream {vertex};
  // read until find a number
  while (stream.good() && !isdigit(stream.peek())) {
    stream.get();
  }
  return stream.str();
}

// print out a graph
std::ostream& operator<<(std::ostream& out, const Graph& G) {
  for (Graph::iterator it = G.begin(); it != G.end(); ++it) {
    out << it->first << ':';
    for (const std::string& neighbour : it->second) {
      out << ' ' << neighbour;
    }
    out << '\n';
  }
  return out;
}

// default constructor
Graph::Graph() = default;

// construct graph from a file
Graph::Graph(const std::string& inputFile) {
  std::ifstream infile {inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // each line in the inputFile should be of the form
  // [prereq1, prereq2, ..., prereqk] course number, optional extra info
  // assume no space between course number and following comma
  std::string fullLine {};
  while (getline(infile, fullLine )) {
    std::stringstream lineStream {fullLine};
    // first character of line should be '['
    assert('[' == lineStream.peek());
    // advance past '['
    lineStream.get();
    std::string prereqString {};
    getline(lineStream, prereqString, ']');
    // extract course number
    std::string vertex {};
    lineStream >> vertex;
    // remove trailing comma
    vertex.pop_back();
    addVertex(vertex);
    // add edges from prereqs to vertex
    std::vector<std::string> prereqs = parseCSV(prereqString);
    for (const auto& prereq : prereqs) {
      addEdge(prereq, vertex);
    }
  }
}

std::size_t Graph::numVertices() const {
  return adjList.size();
}

void Graph::addVertex(const std::string& a) {
  if (!isVertex(a)) {
    adjList.insert({a, {}});
  }
}

void Graph::addEdge(const std::string& a, const std::string& b) {
  // if a or b is not already a vertex, we add them as vertices
  adjList[a].insert(b);
  if (!isVertex(b)) {
    addVertex(b);
  }
}

bool Graph::isEdge(const std::string& a, const std::string& b) const {
  if (!adjList.contains(a)) {
    return false;
  }
  return adjList.at(a).contains(b);
}

bool Graph::isVertex(const std::string& a) const {
  return adjList.contains(a);
}

TopoOrder::TopoOrder() = default;

std::vector<std::string> TopoOrder::getOrder() const {
  return order;
}

// helper function to construct vertices on a cycle if we find one.
std::vector<std::string> createCycle(const std::string& first,
      const std::string& last,
      const std::unordered_map<std::string, std::string>& prev) {
  std::vector<std::string> cycle {};
  for (std::string current = last; current != first;
                    current = prev.at(current)) {
    cycle.push_back(current);
  }
  cycle.push_back(first);
  std::reverse(cycle.begin(), cycle.end());
  return cycle;
}

std::vector<std::string> TopoOrder::getCycle() const {
  return cycle;
}

bool TopoOrder::dfsVisit(const std::string& vertex, const Graph& G) {
  onStack.insert(vertex);
  visited.insert(vertex);
  auto neighbours = G.find(vertex)->second;
  for (const std::string& neighbour : neighbours) {
    if (onStack.contains(neighbour)) {
      // there is a cycle
      cycle = createCycle(neighbour, vertex, arrivedFrom);
      return true;
    }
    if (!visited.contains(neighbour)) {
      arrivedFrom[neighbour] = vertex;
      bool existsCycle = dfsVisit(neighbour, G);
      if (existsCycle) {
        return true;
      }
    }
  }
  // going off stack
  onStack.erase(vertex);
  order.push_back(vertex);
  return false;
}

bool TopoOrder::computeTopoOrder(const Graph& G) {
  visited.clear();
  arrivedFrom.clear();
  for (Graph::iterator it = G.begin(); it != G.end(); ++it) {
    if (!visited.contains(it->first)) {
      // clear onStack for each running of dfsVisit
      onStack.clear();
      onStack.insert(it->first);
      bool existsCycle = dfsVisit(it->first, G);
      if (existsCycle) {
        return true;
      }
    }
  }
  std::reverse(order.begin(), order.end());
  return false;
}
