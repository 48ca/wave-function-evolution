#!/bin/bash

pushd $(dirname "${BASH_SOURCE[0]}") > /dev/null

build() {
	echo -e "\e[96mBuilding with $2... \e[0m "
	if [ -d $1 ]; then rm -r $1; fi
	mkdir $1 && \
	pushd $1 > /dev/null || return 1
	cmake ../.. $3 > /dev/null || return 2
	make > /dev/null || return 3
	popd > /dev/null
	return 0
}

check() {

	ERRORS=("" # Indices corresponding to the return codes of build
			"!!! Error in setup"
			"!!! Error running cmake"
			"!!! Error running make"
			"!!! Error while cleaning up")

	echo -e "\e[91m${ERRORS[$1]}\e[0m"

	# To make this non-fatal, remove this line
	exit $1
}

if [ -e ../CMakeCache.txt ]
then
	echo "!!! It looks like you have already built CMake in the directory above."
	echo "    This build script will not work if CMake detects a previous build."
	echo "    Run clean-cmake.sh in the directory above to fix this problem."
	exit 1
fi

build default "default settings" || check $?
build noquadmath "no quadmath" "-DNO_QUADMATH=True" || check $?
build noopenmp "no openmp" "-DNO_OPENMP=True" || check $?

echo -e "\e[92mAll builds completed\e[0m"

popd > /dev/null
