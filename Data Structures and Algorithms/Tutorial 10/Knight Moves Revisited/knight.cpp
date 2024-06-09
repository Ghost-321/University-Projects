#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include "knight.hpp"

// moves a knight can make
const std::vector<Knight::Point> moves
  { {2, 1}, {2, -1}, {1, 2}, {1, -2},
    {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };

// helper function to output a path once we have found it
std::vector<Knight::Point>
outputPath(const Knight::Point& last,
            const std::map<Knight::Point, Knight::Point>& prev) {
  std::vector<Knight::Point> path {};
  for (Knight::Point current = last; current != Knight::Point {0, 0};
                              current = prev.at(current)) {
    path.push_back(current);
  }
  path.push_back({0, 0});
  std::reverse(path.begin(), path.end());
  return path;
}

// return a lower bound on the number of knight moves from a to b
// lazy way to take ceiling of a/2 for non-negative number a:
// ceil(a/2) == (a+1)/2
int heuristic(Knight::Point a, Knight::Point b) {
  return std::max(std::abs(a.x - b.x) + 1, std::abs(a.y - b.y) + 1)/2;
}

using minPQ = std::priority_queue<Knight::DistanceAndPoint,
                                  std::vector<Knight::DistanceAndPoint>,
                                  std::greater<Knight::DistanceAndPoint> >;

std::vector<Knight::Point> Knight::minKnightMoves(const Knight::Point& dest) {
  // min priority queue ordered by heuristic distance
  minPQ pointQueue {};
  pointQueue.push({ heuristic({0, 0}, dest), 0, {0, 0} });
  // record the edgeTo relation. We reach v from prev(v)
  // updates when we find a better path to the point
  std::map<Point, Point> prev {};
  // records shortest distance to point found so far
  // if not in map then shortest distance found is infinity
  std::map<Point, int> bestDistanceTo { {{0, 0}, heuristic({0, 0}, dest)} };
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::set<Point> visited {};
  while (!pointQueue.empty()) {
    DistanceAndPoint current = pointQueue.top();
    pointQueue.pop();
    if (visited.contains(current.p)) {
      continue;
    }
    visited.insert(current.p);
    if (current.p == dest) {
      return outputPath(current.p, prev);
    }
    // relax all neighbours
    for (auto move : moves) {
      Point nextPoint = current.p + move;
      DistanceAndPoint next {current.realDist + 1 + heuristic(nextPoint, dest),
                              current.realDist + 1, nextPoint};
      if (!bestDistanceTo.contains(next.p) ||
          next.heurDist < bestDistanceTo.at(next.p)) {
        bestDistanceTo[next.p] = next.heurDist;
        prev[next.p] = current.p;
        // lazy dijkstra: nextPoint could already be in the queue
        // we don't update it with better distance just found.
        pointQueue.push(next);
      }
    }
  }
  return {};
}
