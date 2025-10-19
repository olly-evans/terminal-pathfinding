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

    // need a check here ofc.
    
    struct Cell *cell = S->frontier[S->rear--];
    if (!cell) die("stackPop() -> cell");

    cell->type = CLOSED;

    return cell;
    
}