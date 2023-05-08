#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR

MODEL_PATH=$(realpath $SCRIPT_DIR/../model/inverted_pendulum/inverted_pendulum.xml)
echo $MODEL_PATH

../build/inverted_pendulum --model $MODEL_PATH
