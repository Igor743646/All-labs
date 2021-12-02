#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"

bool empty(vector v) {
	return v.size==0;
}

void create(  vector *v, int sz) {
 v->size=sz; 
 v->data=malloc(sizeof(float)*v->size); 
}

int size(vector v) {
 
 return v.size; 
}

float load(vector *v, int i) {
  if((i>=0) && (i<v->size)) {
    return v->data[i];
  } 
  return 0;
}

void save( vector *v, int i, float t) {
  if((i>=0) && (i<v->size)) {
    v->data[i]=t;
  }
}

void destroy(vector *v) {
	v->size=0;
	free(v->data);
}

bool equal(vector *v1, vector *v2) {
	if (v1->size != v2->size) {
		return false;
	} else {
		for (int i=0; i<v1->size; i++) {
			if (v1->data[i] != v2->data[i]) {
				return false;
			} 
		} return true;
	}
}

void resize(vector *v, int sz) {
	v->size=sz;
    v->data=realloc(v->data,sizeof(float)*v->size);
}
