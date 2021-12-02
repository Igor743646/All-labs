# makefile 1

CC = gcc

CCFLAGS = -g -Wall -pedantic -std=c99

laboratornaya26-25: main.o queue.o sort.o
	$(CC) -o laboratornaya26-25 main.o queue.o sort.o
main.o: main.c queue.h sort.h
	$(CC) $(CCFLAGS) -c main.c
queue.o: queue.c queue.h
	$(CC) -c queue.c
sort.o: sort.c sort.h
	$(CC) $(CCFLAGS) -c sort.c
sort.o: queue.h

clean:
	rm -f *.o laboratornaya26-25

cleansort:
	rm -f sort.o

start:
	./laboratornaya26-25
