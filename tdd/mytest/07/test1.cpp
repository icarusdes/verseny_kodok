#include <iostream>
#include <gtest/gtest.h>
#include "minimath.h"


TEST(MiniMath, gcd)
{
  MiniMath mm;
  EXPECT_EQ(1, mm.gcd(9,16) );
  EXPECT_EQ(4, mm.gcd(12,8) );
  EXPECT_EQ(5, mm.gcd(15,10) );
}

TEST(MiniMath, mutPrime)
{
  EXPECT_TRUE(MiniMath::mutPrime(9,16) );
  EXPECT_FALSE(MiniMath::mutPrime(12,8) );
  EXPECT_TRUE(MiniMath::mutPrime(3*5,2*5) ); // should fail
}

TEST(MiniMath, mutPrimePred)
{
  EXPECT_PRED2(MiniMath::mutPrime, 9,16);
  EXPECT_PRED2(MiniMath::mutPrime,12, 8);
  EXPECT_PRED2(MiniMath::mutPrime,3*5,2*5);
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
