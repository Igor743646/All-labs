#ifndef _vector_h_
#define _vector_h_

typedef struct {
 float *data;
 int size;
} vector;

void create(vector *v, int sz);
bool empty(vector v);
int size(vector v);
float load(vector *v, int i);
void save(vector *v, int i, float t);
bool equal(vector *v1, vector *v2);
void destroy(vector *v);
void resize(vector *v, int sz);
#endif