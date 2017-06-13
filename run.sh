#!/bin/bash

DIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
pushd $DIR > /dev/null

set -e

echo "Compiling..."
cmake .
make

echo "##############################################"

# Schrodinger
./evolvequ
echo "" && echo ""
./evolvequ -e
# Eigenstate
echo "" && echo ""
# Classical
./evolvewv

set +e

echo "##############################################"

echo "Plotting schrodinger..."
echo "  use ^\ to quit"
cd plot
./plot.py ../outqu.txt

echo "" && echo ""

echo "Plotting schrodinger eigenstate..."
./plot.py ../outque.txt

echo "" && echo ""

echo "Plotting classical..."

./plot.py ../outwv.txt
cd ..

echo "Done"

popd > /dev/null
