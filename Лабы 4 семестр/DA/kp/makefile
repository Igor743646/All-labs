#!/bin/bash
CC = g++
FLAGS = -std=c++2a -Wno-sign-compare -O2 -lm

all: prog2.out point.hpp edge.hpp persistent_tree.hpp

prog2.out: prog2.o point.o edge.o
	${CC} ${FLAGS} prog2.o point.o edge.o -o prog2.out

%.o: %.cpp point.hpp edge.hpp persistent_tree.hpp
	${CC} ${FLAGS} -c $<

run:
	rm -f tests/ans.txt
	rm -f tests/ans2.txt
	rm -f tests/ans1.txt
	bash bash*

runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./prog2.out < tests/test0.txt

clean:
	rm -rf *.out *.o
