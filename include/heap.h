
#ifndef HEAP_H
#define HEAP_H

#define HEAP_INIT (Heap){.openSet = NULL, .openSetSize = 0, .closed_set = NULL, .closedSetSize = 0};

#define INIT_OS_CAP 16
#define INIT_CS_CAP 16

typedef struct {
    struct Cell **openSet; // Binary minimum heap, zero-indexed so left child at 2i + 1, right at 2i + 2.
    int openSetSize;
    int os_cap;

    struct Cell **closed_set; // Closed set of explored cells.
    int closedSetSize;
    int cs_cap;
} Heap;

struct Cell* heapExtract(Heap *hp);
void heapInsert(Heap *hp, struct Cell *cell);
void heapBubbleUp(Heap *hp, int childIdx);
void swap(struct Cell **a, struct Cell **b);
void heapBubbleDown(Heap *hp, int parentIdx);
Heap* initHeap();
void makeClosed(Heap *hp, struct Cell* curr);
int getOpenSetIdx(Heap *hp, struct Cell *cell);
void freeHeap(Heap *hp);

#endif