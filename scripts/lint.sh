#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR/..

find ./src ./include -name "*.cpp" | xargs -I {} clang-format {} -style=Chromium -i
