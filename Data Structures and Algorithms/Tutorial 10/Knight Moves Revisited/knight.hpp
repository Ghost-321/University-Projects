#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include <iostream>
#include <vector>
#include <map>

namespace Knight {
struct Point {
  int x {};
  int y {};
  auto operator<=>(const Point& other) const = default;
  Point operator+(const Point& other) const {
    return {x + other.x, y + other.y};
  }
};

struct DistanceAndPoint {
  int heurDist {};
  int realDist {};
  Point p;
  auto operator<=>(const DistanceAndPoint& other) const = default;
};

  std::vector<Point> minKnightMoves(const Point& dest);
}     // namespace Knight

#endif      // KNIGHT_HPP_
