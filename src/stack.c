#include <stdlib.h>

#include "stack.h"
#include "terminal.h"

Stack* stackInit() {
    Stack *S = malloc(sizeof(Stack));
    if (!S) die("stackInit() -> malloc");

    S->st = NULL;
    S->st_size = 0;
    
    S->visited = NULL;
    S->v_size = 0;
    return S;
}

Stack* stackPush(Stack *S, struct Cell  *cell) {
    
    cell->type = OPEN;
    cell->inOpenSet = true;

    if (S->st_size == 0) S->st = malloc(sizeof(*S->st));
    S->st = realloc(S->st, (S->st_size + 1) * sizeof(S->st));

    S->st[S->st_size++] = cell;

    return S;
}

struct Cell* stackPop(Stack *S) {
    struct Cell *cell = S->st[S->st_size-1];

    cell->type = CLOSED;
    cell->inOpenSet = false;

    S->st_size--;

    return cell;
}

void stackFree(Stack *S) {
    return;
}