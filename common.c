#include "common.h"

#include <math.h>
#include <png.h>
#include <stdio.h>
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

complex complex_squared(complex number) {
    complex squared;
    squared.real = pow(number.real, 2) - pow(number.imag, 2);
    squared.imag = 2 * number.real * number.imag;
    return squared;
}

int *create_iterations_space(int width, int height) {
    return (int *)malloc(sizeof(int) * width * height);
}

void logExperiment(int width, int height, int numberOfThreads,
                   int maxNumberOfIterations, double elapsedTime) {
    printf("-> Elapsed time: %lf\n", elapsedTime);

    FILE *experimentFile = fopen("experiments.csv", "a");

    if (!experimentFile) {
        printf("-> Unable to open experiment file.\n");
        return;
    }

    fprintf(experimentFile, "%d,%d,%d,%d,%lf\n", width, height, numberOfThreads,
            maxNumberOfIterations, elapsedTime);
    fclose(experimentFile);
}

int save_result_to_png(const char *fileName, int *iterationsSpace, int width,
                       int height, int maxIterations) {
    FILE *mandelbrot = fopen(fileName, "wb");
    if (!mandelbrot) {
        printf("-> Unable to open file %s for writing.\n", fileName);
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
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            color = (int)(((double)iterationsSpace[x * height + y] /
                           maxIterations) *
                          255);
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

    return 0;
}

double get_elapsed_time(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_usec - start.tv_usec) / 1000000.0;
}