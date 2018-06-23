#!/bin/bash

for (( i=1; i<=28; i++ ))
do
    echo "mod: $i"
    ./wu 1470 $i
done
