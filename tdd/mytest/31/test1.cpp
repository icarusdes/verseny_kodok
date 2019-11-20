#include <iostream>
#include <gtest/gtest.h>

#include "timeout.h"

#include "func.h"


TEST(Timeout, NoTimeoutOk)
{
  TEST_TIMEOUT_BEGIN
    EXPECT_EQ(10, long_function(10));
  TEST_TIMEOUT_FAIL_END(1000)
}



TEST(Timeout, Timeout)
{
  TEST_TIMEOUT_BEGIN
    EXPECT_EQ(42, long_function(5000));
  TEST_TIMEOUT_FAIL_END(1000)
}



TEST(Timeout, NoTimeoutBadReturn)
{
  TEST_TIMEOUT_BEGIN
    EXPECT_EQ(40, long_function(100));
  TEST_TIMEOUT_FAIL_END(1000)
}

TEST(Timeout, Eternity)
{
  TEST_TIMEOUT_BEGIN
    EXPECT_EQ(40, long_function(-1));
  TEST_TIMEOUT_FAIL_END(1000)
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
