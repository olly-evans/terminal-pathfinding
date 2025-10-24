#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

typedef struct Stack {
    struct Cell **frontier;
    int front;
    int rear;
    int capacity;
} Stack;

Stack* stackInit();

void stackPush(Stack* S, struct Cell *cell);
struct Cell* stackPop(Stack* S);

#endif