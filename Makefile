CC=gcc
CFLAG=-O0 -Wall -pg -g
COMMON= main.c clz.h
REPEAT=20
min= 100000
max= 165536
EXECUTABLES=binary_search_clz \
			recursive_clz \
			iterate_clz \
			byte_shift_clz \
			harley_clz
all: astyle exec
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
harley_clz: ${COMMON} harley_clz.c
	${CC} ${CFLAG} -Dharley main.c  $@.c -o $@

clean:
	-rm -f ${EXECUTABLES} calculate gmon.out *.txt plot.png
run: ${EXECUTABLES}
#	echo 1 | sudo tee /proc/sys/vm/drop_caches	
	-rm -f *.txt

#	perf stat --repeat ${REPEAT} -e cycles ./binary_search_clz
#	perf stat --repeat ${REPEAT} -e cycles ./recursive_clz
#	perf stat --repeat ${REPEAT} -e cycles ./iterate_clz
#	perf stat --repeat ${REPEAT} -e cycles ./byte_shift_clz
#	perf stat --repeat ${REPEAT} -e cycles ./harley_clz
	taskset -c 1 ./binary_search_clz ${min} ${max}
	taskset -c 1 ./recursive_clz ${min} ${max}
	taskset -c 1 ./iterate_clz ${min} ${max}
	taskset -c 1 ./byte_shift_clz ${min} ${max}
	taskset -c 1 ./harley_clz ${min} ${max}
output.txt: calculate.c
	${CC} calculate.c -o calculate
	./calculate ${REPEAT}
plot: output.txt
	gnuplot plot.gp
astyle: 
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.c *.h
