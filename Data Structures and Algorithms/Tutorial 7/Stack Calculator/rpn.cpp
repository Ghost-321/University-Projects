#include <iostream>
#include <vector>
#include <algorithm>
#include "rpn.hpp"

// TODO: This function has no error checking to deal with
// badly formed expressions.  This can cause heap buffer overflow.
int evalRPN(const std::vector<char>& tokens) {
  if (tokens.empty()) {
    return 0;
  }
  std::vector<int> stack;
  for (char token : tokens) {
    if (std::isdigit(token)) {
      stack.push_back(static_cast<int>(token - '0'));
    } else {
      int second = stack.back();
      stack.pop_back();
      int first = stack.back();
      stack.pop_back();
      if (token == '+') {
        stack.push_back(first + second);
      } else if (token == '*') {
        stack.push_back(first * second);
      } else if (token == '-') {
        stack.push_back(first - second);
      } else if (token == '/') {
        stack.push_back(first / second);
      } else {
          std::cout << "invalid token\n";
      }
    }
  }
  return stack.back();
}
