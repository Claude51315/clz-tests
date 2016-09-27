CC=gcc
CFLAG=-O0 -Wall -pg -g
REPEAT=20


EXECUTABLES= binary_search_clz \
			 recursive_clz \
			 iterate_clz 
all: astyle binary_search_clz recursive_clz iterate_clz

binary_search_clz: binary_search_clz.c 
	${CC} ${CFLAG} binary_search_clz.c -o binary_search_clz
recursive_clz: recursive_clz.c
	${CC} ${CFLAG} recursive_clz.c -o recursive_clz
iterate_clz: iterate_clz.c
	${CC} ${CFLAG} iterate_clz.c -o iterate_clz
.phony: clean bench astyle

clean:
	-rm -f ${EXECUTABLES} gmon.out origin_data.txt
bench: binary_search_clz recursive_clz iterate_clz
	perf stat --repeat ${REPEAT} -e cycles ./binary_search_clz
	perf stat --repeat ${REPEAT} -e cycles ./recursive_clz
	perf stat --repeat ${REPEAT} -e cycles ./iterate_clz
astyle: binary_search_clz.c recursive_clz.c iterate_clz.c
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none \
		binary_search_clz.c recursive_clz.c iterate_clz.c
