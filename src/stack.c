#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "cell.h"
#include "terminal.h"

Stack* stackInit() {
    Stack* QS = malloc(sizeof(Stack));
    if (!QS) die("queue_stackInit -> malloc");

    QS->capacity = 8;
    QS->frontier = malloc(QS->capacity * sizeof(struct Cell *));
    if (!QS->frontier) die("queue_stackInit -> malloc");

    QS->rear = -1;
    QS->front = 0;

    return QS;
}

void stackPush(Stack* S, struct Cell *cell) {
    cell->type = OPEN;

    if (stackFull(S)) {
        S->capacity *= 2;
        S->frontier = realloc(S->frontier, S->capacity * sizeof(*S->frontier));
        if (!S->frontier) die("pushStack -> realloc");
    }
    S->frontier[++S->rear] = cell;
}

struct Cell* stackPop(Stack* S) {

    if (stackEmpty(S)) return NULL;

    struct Cell *cell = S->frontier[S->rear--];
    if (!cell) die("stackPop() -> cell");
    cell->type = CLOSED;

    return cell; 
}

bool stackEmpty(Stack *S) {
    return S->rear == -1;
}

bool stackFull(Stack *S) {
    return S->rear == S->capacity - 1;
}

void stackFree(Stack *S) {
    free(S->frontier);
    free(S);
}