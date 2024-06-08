#include <gtest/gtest.h>
#include "factorial.hpp"

TEST(factorialTest, factorialOf0is1) {
  EXPECT_EQ(factorial(0), 1);
}

TEST(factorialTest, factorialOf1is1) {
  EXPECT_EQ(factorial(1), 1);
}

TEST(factorialTest, factorialOf2is2) {
  EXPECT_EQ(factorial(2), 2);
}

TEST(factorialTest, factorialOf3is6) {
  EXPECT_EQ(factorial(3), 6);
}


TEST(factorialTest, factorial4is24) {
  EXPECT_EQ(factorial(4), 24);
}

TEST(factorialTest, factorialOf5is120) {
  EXPECT_EQ(factorial(5), 120);
}

TEST(factorialTest, factorialOf6is720) {
  EXPECT_EQ(factorial(6), 720);
}

TEST(factorialTest, factorialOf7is5040) {
  EXPECT_EQ(factorial(7), 5040);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
