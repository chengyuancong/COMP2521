#!/bin/sh

for n in 10000 20000 40000 80000 160000 320000

do
    seq $n | sort -R > tests/1
    seq $n > tests/2
    seq $n | sort -nr > tests/3
    ./randList $n > tests/4
    ./randList $n | sort -n > tests/5
    ./randList $n | sort -nr > tests/6

    echo =========== Input $n ===========

    for t in 1 2 3 4 5 6
    do
        echo ===== Test $t =====
        echo == use ==
        time ./useIntList < tests/$t > /dev/null
        echo == sort ==
        time sort -n < tests/$t > /dev/null
    done

done