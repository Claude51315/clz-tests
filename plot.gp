reset
set ylabel 'time(sec)'
set title 'performance comparison'
set style fill solid
set term png enhanced font 'Verdana,10'
set output 'plot.png'

plot [:][:0.01] 'output.txt' using 2:xtic(1) title 'execution time (s)' with histogram, \
'' using ($0):($2+0.0001):2 with labels title ' '

