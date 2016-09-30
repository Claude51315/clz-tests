reset
set ylabel 'cycles'
set title 'numerical distribution'
set style fill solid
set term png enhanced font 'Verdana,10'
set output 'dist.png'
set format x "%10.0f"
set xtic 2000
set xtics rotate by 45 right
set tmargin 2

plot [:][:300] 'binary.txt' using 1:2 with points title 'binary', \
'iterate.txt' with points title 'iterate',\
'recursive.txt' with points title 'recursive',\
'harley.txt' with points title 'harley',\
'byteshift.txt' with points title 'byteshift'

