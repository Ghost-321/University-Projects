#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "single_number.hpp"

// Only the digit that appears once
// e.g. 3, 2, 3, 2, 5 [5 should return]
// No empty vectors
// Runs in 0(n log n)
// Re-coding as cannot pass a few testcases 

int singleNumber(const std::vector<int>& vec) {

  if (vec.size() == 1) {
    return vec[0];
  }

  std::vector<int> sortedVec = vec;
  std::sort(sortedVec.begin(), sortedVec.end());

  if (sortedVec[0] != sortedVec[1]) {
    return sortedVec[0];
  }


  for (size_t i = 1; i < sortedVec.size() - 1; ++i) {
    if (sortedVec[i] != sortedVec[i-1] && sortedVec[i] != sortedVec[i + 1]) {
      return sortedVec[i];
    }
  }
  return sortedVec.back();

 // This code passed the mark test cases but failed the run test cases previously set-forth so altered it.
 // std::vector<int> vCopy = vec;
  //std::sort(vCopy.begin(), vCopy.end());
  //for (size_t i = 0; i < vCopy.size(); i += 2) {
   // if (i == vCopy.size() - 1 || vCopy[i] != vCopy[i+1]) {
    //  return vCopy[i];
    //}
  //}
  //return -1;

}
