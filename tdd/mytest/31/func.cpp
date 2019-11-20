#ifndef LONGFUNC_H
#define LONGFUNC_H

#include <thread>
#include <chrono>

int long_function(int i)
{
  if ( i < 0 )
  {
    for(;;);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(i));
  return i;
}
#endif /* LONGFUNC_H */
