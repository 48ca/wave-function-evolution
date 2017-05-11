#!/bin/bash

DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"

pushd $DIR/libs > /dev/null

tar xvf mathgl-*.gz
cd mathgl-*/

cmake .
make
sudo make install

cd ..
rm -rf mathgl-*/

popd > /dev/null

echo Done
