#!/bin/bash

# for (( i=1; i<=28; i++ ))
# do
#     echo "mod: $i"
#     ./wu 1470 $i
# done


for (( i=1410; i<=1419; i++ ))
do
    echo "mod: $i"
    ./wu $i 14
done
