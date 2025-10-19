#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

typedef struct QueueStack {
    struct Cell **frontier;
    int front;
    int rear;
    int capacity;

    void (*push)(struct QueueStack*, struct Cell *);
    struct Cell * (*pop)(struct QueueStack*);
} QueueStack;

QueueStack* queue_stackInit();
void stackPush(QueueStack* S, struct Cell *cell);
struct Cell* stackPop(QueueStack* S);

#endif