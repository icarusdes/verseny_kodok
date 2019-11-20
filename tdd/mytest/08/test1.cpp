#include <iostream>
#include <gtest/gtest.h>
#include "minimath.h"


class MiniMathTest : public ::testing::Test
{
protected:
  MiniMath mm;

  void SetUp() { std::cout << "Before test" << std::endl; }
  void TearDown() { std::cout << "After test" << std::endl; }

};

TEST_F(MiniMathTest, withPositiveNumbers)
{
  EXPECT_EQ(120, mm.factorial(5));
  EXPECT_EQ(6, mm.factorial(3));
}

TEST_F(MiniMathTest, withZero)
{
  EXPECT_EQ(1, mm.factorial(0));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
