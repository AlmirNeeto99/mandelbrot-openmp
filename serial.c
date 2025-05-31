#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int main(int argc, char *argv[]) {
    struct timeval programStart, programEnd;

    int width, height, maxIterations;
    double xMin, xMax, yMin, yMax;

    scanf("%d %d %lf %lf %lf %lf %d", &width, &height, &xMin, &xMax, &yMin,
          &yMax, &maxIterations);

    printf("-> Starting mandelbrot generation\n");
    printf("-> Resolution: %dx%d\n", width, height);
    printf("-> Complex plane limit (x): [%lf, %lf]\n", xMin, xMax);
    printf("-> Complex plane limit (y): [%lf, %lf]\n", yMin, yMax);
    printf("-> Max number of iterations: %d\n", maxIterations);

    int *iterationsSpace = create_iterations_space(width, height);

    double *xLinearSpace = create_linear_space(xMin, xMax, width);
    double *yLinearSpace = create_linear_space(yMin, yMax, height);

    complex z, c;
    int iterations = 0;
    short int escaped = 0;

    gettimeofday(&programStart, NULL);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            escaped = 0;
            iterations = 0;

            z.real = 0;
            z.imag = 0;

            c.real = xLinearSpace[i];
            c.imag = yLinearSpace[j];

            while (iterations < maxIterations) {
                if (abs_complex(z) > 2) {
                    escaped = 1;
                    break;
                }
                z = complex_squared(z);

                z.real = z.real + c.real;
                z.imag = z.imag + c.imag;

                iterations++;
            }

            iterationsSpace[j + i * height] = escaped ? iterations : 0;
        }
    }

    gettimeofday(&programEnd, NULL);

    // logExperiment(0, maxIterations, get_elapsed_time(programStart,
    // programEnd));

    const char *outputName = "mandelbrot.png";

    save_result_to_png(outputName, iterationsSpace, width, height,
                       maxIterations);

    free(iterationsSpace);
    free(xLinearSpace);
    free(yLinearSpace);

    return 0;
}
