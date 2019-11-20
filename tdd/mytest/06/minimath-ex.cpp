#include "minimath.h"
#include <iostream>
#include <exception>

int MiniMath::factorial(int n)
{
  if ( n < 0 )
  {
    std::cerr << "Negative input" << std::endl;
    throw Error();
  }
  int res = 1;
  for(int i=2; i<=n; ++i)
    res *= i;
  return res;
}

double MiniMath::div( double x, double y)
{
  return x/y;
}


