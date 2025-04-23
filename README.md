# Mandelbrot

This repository keeps a **Mandelbrot** set implementation in `C`.
It holds two versions of **Mandelbrot**, in _serial_ and in _parallel_ with **OpenMP** specification.

## Structure

- `serial.c`: contains the code for executing the mandelbrot in serial, i.e., single thread
- `parallel.c` contains the code for executing the mandelbrot in parallel
- `common.h`: contains the definition of functions used both for serial and parallel codes
- `common.c`: contains the `commons.h` implementations
- `Makefile`: contains the rules for build both serial and parallel executables
- `run-experiments.sh`: a script for helping executing parallel code for different situations.
- `inputs/`: folder containing inputs examples, can be used both for serial and parallel version
- `analysis/`: folder containing analysis code and charts generations

## Building

### Serial

Run:

```bash
make build-serial
```

### Parallel

```bash
make build-parallel
```

## Input:

In `inputs` folder there are some examples for running the mandelbrot generation.
It column in the input file represents a required information for running the generation:

- **width**: the width of the plane in **x direction** in pixels (the image will be rendered with this width)
- **height**: the height of the plane in **y direction** in pixels (the image will be rendered with this height)
- **xMin**: the min value of x in complex plane
- **xMax**: the max value of x in complex plane
- **yMin**: the min value of y in complex plane
- **yMax**: the max value of y in complex plane
- **maxIterations**: the max number of iterations for the mandelbrot
- **numberOfThreads**: the number of threads when executing in parallel (has no effect when running in serial)

You can feed the application by running:

```bash
cat inputs/8k.txt | ./serial
```

Or:

```bash
cat inputs/8k.txt | ./parallel
```

## Output:

A PNG file will be rendered in folder the application is running.

Default filename: `mandelbrot.png`

_NOTE: The image will be overwritten in consecutive runs_

## Requirements

- An **OpenMP** capable hardware
- `libpng`: for rendering the mandelbrot result (update when tested and validated)
