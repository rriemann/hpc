#!/usr/bin/gnuplot
# kate: encoding utf8
set terminal pdfcairo enhanced solid size 4,4 lw 2
set size ratio 1
set encoding utf8
set grid xtics mytics ytics
set key box
set key right top
set mxtics 5
set mytics 5
set logscale x
set logscale y
set pointsize 1
set xlabel "Nachrichtenlänge N"
set ylabel "Rechenleistung [MFlop/s]"
#set yrange [0:1400]

set output "../../tmp/2processes1core.pdf"
plot "../../data/data.dat" using 1:2 pt 2 t "2 Prozesse, 1 Knoten", "" using 1:3 pt 147 t "2 Prozesse, 2 Knoten", "" using 1:4 pt 70 t "4 Prozesse, 1 Knoten", "" using 1:5 pt 71 t "4 Prozesse, 2 Knoten"
