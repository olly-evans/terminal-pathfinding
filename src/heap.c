#include <stdlib.h>
#include <stdio.h>

#include "output.h"
#include "heap.h"
#include "algorithms.h"
#include "cell.h"

/* PRIORITY QUEUE */
Heap hp;

struct Cell *heapExtract(Heap *hp) {
    if (hp->os_size == 0) return NULL;

    struct Cell *extracted = hp->bh[0];  // the cell to pop

    
    // Swap root with last element
    int lastIdx = hp->os_size - 1;
    swap(&hp->bh[0], &hp->bh[lastIdx]);
    hp->os_size--;

    // Bubble down the new root to maintain heap property
    heapBubbleDown(hp, 0);

    extracted->inOpenSet = false;
    return extracted;
}

Heap* heapInsert(Heap *hp, struct Cell *cell) {

    /* Add element to the binary heap. */

    if (inOpenSet(hp, cell)) return hp; // this check can't be right.
    
    if (!isStartCell(cell) && !isEndCell(cell)) {
        cell->ch = 'O'; //
    }
    cell->type = OPEN; //
    cell->inOpenSet = true;
    // int new_last = hp->os_size; // Becomes last element

    if (hp->os_size == 0) {
        hp->bh = malloc(sizeof(*hp->bh));
    }

    hp->bh = realloc(hp->bh, (hp->os_size + 1) * sizeof(*hp->bh ));
    hp->bh[hp->os_size++] = cell;

    // If one cell in queue we can just return no bubbling required.
    if (hp->os_size == 1) return hp;

    return heapBubbleUp(hp, hp->os_size - 1);
}

Heap* heapBubbleUp(Heap *hp, int childIdx) {

    /* Try and make this account for g score too */
    if (childIdx == 0) return hp;

    int parentIdx = ((childIdx - 1) / 2);

    while (childIdx > 0 && hp->bh[parentIdx]->f >= hp->bh[childIdx]->f) {
        swap(&hp->bh[parentIdx], &hp->bh[childIdx]);

        childIdx = parentIdx;
        parentIdx = ((childIdx - 1) / 2);
    }
    return hp;
}

Heap* heapBubbleDown(Heap *hp, int parentIdx) {
    int os_size = hp->os_size;

    while (1) {
        int lchildIdx = 2 * parentIdx + 1;
        int rchildIdx = 2 * parentIdx + 2;
        int smallestIdx = parentIdx;

        // Check if left child exists and has lower f
        if (lchildIdx < os_size && hp->bh[lchildIdx]->f < hp->bh[smallestIdx]->f) {
            smallestIdx = lchildIdx;
        }

        // Check if right child exists and has lower f
        if (rchildIdx < os_size && hp->bh[rchildIdx]->f < hp->bh[smallestIdx]->f) {
            smallestIdx = rchildIdx;
        }

        // If no swap needed, break
        if (smallestIdx == parentIdx) break;

        if (parentIdx >= hp->os_size || smallestIdx >= hp->os_size) return hp;
        

        // Swap and continue bubbling down
        swap(&hp->bh[parentIdx], &hp->bh[smallestIdx]);
        parentIdx = smallestIdx;
    }

    return hp;
}

void swap(struct Cell **a, struct Cell **b) {
    // a = address pointer in list of pointers pointing to. 
    if (!a || !b) return;
    struct Cell *tmp = *a;
    *a = *b;
    *b = tmp;
}

Heap initBinaryHeap(Heap hp) {
    hp.os_size = 0;
    hp.cs_size = 0;
    hp.bh = NULL;
    hp.cs = NULL;
    return hp;
}

/* MIGHT NEED TO BE IN ANOTHER FILE. */

int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return 2*(abs(end->x - c1->x) + abs(end->y - c1->y));
}