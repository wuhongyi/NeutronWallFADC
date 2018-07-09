#!/bin/bash

# for (( i=1; i<=28; i++ ))
# do
#     echo "mod: $i"
#     ./wu 1470 $i
# done


for (( i=1310; i<=1339; i++ ))
do
    echo "mod: $i"
    ./wu $i 14
done
