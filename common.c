#include <math.h>
#include "common.h"

double complex_absolute_value(complex complex_number)
{
    return sqrt((complex_number.real) + (complex_number.imag));
}