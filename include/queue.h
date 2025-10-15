#ifndef STACK_H
#define STACK_H

#include "cell.h"

#define STACK_INIT (Queue){.st = NULL, .st_size = 0};


typedef struct {
    struct Cell **qu; // Stack, pointer to an array of cell pointers.
    int qu_size; // Number of cell pointers in st.
} Queue;

Queue* queueInit();
Queue* enqueue(Queue *S, struct Cell *cell);
struct Cell* dequeue(Queue *S);
void stackFree(Queue *S);

#endif