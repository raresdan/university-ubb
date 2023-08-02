#!/bin/bash

D=$1
S=0

for dir in `find $D -type f -name "*.c"`; do
	N=`grep -c "[^ ]" $dir`
	S=`expr $S + $N`
done

echo $S
