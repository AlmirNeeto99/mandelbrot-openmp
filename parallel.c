#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "png.h"

int main(int argc, char *argv[]) {
    int width, height, maxIterations, numThreads;
    double xMin, xMax, yMin, yMax;

    scanf("%d %d %lf %lf %lf %lf %d %d", &width, &height, &xMin, &xMax, &yMin,
          &yMax, &maxIterations, &numThreads);

    printf("-> Starting mandelbrot generation in \"Parallel\"\n");
    printf("-> Resolution: %dx%d\n", width, height);
    printf("-> Complex plane limit (x): [%lf, %lf]\n", xMin, xMax);
    printf("-> Complex plane limit (y): [%lf, %lf]\n", yMin, yMax);
    printf("-> Max number of iterations: %d\n", maxIterations);
    printf("-> Number of Threads: %d\n", numThreads);

    int *iterationsSpace = create_iterations_space(width, height);

    double *xLinearSpace = create_linear_space(xMin, xMax, width);
    double *yLinearSpace = create_linear_space(yMin, yMax, height);

    int grainSize = 100;
    int currentPos = 0;

    double programStart = omp_get_wtime();

#pragma omp parallel num_threads(numThreads) shared(currentPos)

    {
        double start = omp_get_wtime();
        int num = omp_get_thread_num();

        int myPos = 0;
        while (1) {
#pragma omp critical
            {
                myPos = currentPos++;
            }
            if ((myPos + 1) * grainSize >= width) break;

            complex z, c;
            int iterations = 0;
            short int escaped = 0;
            for (int i = grainSize * myPos; i < grainSize * (myPos + 1); i++) {
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

                    iterationsSpace[i * height + j] = escaped ? iterations : 0;
                }
            }
        }

        double end = omp_get_wtime();
        printf("\t-> Thread #%d done in %.6f seconds!\n", num, end - start);
    }

    double programEnd = omp_get_wtime();

    FILE *results = fopen("experiments.csv", "a");

    if (!results) {
        printf("Unable to write results!");
    } else {
        fprintf(results, "%d,%d,%lf\n", numThreads, maxIterations,
                programEnd - programStart);
        fclose(results);
    }

    const char *outputName = "mandelbrot.png";

    FILE *mandelbrot = fopen(outputName, "wb");

    if (!mandelbrot) {
        printf("Unable to open %s file\n", outputName);
        return -1;
    }

    png_structp png =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(mandelbrot);
        return -1;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(mandelbrot);
        return -1;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(mandelbrot);
        return -1;
    }

    png_set_compression_level(png, 0);
    png_init_io(png, mandelbrot);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    png_bytep row = (png_bytep)malloc(3 * width * sizeof(png_byte));

    int color = 0;
    double proportion = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            proportion =
                (double)iterationsSpace[x * height + y] / maxIterations;
            color = (int)(proportion * 255);
            row[x * 3] = color;      // Red
            row[x * 3 + 1] = color;  // Green
            row[x * 3 + 2] = color;  // Blue
        }
        png_write_row(png, row);
    }
    free(row);

    png_write_end(png, NULL);
    png_destroy_write_struct(&png, &info);

    fclose(mandelbrot);

    free(iterationsSpace);
    free(xLinearSpace);
    free(yLinearSpace);

    return 0;
}