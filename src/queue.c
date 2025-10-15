#include <stdlib.h>

#include "queue.h"
#include "terminal.h"

Queue* queueInit() {
    Queue *Q = malloc(sizeof(Queue));
    if (!Q) die("queueInit() -> malloc");

    Q->qu = NULL;
    Q->qu_size = 0;
    return Q;
}

Queue* enqueue(Queue *Q, struct Cell  *cell) {
    
    cell->type = OPEN;
    cell->inOpenSet = true;

    if (Q->qu_size == 0) Q->qu = malloc(sizeof(*Q->qu));
    Q->qu = realloc(Q->qu, (Q->qu_size + 1) * sizeof(Q->qu));

    Q->qu[Q->qu_size++] = cell;

    return Q;
}

struct Cell* dequeue(Queue *Q) {
    struct Cell *cell = Q->qu[0];

    cell->type = CLOSED;
    cell->inOpenSet = false;

    Q->qu_size--;

    Q->qu = &Q->qu[1];

    return cell;
}

void stackFree(Queue *S) {
    return;
}