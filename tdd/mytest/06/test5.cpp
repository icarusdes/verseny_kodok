#include <gtest/gtest.h>
#include "minimath.h"


TEST(FactorialTest, notThrow)
{
  MiniMath mm;
  ASSERT_NO_THROW( mm.factorial(0) );
}

TEST(FactorialTest, throwError)
{
  MiniMath mm;
  ASSERT_THROW( mm.factorial(-1), MiniMath::Error );
}

TEST(FactorialTest, throwSomething)
{
  MiniMath mm;
  ASSERT_ANY_THROW( mm.factorial(-1) );
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



