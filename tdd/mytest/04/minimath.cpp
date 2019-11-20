#include <cmath>
#include "minimath.h"

int MiniMath::factorial(int n)
{
  int res = 1;
  for(int i=2; i<=n; ++i)
    res *= i;
  return res;
}

double MiniMath::div( double x, double y)
{
  return x/y;
}

