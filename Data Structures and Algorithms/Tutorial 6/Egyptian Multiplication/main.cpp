#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include "rec.hpp"

TEST(MultiplyTest, multiplicationTable) {
  const int N = 30;
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      EXPECT_EQ(multiply(i, j), i * j);
    }
  }
}

TEST(PowerTest, powerTable) {
  const int N = 10;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      EXPECT_EQ(power(i, j), std::pow(i, j));
    }
  }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
