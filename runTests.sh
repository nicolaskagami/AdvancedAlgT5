#!/bin/bash

TESTS="./Tests"
RESULTS="./Results"

for file in ${TESTS}/*.dat;
do
    TEST="${RESULTS}/$(basename ${file} .dat)"
    echo "File: $file"
    #./EPPM < $file 2> $TEST.results 1>/dev/null 
    ./EPM < $file 2>> $TEST.results 1>/dev/null
done
