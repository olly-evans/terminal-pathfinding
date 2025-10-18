
#ifndef HEAP_H
#define HEAP_H

#define HEAP_INIT (Heap){.os = NULL, .os_size = 0, .cs = NULL, .cs_size = 0};

#define INIT_OS_CAP 16
#define INIT_CS_CAP 16

typedef struct {
    struct Cell **os; // Binary minimum heap, zero-indexed so left child at 2i + 1, right at 2i + 2.
    int os_size;
    int os_cap;

    struct Cell **cs; // Closed set of explored cells.
    int cs_size;
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