#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

// amount of distinct numbers appear in the vector
// E.g. A digit can only appear once like {2,2,2} = 1 versus {1,2,2} = 2 verus {1,2,3} = 3
// Algorithm should run in O(n log n)


int numberOfDistinctElements(const std::vector<int>& vec) {
  std::vector<int> sortVec = vec;
  std::sort(sortVec.begin(), sortVec.end());
  auto vecUnique = std::unique(sortVec.begin(), sortVec.end());
  return std::distance(sortVec.begin(), vecUnique);
}
