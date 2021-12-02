#ifndef _queue_h_
#define _queue_h_

typedef struct {
	int *mas;
	int size;
} queue;

bool empty(queue *q);
void create(queue *q, int sz);
int size(queue *q);
void load(queue *q, int x);

void del (queue *q);
void finl (queue *q);
int felem (queue *q);
int elem (queue *q, int x);
void change (queue *q, int x, int a);
void print (queue *q, int x);
#endif