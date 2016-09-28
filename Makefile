CC=gcc
CFLAG=-O0 -Wall -pg -g
COMMON= main.c clz.h
REPEAT=20

EXECUTABLES=binary_search_clz \
			recursive_clz \
			iterate_clz \
			byte_shift_clz
all: astyle plot
exec: ${EXECUTABLES}

.phony: clean bench astyle

binary_search_clz: ${COMMON} binary_search_clz.c 
	${CC} ${CFLAG} -Dbinary main.c $@.c -o $@
recursive_clz: ${COMMON} recursive_clz.c
	${CC} ${CFLAG} -Drecursive main.c $@.c -o $@
iterate_clz: ${COMMON} iterate_clz.c
	${CC} ${CFLAG} -Diterate main.c  $@.c -o $@
byte_shift_clz: ${COMMON} byte_shift_clz.c
	${CC} ${CFLAG} -Dbyteshift main.c  $@.c -o $@
clean:
	-rm -f ${EXECUTABLES} calculate gmon.out *.txt plot.png
bench: ${EXECUTABLES}
#	echo 1 | sudo tee /proc/sys/vm/drop_caches	
	perf stat --repeat ${REPEAT} -e cycles ./binary_search_clz
	perf stat --repeat ${REPEAT} -e cycles ./recursive_clz
	perf stat --repeat ${REPEAT} -e cycles ./iterate_clz
	perf stat --repeat ${REPEAT} -e cycles ./byte_shift
#	perf stat --repeat ${REPEAT} -e cycles ./harley_clz
output.txt: bench calculate.c
	${CC} calculate.c -o calculate
	./calculate ${REPEAT}
plot: output.txt
	gnuplot plot.gp
astyle: 
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.c *.h
