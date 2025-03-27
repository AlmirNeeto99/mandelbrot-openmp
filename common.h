typedef struct complex
{
    double real;
    double imag;
} complex;

double complex_modulus(complex complex_number);
double *create_linear_space(double min, double max, int size);
double *create_2d_linear_space(int width, int height);