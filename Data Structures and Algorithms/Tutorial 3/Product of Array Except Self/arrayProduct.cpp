#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include "arrayProduct.hpp"

// first solution: handle separately cases of no zeros, one zero, two zeros
// if no zeros then result[i] = (product of all values in nums)/ nums[i]
// if one zero all entries of result are zero except the one corresponding
// to the zero in nums
// if 2 or more zeros the result is the all zero vector.
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
  int numZeros = 0;
  int productWithoutZeros = 1;
  std::size_t zeroIndex = nums.size();
  // compute 
  // 1) number of non-zeros
  // 2) product of all non-zeros in nums
  // 3) index of a zero in nums, if there is one
  for (std::size_t i = 0; i < nums.size(); ++i) {
    if (nums[i] == 0) {
      ++numZeros;
      zeroIndex = i;
    } else {
      productWithoutZeros *= nums[i];
    }
  }
  // initialise result to be all zero vector 
  std::vector<int> result(nums.size());
  if (numZeros == 0) {
    for (std::size_t i = 0; i < nums.size(); ++i) {
      result[i] = productWithoutZeros/nums[i];
    }
    return result;
  }
  // when numZeros == 1, we just have to correct the 
  // entry of result corresponding to the 0 in nums
  if (numZeros == 1) {
    result[zeroIndex] = productWithoutZeros;
    return result;
  }
  // when numZeros >= 2, result (= all zero vector) is correct answer
  return result;
}

// another solution
// similar to the first, but uses some functions from the standard
// library to help out
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
  // use count function to count number of zeros
  int numZeros = std::count(nums.cbegin(), nums.cend(), 0);
  std::vector<int> result(nums.size());
  if (numZeros == 0) {
    // use accumulate to compute the product
    int prod = std::accumulate(nums.cbegin(), nums.cend(), 1, 
      std::multiplies<int>());
    for (std::size_t i = 0; i < nums.size(); ++i) {
      result[i] = prod/nums[i];
    }
    return result;
  }
  if (numZeros == 1) {
    auto zeroIt = std::find(nums.cbegin(), nums.cend(), 0);
    int prod = std::accumulate(nums.cbegin(), zeroIt, 1, 
      std::multiplies<int>());
    prod = std::accumulate(zeroIt + 1, nums.cend(), prod, 
      std::multiplies<int>());
    result[static_cast<std::size_t>(zeroIt - nums.cbegin())] = prod;
    return result;
  }
  // remaining case numZeros >= 2
  return result;
}

// another type of solution
// let productFromLeft[i] = nums[0]* ... * nums[i-1]
// let productFromRight[i] = nums[i+1]* ... * nums[size - 1]
// then results[i] = productFromLeft[i-1] * productFromRight[i+1]
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
  std::size_t N = nums.size();
  if (N <= 1) {
    return {0};
  }
  std::vector<int> productFromLeft(N);
  productFromLeft[0] = nums[0];
  for (std::size_t i = 1; i < N; ++i) {
    productFromLeft[i] = productFromLeft[i-1] * nums[i];
  }
  std::vector<int> productFromRight(N);
  productFromRight.back() = nums.back();
  for (std::size_t i = N-1; i-- > 0;) {
    productFromRight[i] = productFromRight[i+1] * nums[i];
  }
  std::vector<int> result(N);
  result[0] = productFromRight[1];
  result[N-1] = productFromLeft[N-2];
  for (std::size_t i = 1; i < N-1; ++i) {
    result[i] = productFromLeft[i-1] * productFromRight[i+1];
  }
  return result;
}
