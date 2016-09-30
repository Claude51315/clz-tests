reset
set ylabel 'cycles'
set title 'average cycle count'
set style fill solid
set term png enhanced font 'Verdana,10'
set output 'average.png'

plot [:][:1000] 'output.txt' using 2:xtic(1) title '' with histogram, \
'' using ($0):($2+0.0001):2 with labels title ' '

