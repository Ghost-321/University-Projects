// you can add more includes you might
// need for your data structure
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

class Graph {
 private:
  // TODO: Add some member variables here to represent your graph

 public:
  Graph(int N, bool type) {} 

  void addEdge(int i, int j) {
  }

  bool isEdge(int i, int j) {
  }

  void adjacentTo(int v) {
  }

  void display() {
  }
};

int main() {
    // Create an undirected graph on 5 vertices
    Graph G(5, false);
    G.addEdge(1, 0);
    G.addEdge(0, 3);
    G.addEdge(2, 1);
    G.addEdge(2, 3);
    G.addEdge(3, 1);
    G.addEdge(2, 4);

    // print out all the edges
    // {0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}
    G.display();

    // print out vertices adjacent to vertex 2
    // should print out 1, 3, 4
    G.adjacentTo(2);

    std::cout << "\nNow try a directed graph\n";
    // Create a directed graph on 4 vertices
    Graph digraph(4, true);
    digraph.addEdge(1, 0);
    digraph.addEdge(0, 3);
    digraph.addEdge(2, 1);
    digraph.addEdge(2, 3);
    digraph.addEdge(3, 1);

    // print out all the edges
    // (0, 3), (1, 0), (2, 1), (2, 3), (3, 1)
    digraph.display();

    // print out the vertices out-adjacent to vertex 0
    // should print out 3
    digraph.adjacentTo(0);

    return 0;
}
