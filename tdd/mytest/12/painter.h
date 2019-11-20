#ifndef PAINTER_H
#define PAINTER_H

#include "turtle.h"

class Painter
{
public:
  Painter( Turtle *trt);
  bool DrawLine(int len);
  bool DrawZigzag(int n);
private:
  Turtle *turtle; 
};

#endif /* PAINTER_H */
