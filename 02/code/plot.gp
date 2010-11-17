#!/usr/bin/gnuplot
# kate: encoding utf8
set terminal pdfcairo enhanced solid size 3,3 lw 2
#set terminal postscript portrait enhanced solid color
#set terminal pdfcairo enhanced color
set output "../tmp/similarity_vs_Hz.pdf"
#set size ratio 0.71 #a4
#set size 0.6
set size ratio 1
set encoding utf8
#set encoding iso_8859_1
#set title ""
#set xlabel "{/Symbol b}{/Symbol g}" enhanced
#set xtics 3
#set mxtics 3
#set ytics 0.5
#set mytics 4
#set grid xtics ytics mxtics mytics
#set style line 1 lt 1 lw 3
#set key left top
#set key box
set nokey
#set format x "10^{%L}"
#set xtics 0.2
set mxtics 3
set grid xtics ytics
#set tmargin 0
#set rmargin 0.0

set key box
set key left
set logscale x
set logscale y
set output "../tmp/step4_gcc.pdf"
set xlabel "Vektorlänge N"
set ylabel "Rechenleistung [MFlop/s]"
#set xtics 0.25
#set mxtics 2
#set grid mxtics ytics
set key right
plot "../data/data.dat" using 1:( $2==4 ? $3 : 1/0 ) pt 7 ps 0.5 t "gcc", "" using 1:( $2==4 ? $4 : 1/0 ) pt 8 ps 0.5 t "gcc -O0", "" using 1:( $2==4 ? $5 : 1/0 ) pt 8 ps 0.5 t "gcc -O3"
