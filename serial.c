#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int main()
{

    complex c;

    c.real = 5.4;
    c.imag = 8.0;

    printf("-> Real: %lf <-> Imag: %lf\n", c.real, c.imag);
    printf("-> Absolute value: %lf\n", complex_absolute_value(c));

    return 0;
}