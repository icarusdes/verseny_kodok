#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <cstdlib>
#include "minimath.h"

int MiniMath::factorial(int n)
{
  if ( n < 0 )
  {
    std::cerr << "Negative input" << std::endl;
    kill( getpid(), SIGUSR1);
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


