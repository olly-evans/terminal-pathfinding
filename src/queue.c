#include <stdlib.h>

#include "queue.h"
#include "terminal.h"

Queue* queueInit() {
    Queue *Q = malloc(sizeof(Queue));
    if (!Q) die("queueInit() -> malloc");

    Q->capacity = 2;
    Q->qu = malloc(Q->capacity * sizeof(struct Cell *));
    if (!Q->qu) die("queueInit() -> malloc");

    Q->front = 0;
    Q->rear = 0;
    return Q;
}

Queue* enqueue(Queue *Q, struct Cell  *cell) {
    
    cell->type = OPEN;
    cell->inOpenSet = true; // prob don't need.

    if (Q->rear == Q->capacity) {
        Q->capacity *= 2;
        Q->qu = realloc(Q->qu, Q->capacity * sizeof(struct Cell *));
        if (!Q->qu) die("enqueue() -> realloc");

    }

    Q->qu[Q->rear++] = cell;
    return Q;
}

struct Cell* dequeue(Queue *Q) {
    
    if (Q->rear == Q->front) return NULL;

    struct Cell *cell = Q->qu[Q->front++];

    if (!cell) die("dequeue() -> cell is NULL.");

    cell->type = CLOSED;
    cell->inOpenSet = false; // prob don't need.
    return cell;
}

void freeQueue(Queue *Q) {
    free(Q->qu);
    free(Q);
}