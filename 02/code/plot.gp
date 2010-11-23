#!/usr/bin/gnuplot
# kate: encoding utf8
#set terminal pdfcairo enhanced solid size 3,3 lw 2
set terminal postscript solid
#set terminal postscript portrait enhanced solid color/monochrome
#set terminal pdfcairo enhanced color
#set size ratio 0.71 #a4
#set size 0.6
set size ratio 1
#set encoding utf8
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
set grid xtics mytics ytics
#set tmargin 0
#set rmargin 0.0
set key right
#set xtics 0.25
#set mxtics 2
set mxtics 5
set mytics 5


set key box
set key left
set logscale xy
set pointsize 1.5
set xlabel "Vektorlänge N"
set ylabel "Rechenleistung [MFlop/s]"

#N S gcc gcc(0) gcc(3) icc icc(0) icc(3) pgcc pgcc(0) pgcc(3)
#1 2 3   4      5      6   7      8      9    10      11

set output "../tmp/step4_gcc.ps"
plot "../data/data.dat" using 1:( $2==4 ? $3 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==4 ? $4 : 1/0 ) pt 147 t "gcc -O0", "" using 1:( $2==4 ? $5 : 1/0 ) pt 70 t "gcc -O3"

set output "../tmp/step4_icc.ps"
plot "../data/data.dat" using 1:( $2==4 ? $6 : 1/0 ) pt 2 t "icc", "" using 1:( $2==4 ? $7 : 1/0 ) pt 147 t "icc -O0", "" using 1:( $2==4 ? $8 : 1/0 ) pt 70 t "icc -O3"

set output "../tmp/step4_pgcc.ps"
plot "../data/data.dat" using 1:( $2==4 ? $9 : 1/0 ) pt 2 t "pgcc", "" using 1:( $2==4 ? $10 : 1/0 ) pt 147 t "pgcc -O0", "" using 1:( $2==4 ? $11 : 1/0 ) pt 70 t "pgcc -O3"


set key left bottom
set output "../tmp/gcc_o0.ps"
plot "../data/data.dat" using 1:( $2==1 ? $3 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $3 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $3 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $3 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $3 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $3 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $3 : 1/0 ) pt 74 t "stride 64"

# trenner

#