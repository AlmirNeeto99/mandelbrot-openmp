#include <math.h>
#include <stdlib.h>

#include "common.h"

double complex_modulus(complex complex_number)
{
    return sqrt((complex_number.real) + (complex_number.imag));
}

double *create_linear_space(double min, double max, int size)
{

    double step = ((double)(max - min)) / size;
    double *space = malloc(sizeof(double) * size);

    for (int i = 0; i < size; i++)
    {
        space[i] = min + (i * step);
    }
    return space;
}

double *create_2d_linear_space(int width, int height)
{
    return malloc(sizeof(double) * width * height);
}