GCC=gcc

LINK=-lm

DEPS=common.c

build-serial: serial.c $(DEPS)
	$(GCC) $(DEPS) serial.c -o serial $(LINK) 

clean:
	rm serial