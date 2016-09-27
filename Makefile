CC=gcc
CFLAG=-O0 -Wall -pg -g
REPEAT=20


EXECUTABLES= binary_search_clz \
			 recursive_clz \
			 iterate_clz \
			 calculate
all: astyle plot
.phony: clean bench astyle

binary_search_clz: binary_search_clz.c 
	${CC} ${CFLAG} binary_search_clz.c -o binary_search_clz
recursive_clz: recursive_clz.c
	${CC} ${CFLAG} recursive_clz.c -o recursive_clz
iterate_clz: iterate_clz.c
	${CC} ${CFLAG} iterate_clz.c -o iterate_clz



clean:
	-rm -f ${EXECUTABLES} gmon.out origin_data.txt output.txt plot.png
bench: binary_search_clz recursive_clz iterate_clz
	perf stat --repeat ${REPEAT} -e cycles ./binary_search_clz
	perf stat --repeat ${REPEAT} -e cycles ./recursive_clz
	perf stat --repeat ${REPEAT} -e cycles ./iterate_clz
output.txt: bench calculate.c
	${CC} calculate.c -o calculate
	./calculate ${REPEAT}
plot: output.txt
	gnuplot plot.gp
astyle: binary_search_clz.c recursive_clz.c iterate_clz.c calculate.c
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none \
		binary_search_clz.c recursive_clz.c iterate_clz.c calculate.c
