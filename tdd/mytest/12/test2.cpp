
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "painter.h"
#include "mock_turtle.h"

using ::testing::AtLeast;
using ::testing::Ge;                     
using ::testing::InSequence;
using ::testing::_;
using ::testing::NiceMock;

TEST(PainterTest, PenDownBeforeDraw) 
{
  NiceMock<MockTurtle> turtle;                          
  EXPECT_CALL(turtle, PenDown())              
      .Times(AtLeast(1));

  Painter painter(&turtle);                   

  EXPECT_TRUE(painter.DrawLine(10));
}                                            

TEST(PainterTest, XwithZigzag) 
{
  NiceMock<MockTurtle> turtle;                          
  EXPECT_CALL(turtle, Forward(Ge(2)))              
      .Times(AtLeast(3));
 
  Painter painter(&turtle);                   

  EXPECT_TRUE(painter.DrawZigzag(4));
}  

TEST(PainterTest, DrawLineSequence) 
{
  MockTurtle turtle;      
  {
    InSequence dummy;                    
    EXPECT_CALL(turtle, PenDown());              
    EXPECT_CALL(turtle, Forward(_));              
    EXPECT_CALL(turtle, PenUp());              
  }
 
  Painter painter(&turtle);                   
  painter.DrawLine(4);
}  

int main(int argc, char** argv) 
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
