#ifndef QUEUE_H
#define QUEUE_H

typedef int var;
typedef struct queue queue;

queue* queue_create();
int queue_insert(queue*, var);
void queue_destroy(queue*);
void queue_print(queue*);
int queue_size(queue*);
int queue_isEmpty(queue*);
int queue_isFull(queue*);
int queue_remove(queue*, var*);

#endif