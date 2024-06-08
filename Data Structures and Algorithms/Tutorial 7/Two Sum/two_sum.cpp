#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "two_sum.hpp" 

std::pair<int, int>
twoSum(const std::vector<int>& vec, int target) {
  // keys: vector entries (ints), value: indices (size_t)
  std::unordered_map<int, std::size_t > partners {};
  for (std::size_t i = 0; i < vec.size(); ++i) {
    if (partners.contains(target - vec.at(i))) {
      return {partners.at(target - vec.at(i)), static_cast<int>(i)};
    }
    partners.insert({vec.at(i), i});
  }
  // because of promise should not reach here
  return {0, 0};
}
