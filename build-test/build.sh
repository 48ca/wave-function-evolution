#!/bin/bash

set -e

build() {
	echo "Building with $2..."
	if [ -d $1 ]; then rm -r $1; fi
	mkdir $1
	pushd $1 > /dev/null
	cmake ../.. $3 && make
	popd > /dev/null
	rm -rf $1
}

build default "default settings"
build noquadmath "no quadmath" "-DNO_QUADMATH=True"
