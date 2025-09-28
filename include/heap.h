
#ifndef HEAP_H
#define HEAP_H

typedef struct {
    struct Cell **bh; // Binary minimum heap, zero-indexed so left child at 2i + 1, right at 2i + 2.
    int os_size;

    struct Cell **cs; // Closed set of explored cells.
    int cs_size;
} Heap;

extern Heap hp;

struct Cell* heapExtract(Heap *hp);
Heap* heapInsert(Heap *hp, struct Cell *cell);
void heapBubbleUp(Heap *hp, int childIdx);
void swap(struct Cell **a, struct Cell **b);
Heap* heapBubbleDown(Heap *hp, int parentIdx);
void initBinaryHeap();
int getManhattanDist(struct Cell *c1, struct Cell *end);

#endif