#include <stdlib.h>
#include <stdio.h>

#include "output.h"
#include "heap.h"

/* PRIORITY QUEUE */
Heap hp = { NULL, 0, NULL, 0 };

struct Cell* heapExtract(Heap *hp) {
    if (hp->os_size == 0) return NULL;

    struct Cell *root = hp->bh[0];

    if (hp->os_size == 1) {
        hp->os_size--;
        return root;
    }

    int lastIdx = hp->os_size - 1;

    // Swap root with last
    swap(&hp->bh[0], &hp->bh[lastIdx]);

    // Remove last element (which is now at index 0 after swap)
    hp->os_size--;

    heapBubbleDown(hp, 0);

    return root;
}

Heap* heapInsert(Heap *hp, struct Cell *cell) {

    /* Add element to the binary heap. */

    cell->inOpenSet = true;
    cell->ch = 'O'; //
    cell->type = OPEN; //

    int idx = hp->os_size; // hp.size incremented so saving this.

    hp->bh = realloc(hp->bh, (hp->os_size + 1) * sizeof(*hp->bh ));
    hp->bh[hp->os_size++] = cell;

    // If one cell in queue we can just return no bubbling required.
    if (hp->os_size == 1) return hp;

    return heapBubbleUp(hp, idx);
}

Heap* heapBubbleUp(Heap *hp, int childIdx) {

    if (childIdx == 0) return hp;

    int parentIdx = ((childIdx - 1) / 2);

    while (childIdx > 0 && hp->bh[parentIdx]->f > hp->bh[childIdx]->f) {
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
    struct Cell *tmp = *a;
    *a = *b;
    *b = tmp;
}

void initBinaryHeap() {
    hp.os_size = 0;
    hp.cs_size = 0;
}

/* MIGHT NEED TO BE IN ANOTHER FILE. */
int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return abs(end->x - c1->x) + abs(end->y - c1->y);
}

// get neighbours

// we calculate function value for cell. we add it to min prio queue where lowest value chosen next.