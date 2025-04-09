#!/bin/bash

THREADS=(1 2 5 8 10)

ITERATIONS=(10 100 500 1000 5000 10000 50000 100000)

APPLICATION=./parallel

for thread in "${THREADS[@]}"
do

    for iteration in "${ITERATIONS[@]}"
    do
        echo Running for $thread-$iteration
        echo 7680 4320 -2.0 1.0 -1.5 1.5 $iteration $thread > inputs.txt
        cat inputs.txt | $APPLICATION
    done
done