#!/bin/bash

for I in $@ ; do 
	
	if test -f $I ; then
		echo "$I is a file"
	elif test -d $I ; then
		echo "$I is a directory"
	elif `echo $I | grep -E -q "^[0-9]+$"` ; then
		echo "$I is an integer"
	else
		echo "We don't know what $I is"
	fi
done