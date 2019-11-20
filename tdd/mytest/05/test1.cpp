#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>

TEST(StringTest, Expect_Eq)
{
  double d = 5./3.;
  std::ostringstream s;
  s << std::setprecision(6) << d;
  EXPECT_EQ("1.66667", s.str());
}

TEST(StringTest, Expect_StringEq)
{
  double d = 5./3.;
  std::ostringstream s;
  s << std::setprecision(6) << d;
  EXPECT_STREQ("1.66667", s.str().c_str());
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
