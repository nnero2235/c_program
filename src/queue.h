#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

Queue *newQueue();

void enqueue(Queue *q,void *node);

void *popQueue(Queue *q);

int queueEmpty(Queue *q);

void queueFree(Queue *q);

#endif