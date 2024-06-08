#include <gtest/gtest.h>
#include <iostream>
#include "fibonacci.hpp"
#include "stopwatch.hpp"

// Tests of iterativeFibonacci
TEST(fibTest, iterOnZero) {
  EXPECT_EQ(iterativeFibonacci(0), 0);
}

TEST(fibTest, iterOnOne) {
  EXPECT_EQ(iterativeFibonacci(1), 1);
}

TEST(fibTest, iterOnTwo) {
  EXPECT_EQ(iterativeFibonacci(2), 1);
}

TEST(fibTest, iterOnThree) {
  EXPECT_EQ(iterativeFibonacci(3), 2);
}

TEST(fibTest, iterOnFour) {
  EXPECT_EQ(iterativeFibonacci(4), 3);
}

TEST(fibTest, iterOnFive) {
  EXPECT_EQ(iterativeFibonacci(5), 5);
}

TEST(fibTest, iterOnSix) {
  EXPECT_EQ(iterativeFibonacci(6), 8);
}

TEST(fibTest, iterOnTen) {
  EXPECT_EQ(iterativeFibonacci(10), 55);
}

// Tests of recursiveFibonacci
TEST(fibTest, recursiveOnZero) {
  EXPECT_EQ(recursiveFibonacci(0), 0);
}

TEST(fibTest, recursiveOnOne) {
  EXPECT_EQ(recursiveFibonacci(1), 1);
}

TEST(fibTest, recursiveOnTwo) {
  EXPECT_EQ(recursiveFibonacci(2), 1);
}

TEST(fibTest, recursiveOnThree) {
  EXPECT_EQ(recursiveFibonacci(3), 2);
}

TEST(fibTest, recursiveOnFour) {
  EXPECT_EQ(recursiveFibonacci(4), 3);
}

TEST(fibTest, recursiveOnFive) {
  EXPECT_EQ(recursiveFibonacci(5), 5);
}

TEST(fibTest, recursiveOnSix) {
  EXPECT_EQ(recursiveFibonacci(6), 8);
}

TEST(fibTest, recursiveOnTen) {
  EXPECT_EQ(recursiveFibonacci(10), 55);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  // Our suggestion is to first get your code 
  // passing all the tests, and then you can 
  // play with seeing how long it takes to run.
  // we provide a (commented out) example of how to use 
  // the stopwatch.
  /*
  const int n {30};
  // Constructor starts the timer.
  Stopwatch clock {};
  int64_t result1 = recursiveFibonacci(n);
  // default call to elapsed gives time in milliseconds.
  uint64_t recursiveTime = clock.elapsed();
  std::cout << "Time for recursive is " << recursiveTime << 
    " milliseconds\n";
  // you can also manually start the clock with the start function
  clock.start();
  int64_t result2 = iterativeFibonacci(n);
  // get elapsed time in nanoseconds
  uint64_t iterTime = clock.elapsed<Stopwatch::nanoseconds>();
  std::cout << "Time for iterative is " << iterTime << " nanoseconds\n";
  // use the values so compiler doesn't omit the computation
  std::cout << result1 << ' ' << result2 << '\n';
  */
  return RUN_ALL_TESTS();
}
