#include "minimath.h"

int MiniMath::factorial(int n)
{
  int res = 1;
  for(int i=2; i<=n; ++i)
    res *= i;
  return res;

}

int MiniMath::gcd(int a, int b)
{
  while( a != b )
  {
    if( a > b )
      a -= b;
    else
      b -= a;
  }
  return a;
}

bool MiniMath::mutPrime(int a, int b)
{
  MiniMath mm;
  return 1 == mm.gcd( a, b);
}
