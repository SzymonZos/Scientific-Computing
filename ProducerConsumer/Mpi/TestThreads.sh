#!/bin/bash

for NUMBER_OF_PROCESSES in {2..8};
do
    echo "Processes: " ${NUMBER_OF_PROCESSES} >> "./logs/comparison.txt"
    mpiexec -n ${NUMBER_OF_PROCESSES} $1
done
