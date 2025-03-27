#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int main(int argc, char *argv[])
{

    char arguments[256];

    if (fgets(arguments, sizeof(arguments), stdin) != NULL)
    {
        printf("-> Arguments: %s\n", arguments);
    }

    int width = 7680, height = 4320;

    double *space = create_2d_linear_space(100, 100);

    double *xLinearSpace = create_linear_space(-5.0, 5.0, width);
    double *yLinerSpace = create_linear_space(-5.0, 5.0, height);

    complex z, c;
    int iteration = 0;
    int max_iter = 1000000;

    double real, imag;
    double a, b;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            z.real = 0;
            z.imag = 0;
            iteration = 0;

            c.real = xLinearSpace[i];
            c.imag = yLinerSpace[j];
            while (complex_modulus(z) < 2.0 && iteration < max_iter)
            {
                real = z.real * z.real - z.imag * z.imag;
                imag = z.real * z.imag + z.imag * z.real;
                z.real = real + c.real;
                z.imag = imag + c.imag;
                iteration++;
            }
        }
    }

    FILE *mandelbrot = fopen("mandelbrot.png", "wb");

    if (!mandelbrot)
    {
        printf("Unable to open output file\n");
    }

    free(space);
    free(xLinearSpace);
    free(yLinerSpace);

    return 0;
}