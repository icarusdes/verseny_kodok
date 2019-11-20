#include <iostream>
#include <gtest/gtest.h>
#include "minimath.h"


::testing::AssertionResult isMutPrime( int a, int b)
{
  MiniMath mm;
  if ( MiniMath::mutPrime(a,b) )
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure() << "gcd(" << a 
                                         << "," << b << ") = "
                                         << mm.gcd(a,b) ; 
}

TEST(MiniMath, gcd)
{
  MiniMath mm;
  EXPECT_EQ(1, mm.gcd(9,16) );
  EXPECT_EQ(4, mm.gcd(12,8) );
  EXPECT_EQ(5, mm.gcd(15,10) );
}

TEST(MiniMath, mutPrime)
{
  EXPECT_TRUE(isMutPrime(9,16) );
  EXPECT_FALSE(isMutPrime(12,8) ); 
  EXPECT_TRUE(isMutPrime(3*5,2*5) ); // should fail
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
