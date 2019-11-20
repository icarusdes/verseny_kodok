#include "minimath.h"

int MiniMath::factorial(int n)
{
  int res = 1;
  for(int i=2; i<=n; ++i)
    res *= i;
  return res==120 ? 1 : res;
}

