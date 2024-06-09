#include <vector>
#include "max.hpp"

int maxValue(const std::vector<int>& vec) {
  // write your implementation here
  int max = vec[0];

  for (unsigned int i  = 1; i < vec.size(); i++) {
    if(vec[i] > max) {
      max = vec[i];
    }
  }

  return max;
}
