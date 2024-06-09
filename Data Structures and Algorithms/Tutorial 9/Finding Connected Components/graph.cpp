#include <iostream>
#include <vector>
#include <unordered_set>

class Graph {
 private:
  // represent the graph with a vector of sets
  std::vector<std::unordered_set<int> > vec {};
  int numVertices {};

 public:
  explicit Graph(int N) : vec {std::vector<std::unordered_set<int> >(N)},
                          numVertices {N} {}

  void addEdge(int i, int j) {
    vec.at(i).insert(j);
    vec.at(j).insert(i);
  }

  bool isEdge(int i, int j) {
    return vec.at(i).contains(j);
  }

  void adjacentTo(int v) {
    for (auto x : vec.at(v)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
  }

  void print() {
    for (int v = 0; v < numVertices; ++v) {
      std::cout << "Neighbors of " << v << ": ";
      for (auto neighbour : vec.at(v)) {
        std::cout << neighbour << ' ';
      }
      std::cout << '\n';
    }
  }

  void connectedComponents() {
    std::vector<bool> marked(numVertices);
    std::vector<std::unordered_set<int> > components {};
    for (int v = 0; v < numVertices; ++v) {
      if (not marked.at(v)) {
          // add new unordered_set to hold next connected component
          components.push_back(std::unordered_set<int> {});
          dfs(v, marked, components);
      }
    }
    // print out connected components
    std::cout << "number of components is " << components.size() << '\n';
    int componentNumber = 1;
    for (const auto& component : components) {
      std::cout << "vertices in component " << componentNumber << " are\n";
      for (auto v : component) {
        std::cout << v << ' ';
      }
      ++componentNumber;
      std::cout << '\n';
    }
  }

 private:
  void dfs(int v, std::vector<bool>& marked,
                  std::vector<std::unordered_set<int> >& components) {
    marked.at(v) = true;
    components.back().insert(v);
    for (auto u : vec.at(v)) {
      if (not marked.at(u)) {
        dfs(u, marked, components);
      }
    }
  }
};

int main() {
  // Create a connected undirected graph on 5 vertices
  Graph G(5);
  G.addEdge(1, 0);
  G.addEdge(0, 3);
  G.addEdge(2, 1);
  G.addEdge(2, 3);
  G.addEdge(3, 1);
  G.addEdge(2, 4);

  // this graph has one component with all the vertices
  G.connectedComponents();
  std::cout << '\n';

  // Create a disconnected undirected graph on 6 vertices
  Graph G2(6);
  G2.addEdge(0, 4);
  G2.addEdge(0, 5);
  G2.addEdge(4, 5);
  G2.addEdge(1, 3);
  G2.addEdge(1, 2);
  G2.addEdge(2, 3);

  // this graph has two connected components
  // one with vertices 0 4 5 and the second with vertices 1 2 3
  G2.connectedComponents();
  std::cout << '\n';

  // Create a disconnected undirected graph on 7 vertices
  Graph G3(7);
  G3.addEdge(0, 1);
  G3.addEdge(0, 6);
  G3.addEdge(2, 5);
  G3.addEdge(3, 4);

  // this graph has three connected components
  // one with vertices 0 1 6, one with 2 5, one with 3 4
  G3.connectedComponents();
  return 0;
}
