
all: library.so

library.so: library.o
	g++ -std=c++17 -shared -o library.so library.o

library.o: library.cpp
	g++ -std=c++17 -c -fPIC library.cpp

run:
	python3 VKBot_script.py