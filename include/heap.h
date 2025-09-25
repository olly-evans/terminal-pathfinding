
#ifndef HEAP_H
#define HEAP_H

typedef struct {
    struct Cell **bh; // Binary minimum heap, left child at 2i + 1, right at 2i + 2.
    int size;
} Heap;

extern Heap hp;

void initHeap();

#endif