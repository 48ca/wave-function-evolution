#!/bin/bash

if [ -z "$1" ]
then
	echo "Specify what you want to profile"
	echo "ex: ./profile.sh evolvequ -n 100"
	exit 1
fi

TMP=$(mktemp)
EVOLVEOUT=$(mktemp)
valgrind --tool=callgrind --callgrind-out-file=$TMP ./$@ -o $EVOLVEOUT
rm $EVOLVEOUT
kcachegrind $TMP
rm $TMP
