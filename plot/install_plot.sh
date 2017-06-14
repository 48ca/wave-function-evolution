#!/bin/bash

pushd $(dirname "${BASH_SOURCE[0]}") > /dev/null

if [ -d venv ]
then
	echo "The virtual environment is already installed as 'venv'"
else
	virtualenv -p python3 venv
fi

echo "Updating virtual environment..."
venv/bin/pip3 install -r requirements.txt | sed "s/^/ >>> /g"

popd > /dev/null
