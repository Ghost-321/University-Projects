#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "rpn.hpp"

TEST(RPNTest, returnZeroOnEmptyString) {
  std::vector<char> empty {};
  EXPECT_EQ(evalRPN(empty), 0);
}

TEST(RPNTest, addTwoNumbers) {
  std::vector<char> add {'2', '3', '+'};
  EXPECT_EQ(evalRPN(add), 5);
}

TEST(RPNTest, subtractTwoNumbers) {
  std::vector<char> tokens {'3', '5', '-'};
  EXPECT_EQ(evalRPN(tokens), -2);
}

TEST(RPNTest, multiplyByMinusOne) {
  std::vector<char> tokens {'0', '1', '-', '5', '*'};
  EXPECT_EQ(evalRPN(tokens), -5);
}

TEST(RPNTest, multiplyTwoNumbers) {
  std::vector<char> times {'2', '3', '*'};
  EXPECT_EQ(evalRPN(times), 6);
}

TEST(RPNTest, compoundTest) {
  std::vector<char> compound {'2', '3', '+', '3', '*'};
  EXPECT_EQ(evalRPN(compound), 15);
}

TEST(RPNTest, infixRequiresParentheses) {
  std::vector<char> tokens {'2', '4', '8', '+', '*'};
  EXPECT_EQ(evalRPN(tokens), 24);
}

TEST(RPNTest, withDiv) {
  std::vector<char> tokens {'4', '3', '5', '/', '+'};
  EXPECT_EQ(evalRPN(tokens), 4);
}

TEST(RPNTest, longerExpression1) {
  std::vector<char> tokens
    {'2', '5', '*', '4', '+', '3', '2', '*', '1', '+', '/'};
  EXPECT_EQ(evalRPN(tokens), 2);
}

TEST(RPNTest, longerExpression2) {
  std::vector<char> tokens
    {'8', '6', '4', '3', '-', '3', '*', '/', '*', '7', '+', '5', '+'};
  EXPECT_EQ(evalRPN(tokens), 28);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
