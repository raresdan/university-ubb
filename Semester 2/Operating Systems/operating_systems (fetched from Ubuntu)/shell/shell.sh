#!/bin/bash

echo "Hello world"

echo $#   
# = argc

echo $@   
# = argv

S=0
for X in `find -type f -name "*.txt"` ; do
	echo $X
	N=`grep -E -c "^$" $X`
	# grep -E -c "^$" $X | wc -l
	echo $N
	S=`expr $S + $N`
done

echo "TOTAL:"
echo $S