
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock_configurator.h"
#include "client.h"

using namespace testing;

TEST(PainterTest, PenDownBeforeDraw) 
{
  MockConfigurator cfg;
  Client client(cfg);
  
  int inc_value = 10;
  
  //getParamX will be called a number of times.
  //If it is called, we will return the value pointed to by paramX_ptr.
  //Returning with ReturnPointee is necessary, since we need to have
  //the actual (updated) value each time the method is called.
  EXPECT_CALL(cfg, getParamX())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnPointee(cfg.paramX_ptr));
  
  //SaveArg stores the 0th parameter of the call in the value pointed to by paramX_ptr (paramX)
  //expectation 3
  EXPECT_CALL(cfg, setParamX(cfg.paramX + 3*inc_value))
      .Times(1)
      .WillOnce(DoAll(SaveArg<0>(cfg.paramX_ptr), Return()));
  //expectation 2
  EXPECT_CALL(cfg, setParamX(cfg.paramX + 2*inc_value))
      .Times(1)
      .WillOnce(DoAll(SaveArg<0>(cfg.paramX_ptr), Return()));
  //expectation 1
  EXPECT_CALL(cfg, setParamX(cfg.paramX + inc_value))
      .Times(1)
      .WillOnce(DoAll(SaveArg<0>(cfg.paramX_ptr), Return()));
  
  client.incParamXBy(inc_value); //this will match expectation 1
  client.incParamXBy(inc_value); //this will match expectation 2
  client.incParamXBy(inc_value); //this will match expectation 3
}  

int main(int argc, char** argv) 
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
