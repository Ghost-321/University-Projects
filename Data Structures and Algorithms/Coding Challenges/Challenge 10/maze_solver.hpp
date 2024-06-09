#ifndef MAZE_SOLVER_HPP_
#define MAZE_SOLVER_HPP_

#include <vector>
#include <string>
#include "point.hpp"

// find the shortest path in the maze from start to finish
std::vector<std::string> solveMaze(const std::vector<std::string>& maze, 
  const Point& start, const Point& finish);

#endif    // MAZE_SOLVER_HPP_
