
#include "painter.h"

Painter::Painter( Turtle *trt) : turtle(trt) { } 

bool Painter::DrawCircle( int x, int y, int r)
{
  turtle->PenDown();
  return true;    
}

