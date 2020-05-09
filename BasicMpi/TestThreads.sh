#!/bin/bash

for NUMBER_OF_PROCESSES in {2..8};
do
    echo ${NUMBER_OF_PROCESSES}
    mpiexec -n ${NUMBER_OF_PROCESSES} $1
done
