#!/bin/bash
max=200

function check_dir {
	if [ -d "$1" ]; then
		echo "$1 is present"
	else
		echo "$1 is not present. Creating..."
		mkdir -p $1
	fi
}

function check_file {
	if [ -f "$1" ]; then
		echo "$1 is present"
	else
		echo "$1 is not present. Creating..."
		make
	fi
}

check_dir "tests"
check_file "prog2.out"
python3 tester.py ${max};

for ((i = 0; i < ${max}; i++)) 
do 
	echo "test: $i ";
	./prog2.out < tests/test${i}.txt > tests/test${i}_newans.txt;
	if diff tests/test${i}_ans.txt tests/test${i}_newans.txt ; then
		echo "passed"
	else
		echo "NOT PASSED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		break;
	fi
done