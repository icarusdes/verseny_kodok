
#include "lib.h"

int libfn1()
{
    int a =5;
    a++;
    return (a);
}

int libfn2( int b)
{
    if (b>10)
    {
        libfn1();
        return(b);
    }
    else
        return(0);
}

