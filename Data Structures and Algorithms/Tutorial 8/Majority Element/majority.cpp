#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "majority.hpp"

// Hash Map 
// "Average Case" time Theta(n) and space Theta(n)
int majorityElement(const std::vector<int>& vec) {
  std::unordered_map<int, unsigned> counts;
  for (int x : vec) {
    ++counts[x];
  } 
  for (const auto& [num, count] : counts) {
    if (count > vec.size()/2) {
      return num;
    }
  }
  // some default value
  return 0;
}

// Boyer-Moore Majority Vote algorithm
// Works in time Theta(n) and space Theta(1)
int majorityElement(const std::vector<int>& vec) {
  if (vec.empty()) {
    return 0;
  }
  // default initialisations
  int candidate = 0;
  int count = 0;
  for (int x : vec) {
    if (count == 0) {
      candidate = x;
    }
    if (x == candidate) {
      ++count;
    } else {
      --count;
    }
  }
  return candidate;
}
