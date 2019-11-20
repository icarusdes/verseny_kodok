#include <gtest/gtest.h>
#include "minimath.h"

TEST(DivisionTest, SimpleTest)
{
  MiniMath mm;
  EXPECT_EQ(1.66667, mm.div(5,3));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
