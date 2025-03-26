# Mandelbrot

This repository keeps a **Mandelbrot** set implementation in `C`.
It holds two versions of **Mandelbrot**, in _serial_ and in _parallel_ with **OpenMP** specification.

## Building

### Serial

Run:

```bash
make build-serial
./serial
```

### Parallel

```bash
make build-parallel
./parallel
```

## Input:

TODO

## Output:

TODO

## Requirements

- An **OpenMP** capable hardware
- **PROBABLY** `libpng`: for rendering the mandelbrot result (update when tested and validated)
