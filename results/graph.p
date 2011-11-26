#!/usr/bin/gnuplot
reset
set terminal png

#set xlabel library
#set xlabel "time"

set ylabel "micro second"
set yrange[0:10000]
#set yrange [0:31]

set title "cpp json performance"
#set key reverse Left outside
set grid

#set style data linespoints



set boxwidth 1 relative
set style data histograms
set style fill solid 1.0 border -1
plot "results.dat" using 2:xticlabels(1) title 'parsing', "results.dat" using 3:xticlabels(1) title 'writing'
