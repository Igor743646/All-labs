#!/bin/bash
max=100

python3 tester.py;
for ((i = 0; i < ${max}; i++)) 
do 
	echo "test: $i ";
	./prog2.out < tests/test${i}.txt >> tests/ans.txt;
	./prog2.out < tests/test${i}.txt >> tests/ans1.txt;
	./prog2.out < tests/test${i}.txt >> tests/ans2.txt;
done
gnuplot gnu*;
