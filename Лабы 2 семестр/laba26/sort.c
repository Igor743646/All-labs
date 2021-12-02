#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#define and &&
#define or ||
#include "queue.h"

void swapin (queue *q) {
	if (size(q)>1) {
		for (int j=1; j<size(q); j++) {
			if (elem(q, j)>elem(q, j+1)) {
				int r = 0; 
				r = elem(q, j);
				change(q, j, elem(q, j+1));
				change(q, j+1, r);
				break;
			}
		}
	}
}

void swapde (queue *q, int i) {
	if (size(q)>1) {
		for (int j=1; j<size(q)-i; j++) {
			if (elem(q, j)<elem(q, j+1)) {
				int r = 0; 
				r = elem(q, j);
				change(q, j, elem(q, j+1));
				change(q, j+1, r);
				//break;
			}
		}
	}
}

bool ord (queue *q) {
	int i=0;
	while ((elem(q, i)<elem(q, i+1)) and (i<size(q)-1)) {
		i++;
	}
	if (i==size(q)-1) {
		return true;
	} else {
		return false;
	}
}

void sortedqueuein (queue *q) {
	for (int i=0; i<size(q)*(size(q)-1); i++) {
		swapin(q);
	}
}

void sortedqueuede (queue *q) {
	for (int i=0; i<size(q)-1; i++) {
		swapde(q, i);
	}
}

