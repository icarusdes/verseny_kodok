
#include "painter.h"

Painter::Painter( Turtle *trt) : turtle(trt) { } 

bool Painter::DrawLine( int len)
{
  turtle->PenDown();
  turtle->Forward(len);
  turtle->PenUp();
  return true;    
}

bool Painter::DrawZigzag(int n)
{
  turtle->PenDown();
  for (int i = 0; i < n; ++i)
  { 
    turtle->Turn(10);
    turtle->Forward(5);
  }
  return true;
}

