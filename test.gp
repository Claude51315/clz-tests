reset
set ylabel 'time(nsec)'
set title 'binary clz '
set style fill solid
set term png enhanced font 'Verdana,10'
set output 'test.png'
set multiplot layout 3,1 title 'comparison'
set tmargin 2

set title "binary"
unset key
plot [:][:10000] 'binary.txt'  title 'execution time (ns)' with histogram

set title "iterate"
unset key
plot [:][:10000] 'iterate.txt'  title 'execution time (ns)' with histogram

set title "recursive"
unset key
plot [:][:10000] 'recursive.txt'  title 'execution time (ns)' with histogram
unset multiplot
