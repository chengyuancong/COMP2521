#!/bin/bash

NAME="lab03"
BIN="./bst"

echo "***                 ***"
echo "***  Testing $NAME  ***"

if [ ! -f "$BIN" ]
then
	echo "No such executable: $BIN"
	exit 1
fi

if [ ! -x "$BIN" ]
then
	echo "$BIN is not executable"
	exit 1
fi

if [ ! -d tests ]
then
	echo "No tests/ directory here. Are you in the right directory?"
	exit 1
fi


if [ "$#" -eq 0 ]
then
	inFiles="*.in"
elif [ "$#" -eq 1 ]
then
	inFiles="$1.in"
else
	echo "Usage-1: autotest  "
	echo "Usage-2: autotest <test-number> "
	exit 1
fi

for tt in tests/$inFiles
do
	t=`basename $tt .in`
	"./$BIN" < tests/$t.in | head -500 > tests/$t.out
	echo "------------------------------ "
	if cmp -s tests/$t.exp tests/$t.out
	then
		echo "** Passed Test $t"
	else
		echo "** Failed Test $t"
		echo " "
		echo "> Your output (in tests/$t.out): "
		cat  tests/$t.out
		echo " "
		echo "> Expected output (in tests/$t.exp): "
		cat  tests/$t.exp
		echo " "
		echo "> Compare files tests/$t.exp and tests/$t.out to see differences"
	fi
	echo "------------------------------ "
done

echo "        "



