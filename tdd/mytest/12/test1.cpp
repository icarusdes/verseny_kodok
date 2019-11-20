
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "painter.h"
#include "mock_turtle.h"

using ::testing::AtLeast;
using ::testing::Ge;                     

TEST(PainterTest, PenDownBeforeDraw) 
{
  MockTurtle turtle;                          
  EXPECT_CALL(turtle, PenDown())              
      .Times(AtLeast(1));

  Painter painter(&turtle);                   

  EXPECT_TRUE(painter.DrawLine(10));
}                                            

TEST(PainterTest, XwithZigzag) 
{
  MockTurtle turtle;                          
  EXPECT_CALL(turtle, Forward(Ge(2)))              
      .Times(AtLeast(3));
  
  Painter painter(&turtle);                   

  EXPECT_TRUE(painter.DrawZigzag(4));
}  

int main(int argc, char** argv) 
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
