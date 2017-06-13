#!/bin/bash

DIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
pushd $DIR > /dev/null

set -e

echo "Compiling..."
cmake . -DNO_QUADMATH=True -DNO_OPENMP=True
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
echo "" && echo ""
# Classical standing
./evolvewv -cs

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

echo "" && echo ""

echo "Plotting classical standing..."

./plot.py ../outwvs.txt
cd ..

echo "Done"

popd > /dev/null
