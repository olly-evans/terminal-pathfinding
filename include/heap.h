
#ifndef HEAP_H
#define HEAP_H

typedef struct {
    struct Cell **bh; // Binary minimum heap, left child at 2i + 1, right at 2i + 2.
    int size;
} Heap;

extern Heap hp;

void heapExtract(Heap *hp);
void heapInsert(Heap *hp, struct Cell *cell);
void heapBubbleUp(Heap *hp, int childIdx);
void swap(struct Cell **a, struct Cell **b);
Heap* heapBubbleDown(Heap *hp, int parentIdx);
void initBinaryHeap();
int getManhattanDist(struct Cell *c1, struct Cell *end);

#endif