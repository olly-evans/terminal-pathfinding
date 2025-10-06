
#ifndef HEAP_H
#define HEAP_H

#define HEAP_INIT (Heap){.bh = NULL, .os_size = 0, .cs = NULL, .cs_size = 0};

// Argument to be had over these being seperate, or renamed.
typedef struct {
    struct Cell **bh; // Binary minimum heap, zero-indexed so left child at 2i + 1, right at 2i + 2.
    int os_size;

    struct Cell **cs; // Closed set of explored cells.
    int cs_size;
} Heap;

extern Heap hp;

struct Cell* heapExtract(Heap *hp);
Heap* heapInsert(Heap *hp, struct Cell *cell);
Heap* heapBubbleUp(Heap *hp, int childIdx);
void swap(struct Cell **a, struct Cell **b);
Heap* heapBubbleDown(Heap *hp, int parentIdx);
Heap* initHeap();

#endif