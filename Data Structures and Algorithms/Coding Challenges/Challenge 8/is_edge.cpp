#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include "is_edge.hpp"

// operations on points
bool operator==(const Point& x, const Point& y) {
  return x.row == y.row and x.col == y.col;
}

bool operator!=(const Point& x, const Point& y) {
  return not (x == y);
}

Point operator+(const Point& x, const Point& y) {
  return Point {x.row + y.row, x.col + y.col};
}

bool validPoint(const Point& x, int rows, int cols) {
  if (x.row < 0 or x.row >= rows) {
    return false;
  }
  if (x.col < 0 or x.col >= cols) {
    return false;
  }
  return true;
}

// given a maze (where # denotes walls) is there an edge between Point x 
// and Point y?  For this to be true x and y have to be represent valid 
// indices into the maze, maze at these points should not be a wall, and
// y has to be one square left, up, down, or right from x
bool isEdge(const std::vector<std::string>& maze, const Point& x, 
                                                  const Point& y) {
  int numRows = static_cast<int>(maze.size());  
  int numCols = static_cast<int>(maze.at(0).size());
  if (!validPoint(x, numRows, numCols) or !validPoint(y, numRows, numCols)) {
    return false;
  }
  if (maze.at(x.row).at(x.col) != ' ' or maze.at(y.row).at(y.col) != ' ') {
    return false;
  }
  if (x.row == y.row and std::abs(x.col - y.col) == 1) {
    return true;
  } 
  if (x.col == y.col and std::abs(x.row - y.row) == 1) {
    return true;
  } 
  return false;
}


bool isEdge2(const std::vector<std::string>& maze, const Point& x, 
                                                  const Point& y) {
  int numRows = static_cast<int>(maze.size());  
  int numCols = static_cast<int>(maze.at(0).size());
  if (!validPoint(x, numRows, numCols) or !validPoint(y, numRows, numCols)) {
    return false;
  }
  if (maze.at(x.row).at(x.col) != ' ' or maze.at(y.row).at(y.col) != ' ') {
    return false;
  }
  std::vector<Point> moves = {
    Point {0, 1}, Point {0, -1}, Point {1,0}, Point {-1, 0} };
  for (const Point& move : moves) {
    if (y == x + move) {
      return true;
    }
  }
  return false;
}
