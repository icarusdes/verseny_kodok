#include <iostream>

int f1()
{
    int a =5;
    a++;
    return (a);
}

int *f2( int z)
{
  int *p = nullptr;
  if ( z > 0 )
  {
    p = new int;
  }
  return p;
}

int f3( int x )
{
  throw 1;
  f1();
}

int f4( int x)
try{
    if ( x>10 && *f2(0) )
    {
        f1();
        return(x);
    }
    else if ( f3(1) && f1() )
    {
        return(0);
    }
    f1();
    return 1;
} catch (...) {}


int main ()
{
     f1();
     f2(5);
     f4(5);
}


