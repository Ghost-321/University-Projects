// The Egyptian multiplication example is based on 
// "From Mathematics to Generic Programming", Chapter 2,
// by Stepanov and Rose
#include <iostream>
#include <cstdint>
#include "rec.hpp"

int multiply(int x, int y) {
  if (y == 0) {
    return 0;
  }
  int recursiveEval = multiply(x + x, y/2);
  if (y % 2 == 1) {
    recursiveEval += x;
  }
  return recursiveEval;
}

int64_t power(int64_t x, int exponent) {
  if (exponent == 0) {
    return 1;
  }
  int64_t recursiveEval = power(x * x, exponent/2);
  if (exponent % 2 == 1) {
    recursiveEval *= x;
  }
  return recursiveEval;
}
