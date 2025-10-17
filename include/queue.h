#ifndef QUEUE_H
#define QUEUE_H

#include "cell.h"

#define STACK_INIT (Queue){.qu = NULL, .qu = 0};


typedef struct {
    struct Cell **qu; // Stack, pointer to an array of cell pointers.
    int front;
    int rear;
    int capacity;

} Queue;

Queue* queueInit();
Queue* enqueue(Queue *S, struct Cell *cell);
struct Cell* dequeue(Queue *S);
void freeQueue(Queue *Q);

#endif