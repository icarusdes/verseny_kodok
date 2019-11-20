#include <gtest/gtest.h>
#include "minimath.h"

TEST(DivisionTest, Float6digit)
{
  EXPECT_NEAR(1.6666661, 1.6666669, 1e-7);
}

TEST(DivisionTest, Float7digit)
{
  EXPECT_NEAR(1.66666661, 1.66666669, 1e-7);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
