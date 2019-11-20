#include <gtest/gtest.h>
#include "minimath.h"

TEST(FactorialTest, withPositiveNumbers)
{
  MiniMath mm;
  ASSERT_EQ(120, mm.factorial(5));
  ASSERT_EQ(6, mm.factorial(3));
}

TEST(FactorialTest, withZero)
{
  MiniMath mm;
  ASSERT_EQ(1, mm.factorial(0));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
