// Struct to represent a complex number
typedef struct complex {
    double real;
    double imag;
} complex;

/**
 * @brief Computes the square of a complex number.
 *
 * @param number The complex number to be squared.
 * @return The square of the input complex number.
 */
complex complex_squared(complex number);
/**
 * @brief Computes the magnitude of a complex number.
 *
 * @param number A complex number
 * @return The magnitude of the given complex number.
 */
double abs_complex(complex number);

/**
 * @brief Creates a linearly spaced array of double values.
 *
 * @param min The starting value of the linear space.
 * @param max The ending value of the linear space.
 * @param size The number of elements in the linear space.
 * @return A pointer to the array containing the linearly spaced values.
 */
double *create_linear_space(double min, double max, int size);
/**
 * @brief Allocates memory for a 2D space to store iteration counts.
 *
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @return A pointer to the allocated memory block
 */
int *create_iterations_space(int width, int height);
/**
 * @brief Logs the details of an experiment to a CSV file and prints the elapsed
 * time.
 *
 * @param numberOfThreads The number of threads used in the experiment.
 * @param maxNumberOfIterations The maximum number of iterations performed.
 * @param elapsedTime The time elapsed during the experiment, in seconds.
 */
void logExperiment(int numberOfThreads, int maxNumberOfIterations,
                   double elapsedTime);

int save_result_to_png(const char *fileName, int *iterations, int width,
                       int height, int maxIterations);