#include <gtest/gtest.h>
#include "minimath.h"

TEST(FactorialTest, cleanupResource)
{
  MiniMath mm;
  ASSERT_EXIT( mm.factorial(-1),
               [](int code){ return ((code>0) && (code<55));},
               "Negative input");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



