#!/bin/sh

seq 10 | sort -R > tests/01
seq 10 | sort -nr > tests/02
./randList 10 11 > tests/03

for t in 01 02 03
do
	echo === Test $t ===
	sort -n < tests/$t > tests/$t.expected
	./useIntList < tests/$t > tests/$t.observed
	diff tests/$t.expected tests/$t.observed
done
rm tests/*.expected tests/*.observed    