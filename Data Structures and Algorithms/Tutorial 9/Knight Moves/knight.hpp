#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include <vector>
#include <map>

// small struct to keep x,y coordinates of board position
struct Point {
  int x {};
  int y {};
  // spaceship operator defines all comparisons for us
};

// helper functions about points
// we need to see if points are equal to see if we have reached our destination
bool operator==(const Point& a, const Point& b);

// we define a comparison operator on points so that we can use them
// as keys in a set or map.
// There is no hash function defined on points so we cannot use them as keys
// in an unordered_set or unordered_map
bool operator<(const Point& a, const Point& b);

// add two points together
// return {a.x + b.x, a.y + b.y};
Point operator+(const Point& a, const Point& b);

// main function to implement
// output a shortest path to dest
std::vector<Point> minKnightMoves(const Point& dest);

#endif      // KNIGHT_HPP_
