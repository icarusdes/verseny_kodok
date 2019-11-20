#ifndef MOCK_CONFIGURATOR
#define MOCK_CONFIGURATOR

#include <gmock/gmock.h> 

#include "configurator.h"

class MockConfigurator : public Configurator
{
public:
  int paramX;
  int * paramX_ptr;

  MockConfigurator()
  {
    paramX = 0;
    paramX_ptr = &paramX;
  }
    
  MOCK_METHOD1(setParamX, void(int n));
  MOCK_METHOD0(getParamX, int());
};


#endif /* MOCK_CONFIGURATOR */

