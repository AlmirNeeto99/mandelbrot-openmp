typedef struct complex {
    double real;
    double imag;
} complex;

complex complex_squared(complex number);
double abs_complex(complex number);
double *create_linear_space(double min, double max, int size);
double *create_2d_linear_space(int width, int height);

int *create_iterations_space(int width, int height);