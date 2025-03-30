#include "common.h"

#include <math.h>
#include <stdlib.h>

double abs_complex(complex number) {
    return sqrt(pow(number.real, 2) + pow(number.imag, 2));
}

double *create_linear_space(double min, double max, int size) {
    double step = ((double)(max - min)) / size;
    double *space = malloc(sizeof(double) * size);

    for (int i = 0; i < size; i++) {
        space[i] = min + (i * step);
    }
    return space;
}

double *create_2d_linear_space(int width, int height) {
    return malloc(sizeof(double) * width * height);
}

complex complex_squared(complex number) {
    complex squared;
    squared.real = pow(number.real, 2) - pow(number.imag, 2);
    squared.imag = 2 * number.real * number.imag;
    return squared;
}

int *create_iterations_space(int width, int height) {
    return (int *)malloc(sizeof(int) * width * height);
}