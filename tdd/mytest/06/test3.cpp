#include <gtest/gtest.h>
#include "minimath.h"

TEST(FactorialTest, withPositiveNumbers)
{
  MiniMath mm;
  EXPECT_EQ(120, mm.factorial(5));
  EXPECT_EQ(  6, mm.factorial(3));
  EXPECT_EQ(  1, mm.factorial(1));
}

TEST(FactorialTest, withNegative1)
{
  MiniMath mm;
  ASSERT_DEATH( mm.factorial( 0),"");
}

TEST(FactorialTest, withNegative2)
{
  MiniMath mm;
  ASSERT_DEATH( mm.factorial(-1),"");
}

TEST(FactorialTest, withNegative3)
{
  MiniMath mm;
  ASSERT_DEATH( mm.factorial(-1),"");
}

TEST(FactorialTest, withNegative4)
{
  MiniMath mm;
  ASSERT_DEATH( mm.factorial(-1),"Negative input");
}


TEST(FactorialTest, withZero)
{
  MiniMath mm;
  EXPECT_EQ(1, mm.factorial(0));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



