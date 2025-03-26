GCC=gcc

LINK=-lm
PARALLEL_LINK=$(LINK) -fopenmp

DEPS=common.c

build-serial: serial.c $(DEPS)
	$(GCC) $(DEPS) serial.c -o serial $(LINK)


build-parallel: parallel.c $(DEPS)
	$(GCC) $(DEPS) parallel.c -o parallel $(PARALLEL_LINK)

clean:
	rm serial