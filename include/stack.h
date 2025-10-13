#ifndef STACK_H
#define STACK_H

#include "cell.h"

#define STACK_INIT (Stack){.st = NULL, .st_size = 0};


typedef struct {
    struct Cell **st; // Stack, pointer to an array of cell pointers.
    int st_size; // Number of cell pointers in st.

    struct Cell **visited;
    int v_size;
} Stack;

Stack* stackInit();
Stack* stackPush(Stack *S, struct Cell *cell);
struct Cell* stackPop(Stack *S);
void stackFree(Stack *S);

#endif