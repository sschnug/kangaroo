#! /bin/bash

Root=/home/hn/z/w

RunCount=1
Kangaroo=$Root/kangaroo/examples/kangaroo
Comet=$Root/comet/compiler/comet
Benchmarks=$Root/kangaroo/benchmarks
Experiments=$Root/kangaroo/experiments
Examples=$Root/kangaroo/examples

SizeStart=2000
SizeEnd=5000
SizeStep=1999

touch $Experiments/nqueen/kangaroo.dat
rm $Experiments/nqueen/kangaroo.dat
for((Size = SizeStart; Size < SizeEnd; Size+=SizeStep)); do
   for ((Run = 0; Run < RunCount; Run++)) ; do
	echo $Size $Run >> $Experiments/nqueen/kangaroo.dat
	$Kangaroo nq -n $Size -i $Size | $Benchmarks/nqueenval.out >> $Experiments/nqueen/kangaroo.dat
   done
done

touch $Experiments/nqueen/comet.dat
rm $Experiments/nqueen/comet.dat
for((Size = SizeStart; Size < SizeEnd; Size+=SizeStep)); do
   for ((Run = 0; Run < RunCount; Run++)) ; do
	echo $Run >> $Experiments/nqueen/comet.dat
	$Comet $Benchmarks/nqueen.co -n $Size -i $Size 2>/dev/null | tail -3 | $Benchmarks/nqueenval.out >> $Experiments/nqueen/comet.dat
   done
done


