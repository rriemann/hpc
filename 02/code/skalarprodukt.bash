#!/bin/bash
# skalarprodukt.bash - Leistungsmessung Skalarprodukt

#------------------------------------------------------------------------------
      CC='gcc -O3'  # GNU-Compiler
      CC='icc -O3'  # Intel-Compiler
      CC='pgcc -O3' # PGI-Compiler
#------------------------------------------------------------------------------

set -u

r=1
tmpfile=skalarprodukt.TMP
echo "$(hostname) -- $(date)"

for i in 4 
do

echo 
echo "**** skalarprodukt$i ****"

make "CC=$CC" skalarprodukt$i

##for n in 10000000 1000000 100000 10000 1000 100 10 1 
for n in 1 10 100 1000 10000 100000 1000000 10000000
do

case $n in
    1|10|100|1000|10000) 
              r=1000 ;;
    100000)   r=100 ;;
    1000000)  r=10 ;;
    10000000) r=1 ;;
esac

printf "%8i %4i " $n $r

for i in 0 1 2 3 4 5 6 7 8 9
do
    ./a.out $n $r > $tmpfile

    awk '/Rechenleistung/ {printf "%7.1f", $3}' $tmpfile 

done
echo
done
done

rm $tmpfile

exit

