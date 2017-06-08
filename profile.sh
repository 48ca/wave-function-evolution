#!/bin/bash

TMP=$(mktemp)
EVOLVEOUT=$(mktemp)
valgrind --tool=callgrind --callgrind-out-file=$TMP ./evolve -n 1000 -o $EVOLVEOUT
rm $EVOLVEOUT
kcachegrind $TMP
rm $TMP
