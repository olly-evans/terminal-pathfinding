#include <stdlib.h>

#include "queue_stack.h"
#include "cell.h"
#include "terminal.h"

QueueStack* queue_stackInit() {
    QueueStack* QS = malloc(sizeof(QueueStack));
    if (!QS) die("queue_stackInit -> malloc");

    QS->capacity = 8;
    QS->frontier = malloc(QS->capacity * sizeof(struct Cell *));
    if (!QS->frontier) die("queue_stackInit -> malloc");

    QS->rear = -1;
    QS->front = 0;

    return QS;
}

/* STACK OPERATIONS */

void stackPush(QueueStack* S, struct Cell *cell) {
    cell->type = OPEN;

    if (S->rear == S->capacity) {
        S->capacity *= 2;
        S->frontier = realloc(S->frontier, S->capacity * sizeof(*S->frontier));
        if (!S->frontier) die("pushStack -> realloc");
    }

    S->frontier[++S->rear] = cell;

}

struct Cell* stackPop(QueueStack* S) {

    if (S->rear == -1) return NULL;

    struct Cell *cell = S->frontier[S->rear--];
    if (!cell) die("stackPop() -> cell");

    cell->type = CLOSED;

    return cell;
    
}

void enqueue(QueueStack* Q, struct Cell *cell) {
    cell->type = OPEN;

    if (Q->rear == Q->front) {
        Q->capacity *= 2;
        Q->frontier = realloc(Q->frontier, Q->capacity * sizeof(struct Cell *));
        if (!Q->frontier) die("enqueue() -> realloc");
    }
    Q->frontier[++Q->rear] = cell;
}

struct Cell * dequeue(QueueStack *Q) {
    if (Q->rear == -1) return NULL;
    struct Cell *cell = Q->frontier[Q->front++];
    if (!cell) die("dequeue() -> cell");
    cell->type = CLOSED;
    return cell;
}