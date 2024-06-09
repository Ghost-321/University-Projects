#ifndef IS_EDGE_HPP
#define IS_EDGE_HPP

// simple struct to hold a maze position
struct Point {
  int row {};
  int col {};
};

// determine if two points are equal
bool operator==(const Point& x, const Point& y);

// determine if two points are different
bool operator!=(const Point& x, const Point& y);

// add two points together
Point operator+(const Point& x, const Point& y);

bool isEdge(const std::vector<std::string>&, const Point&, const Point&);

#endif    // IS_EDGE_HPP
