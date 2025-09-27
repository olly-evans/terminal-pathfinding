#include <stdlib.h>
#include <stdio.h>

#include "output.h"
#include "heap.h"

/* PRIORITY QUEUE */
Heap hp;

void heapExtract(Heap *hp) {
    /* remove highest priority element from Priority queue. */
    
    if (!hp->size) return;

    struct Cell **root = &hp->bh[0];
    struct Cell **last = &hp->bh[hp->size - 1];
    swap(root, last);

    hp->size--;
    free(*root);

    // bubble down the new root.
    heapBubbleDown(hp, 0);
}   

void heapInsert(Heap *hp, struct Cell *cell) {

    /* Add element to the binary heap. */

    int idx = hp->size; // hp.size incremented so saving this.

    hp->bh = realloc(hp->bh, (hp->size + 1) * sizeof(*hp->bh ));
    hp->bh[hp->size++] = cell;

    // If one cell in queue we can just return no bubbling required.
    if (hp->size == 1) return;

    heapBubbleUp(hp, idx);
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
    /* 
    Bubble down new root for min-heap. 
    Works in my head but am having to reuse code here.
    */

    int lchildIdx = (2*parentIdx + 1);
    int rchildIdx = (2*parentIdx + 2);

    int parent_f = hp->bh[parentIdx]->f;
    int lchild_f = hp->bh[lchildIdx]->f;
    int rchild_f = hp->bh[rchildIdx]->f;

    // If no left child, then no bubble required.
    if (lchildIdx > hp->size) return hp;

    // We have a left child if we get here, do we have a right.
    if (rchildIdx > hp->size) {
        if (lchild_f < parent_f) {
            swap(&hp->bh[lchild_f], &hp->bh[parentIdx]);
        }
        return hp;
    }

    int smallest_child = (lchild_f < rchild_f) ? lchildIdx : rchildIdx;
    while (smallest_child < hp->size && hp->bh[smallest_child]->f < hp->bh[parentIdx]->f) {

        // Which childs do we have.
        if (lchildIdx > hp->size) return hp;

        if (rchildIdx > hp->size) {
            if (hp->bh[lchildIdx]->f < hp->bh[parentIdx]->f) {
                swap(&hp->bh[lchildIdx], &hp->bh[parentIdx]);
            } 
            return hp;
        }

        // Need to check indexes again.
        swap(&hp->bh[smallest_child], &hp->bh[parentIdx]);

        parentIdx = smallest_child;
        lchildIdx = (2*parentIdx + 1);
        rchildIdx = (2*parentIdx + 2);

        smallest_child = (hp->bh[lchildIdx]->f < hp->bh[rchildIdx]->f) ? lchildIdx : rchildIdx;
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
    hp.size = 0;
}

/* MIGHT NEED TO BE IN ANOTHER FILE. */
int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return abs(end->x - c1->x) + abs(end->y - c1->y);
}

// get neighbours

// we calculate function value for cell. we add it to min prio queue where lowest value chosen next.