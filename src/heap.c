#include <stdlib.h>
#include <stdio.h>

#include "output.h"
#include "heap.h"

/* PRIORITY QUEUE */
Heap hp;

struct Cell* heapExtract(Heap *hp) {
    /* remove highest priority element from Priority queue. */
    
    if (hp->os_size == 0) return NULL;

    struct Cell **root = &hp->bh[0];

    // This non-bubble case is working.
    if (hp->os_size == 1) {
        hp->os_size--;
        return *root;
    }

    struct Cell **last = &hp->bh[hp->os_size - 1];
    swap(root, last);

    hp->os_size--;

    // bubble down the new root.
    heapBubbleDown(hp, 0);
}   

Heap* heapInsert(Heap *hp, struct Cell *cell) {

    /* Add element to the binary heap. */

    int idx = hp->os_size; // hp.size incremented so saving this.

    hp->bh = realloc(hp->bh, (hp->os_size + 1) * sizeof(*hp->bh ));
    hp->bh[hp->os_size++] = cell;

    // If one cell in queue we can just return no bubbling required.
    if (hp->os_size == 1) return hp;

    heapBubbleUp(hp, idx);
    return hp;
}

void heapBubbleUp(Heap *hp, int childIdx) {

    int parentIdx = ((childIdx - 1) / 2);

    while (childIdx > 0 && hp->bh[parentIdx]->f > hp->bh[childIdx]->f) {
        swap(&hp->bh[parentIdx], &hp->bh[childIdx]);

        childIdx = parentIdx;
        parentIdx = ((childIdx - 1) / 2);
    }
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

        if (parentIdx >= hp->os_size || smallestIdx >= hp->os_size) {
            printf("Invalid index! parentIdx=%d, smallestIdx=%d, os_size=%d\n",
                parentIdx, smallestIdx, hp->os_size);
            return hp;
        }

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
	hp.bh = NULL;
    hp.os_size = 0;
    hp.cs_size = 0;
}

/* MIGHT NEED TO BE IN ANOTHER FILE. */
int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return abs(end->x - c1->x) + abs(end->y - c1->y);
}

// get neighbours

// we calculate function value for cell. we add it to min prio queue where lowest value chosen next.