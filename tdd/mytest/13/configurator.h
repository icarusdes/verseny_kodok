#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

class Configurator
{
public:
  virtual ~Configurator() {}

  virtual void setParamX(int n) = 0;
  virtual int getParamX() = 0;
};

#endif /* CONFIGURATOR_H */
