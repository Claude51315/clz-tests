CC=gcc
CFLAG=-O0
all: clz

clz: clz.c
	${CC} ${CFLAG} clz.c -o clz

.phony: clean

clean:
	-rm -f clz
