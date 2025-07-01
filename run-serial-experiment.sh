#!/bin/bash

ITERATIONS=10000
APPLICATION=./serial

DIMENSIONS=(
    "1920 1080"
    "3840 2160"
    "7680 4320"
)

for dimension in "${DIMENSIONS[@]}"
do
    echo "Running experiments for dimension: $dimension"
    THREADS=1
    # Run the serial application for each dimension
    echo === Running serial experiment ===
    echo $dimension -2.0 1.0 -1.5 1.5 $ITERATIONS > inputs.txt
    cat inputs.txt | $APPLICATION
done
rm inputs.txt

