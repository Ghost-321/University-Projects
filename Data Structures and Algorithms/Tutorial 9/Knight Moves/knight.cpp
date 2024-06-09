#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include "knight.hpp"

// definitions of helper functions on Points
bool operator==(const Point& a, const Point& b) {
  return a.x == b.x and a.y == b.y;
}

bool operator<(const Point& a, const Point& b) {
  return a.x < b.x or (a.x == b.x and a.y < b.y);
}

Point operator+(const Point& a, const Point& b) {
  return {a.x + b.x, a.y + b.y};
}

// global variable to hold how a knight can move
const std::vector<Point> moves { {2, 1}, {2, -1}, {1, 2}, 
  {1, -2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };

// optional
// helper function to output a path once we have found it
// std::vector<Point>
// outputPath(const Point& dest, const std::map<Point, Point>& prev) {
// }

std::vector<Point> minKnightMoves(const Point& dest) {
  return {};
}
