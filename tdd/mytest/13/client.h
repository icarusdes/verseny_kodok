#ifndef CLIENT_H
#define CLIENT_H

class Client
{
public:
  Client(Configurator &cfg) : _cfg(cfg) {};
  virtual ~Client() {}

  void setParamX(int n);
  void incParamXBy(int n);
  int getParamX();
private:
  Configurator & _cfg;
};

#endif /* CLIENT_H */
