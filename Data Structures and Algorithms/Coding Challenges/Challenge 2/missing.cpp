#include <vector>
#include "missing.hpp"

// When the input vector is of size n 
// you are guaranteed that it contains all 
// of the integers 0, 1, 2, ..., n except for one.
// The goal of whoIsMissing is to return the missing number
int whoIsMissing(const std::vector<int>& vec) {
  int n = vec.size();
  int potentialSum  = n * (n + 1) / 2;

  int total = 0;
  for (int num : vec) {
    total += num;
  }

  return potentialSum - total;
}
