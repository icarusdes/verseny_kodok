#include <gtest/gtest.h>
#include "minimath.h"

TEST(DivisionTest, FloatTest)
{
  MiniMath mm;
  EXPECT_FLOAT_EQ(1.66667, mm.div(5,3));
}

TEST(DivisionTest, DoubleTest)
{
  MiniMath mm;
  EXPECT_DOUBLE_EQ(1.66667, mm.div(5,3));
}

TEST(DivisionTest, NearTest)
{
  MiniMath mm;
  EXPECT_NEAR(1.66667, mm.div(5,3), 0.0001);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
