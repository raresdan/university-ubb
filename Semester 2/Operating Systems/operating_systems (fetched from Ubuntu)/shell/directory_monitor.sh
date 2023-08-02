#!/bin/bash

if test -z $1 ; then
	echo "we need 1 argument"
	exit 1
fi

if test ! -d $1 ; then
	echo "$1 needs to be a directory"
	exit 1
fi

D=$1
STATE=""

while true ; do
	S=""
	for I in `find $D` ; do
		if test -f $I ; then
			# echo "$I is a file"
			M=`ls -l $I | sha1sum`
			C=`cat $I | sha1sum`
		elif test -d $I ; then
			# echo "$I is a dir"
			M=`ls -l -d $I | sha1sum`
			C=`ls -l $I | sha1sum`			
		fi
		S="$S\n$M $C"
	done
	if test -n "$STATE" && test "$S" != "$STATE"; then
		echo "Any change occured!"
	fi
	STATE="$S"
	sleep 2
done


