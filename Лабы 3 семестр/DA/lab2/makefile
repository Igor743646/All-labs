CC = g++
FLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm

all: main.out

main.out: main.cpp avltree.hpp string.hpp
	${CC} ${FLAGS} main.cpp -o main.out

run:
	python tests_creator.py
	rm -rf time_log.txt
	./main.out < tests/01.t > tests/01ans.txt
	./main.out < tests/02.t > tests/02ans.txt
	./main.out < tests/03.t > tests/03ans.txt
	./main.out < tests/04.t > tests/04ans.txt
	diff tests/01ans.txt tests/01.txt
	diff tests/02ans.txt tests/02.txt
	diff tests/03ans.txt tests/03.txt
	diff tests/04ans.txt tests/04.txt
	cat time_log.txt

testss:
	python tests_creator.py