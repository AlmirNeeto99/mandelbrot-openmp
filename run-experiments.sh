#!/bin/bash

THREADS=12

ITERATIONS=(10 100 1000 10000)

APPLICATION=./parallel

for iteration in "${ITERATIONS[@]}"
do
    for ((thread=THREADS; thread>0; thread--))
    do    
        echo === Running experiment ===
        echo 7680 4320 -2.0 1.0 -1.5 1.5 $iteration $thread > inputs.txt
        cat inputs.txt | $APPLICATION
    done
done

rm inputs.txt
