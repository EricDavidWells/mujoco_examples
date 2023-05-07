#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR/..
mkdir build
cd build
cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE 
make