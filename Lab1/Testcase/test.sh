#!/bin/bash

CPP=$1
g++ -std=c++11 ${CPP} -o a.out
for i in {1..9};do
    echo "case ${i} testing"
    time ./a.out case${i}.txt out${i}
    differ=$(diff -b out${i} golden_case${i}.txt | wc -w)
    if [ ${differ} -eq 0 ];
    then
        echo "case${i} pass"
        rm out${i}
    else
        diff -b out${i} golden_case${i}.txt
    fi
done

