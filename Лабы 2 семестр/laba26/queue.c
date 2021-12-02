#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#define and &&
#define or ||

#include "queue.h"

bool empty(queue *q) {
	return q->size==0;
}

void create(queue *q, int sz) {
 q->size=sz-1; 
 q->mas=malloc(sizeof(int)*(q->size+1)); 
}

int size(queue *q) {
 return q->size; 
}

void load(queue *q, int x) {
   q->size++;
   q->mas=realloc(q->mas,sizeof(int)*q->size);
   q->mas[q->size-1]=x; 
}

/*
void print (queue *q) {
	if (!empty(q)) {
		for (int i=0; i<size(q); i++) {
			printf("%d ", q->mas[i]);
		}
	}
}*/
int felem (queue *q) {
	if (!empty(q)) {
		return q->mas[0];
	}
}



void del (queue *q) {
	if (!empty(q)) {
		for (int i=0; i<size(q)-1; i++) {
			q->mas[i]=q->mas[i+1];
		}
		q->size--;
		q->mas=realloc(q->mas,sizeof(int)*q->size);
		
	}
}


/*
void finl (queue *q) {
	if (!empty(q)) {
		int x=q->mas[0];
		for (int i=0; i<q->size-1; i++) {
			q->mas[i]=q->mas[i+1];
		}
		q->mas[q->size-1]=x;
	}
}*/
void finl (queue *q) {
	if (!empty(q)) {
		load(q, felem(q));
		del(q);
	}
}


int elem (queue *q, int x) {
	if ((!empty(q)) and (x<=size(q)) and (x>0)) {
		for (int i=0; i<x-1; i++) {
			finl(q);
		}
		int r=felem(q);
		for (int i=0; i<size(q)-x+1; i++) {
			finl(q);
		}
		return r;
	}
}

void change (queue *q, int x, int a) {
	if ((!empty(q)) and (x<=size(q)) and (x>0)) {
		for (int i=0; i<x-1; i++) {
			finl(q);
		}
		del(q);
		load(q, a);
		for (int i=0; i<size(q)-x; i++) {
			finl(q);
		}
		
	}
}

void print (queue *q, int x) {
	if (x!=0) {
	printf("%d ", felem(q));
	finl(q);
	print(q, x-1);
	}
}