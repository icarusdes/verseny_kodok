#ifndef PAINTER_H
#define PAINTER_H

#include "turtle.h"

class Painter
{
public:
  Painter( Turtle *trt);
  bool DrawCircle(int x, int y, int r);
private:
  Turtle *turtle; 
};

#endif /* PAINTER_H */
