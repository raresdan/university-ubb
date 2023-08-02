#!/bin/bash

echo "Hello `whoami` !"

n = $1

echo $0 is the name of the command
echo $n is the name of the parameter

# for p in $@; do

for p in $*
do
	echo $p
done
