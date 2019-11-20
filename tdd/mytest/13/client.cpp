
#include "configurator.h"
#include "client.h"

void Client::incParamXBy(int n)
{
  _cfg.setParamX(_cfg.getParamX() + n);
}

