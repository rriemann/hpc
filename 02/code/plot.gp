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
set pointsize 1
set xlabel "Vektorlänge N"
set ylabel "Rechenleistung [MFlop/s]"
set yrange [0:1400]

#N S gcc gcc(0) gcc(3) icc icc(0) icc(3) pgcc pgcc(0) pgcc(3)
#1 2 3   4      5      6   7      8      9    10      11

set output "../tmp/step4_gcc.pdf"
plot "../data/data.dat" using 1:( $2==4 ? $3 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==4 ? $4 : 1/0 ) pt 147 t "gcc -O0", "" using 1:( $2==4 ? $5 : 1/0 ) pt 70 t "gcc -O3"

set output "../tmp/step4_icc.pdf"
plot "../data/data.dat" using 1:( $2==4 ? $6 : 1/0 ) pt 2 t "icc", "" using 1:( $2==4 ? $7 : 1/0 ) pt 147 t "icc -O0", "" using 1:( $2==4 ? $8 : 1/0 ) pt 70 t "icc -O3"

set output "../tmp/step4_pgcc.pdf"
plot "../data/data.dat" using 1:( $2==4 ? $9 : 1/0 ) pt 2 t "pgcc", "" using 1:( $2==4 ? $10 : 1/0 ) pt 147 t "pgcc -O0", "" using 1:( $2==4 ? $11 : 1/0 ) pt 70 t "pgcc -O3"

set output "../tmp/s01_o3.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $5 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==1 ? $8 : 1/0 ) pt 147 t "icc", "" using 1:( $2==1 ? $11 : 1/0 ) pt 70 t "pgcc"

set output "../tmp/s64_o3.pdf"
plot "../data/data.dat" using 1:( $2==64 ? $5 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==64 ? $8 : 1/0 ) pt 147 t "icc", "" using 1:( $2==64 ? $11 : 1/0 ) pt 70 t "pgcc"

set output "../tmp/s01_o0.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $4 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==1 ? $7 : 1/0 ) pt 147 t "icc", "" using 1:( $2==1 ? $10 : 1/0 ) pt 70 t "pgcc"

set output "../tmp/s64_o0.pdf"
plot "../data/data.dat" using 1:( $2==64 ? $4 : 1/0 ) pt 2 t "gcc", "" using 1:( $2==64 ? $7 : 1/0 ) pt 147 t "icc", "" using 1:( $2==64 ? $10 : 1/0 ) pt 70 t "pgcc"

########################### gcc

set output "../tmp/gcc_o.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $3 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $3 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $3 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $3 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $3 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $3 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $3 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/gcc_o0.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $4 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $4 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $4 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $4 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $4 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $4 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $4 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/gcc_o3.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $5 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $5 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $5 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $5 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $5 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $5 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $5 : 1/0 ) pt 74 t "stride 64"

########################### icc

set output "../tmp/icc_o.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $6 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $6 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $6 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $6 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $6 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $6 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $6 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/icc_o0.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $7 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $7 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $7 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $7 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $7 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $7 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $7 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/icc_o3.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $8 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $8 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $8 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $8 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $8 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $8 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $8 : 1/0 ) pt 74 t "stride 64"

############################ pgcc

set output "../tmp/pgcc_o.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $9 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $9 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $9 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $9 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $9 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $9 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $9 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/pgcc_o0.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $10 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $10 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $10 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $10 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $10 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $10 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $10 : 1/0 ) pt 74 t "stride 64"

set output "../tmp/pgcc_o3.pdf"
plot "../data/data.dat" using 1:( $2==1 ? $11 : 1/0 ) pt 2 t "stride 1", "" using 1:( $2==2 ? $11 : 1/0 ) pt 147 t "stride 2", "" using 1:( $2==4 ? $11 : 1/0 ) pt 70 t "stride 4", "" using 1:( $2==8 ? $11 : 1/0 ) pt 151 t "stride 8", "" using 1:( $2==16 ? $11 : 1/0 ) pt 148 t "stride 16", "" using 1:( $2==32 ? $11 : 1/0 ) pt 146 t "stride 32", "" using 1:( $2==64 ? $11 : 1/0 ) pt 74 t "stride 64"