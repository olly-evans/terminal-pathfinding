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

void swap(struct Cell **a, struct Cell **b) {
    struct Cell *tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapBubbleDown(Heap *hp, int parentIdx) {
    /* Bubble down new root for min-heap. */

    int lchildIdx = (2*parentIdx + 1);
    int rchildIdx = (2*parentIdx + 2);

    int lchild_f = hp->bh[lchildIdx]->f;
    int rchild_f = hp->bh[rchildIdx]->f;


    int smallest_child = (lchild_f < rchild_f) ? lchildIdx : rchildIdx;

    // Look over this, think this is right.
    while (smallest_child < hp->size && hp->bh[smallest_child]->f < hp->bh[parentIdx]->f) {

        //unsure about what i actually need to pass in here.
        swap(&hp->bh[smallest_child], &hp->bh[parentIdx]);

        parentIdx = smallest_child;
        lchildIdx = (2*parentIdx + 1);
        rchildIdx = (2*parentIdx + 2);

        smallest_child = (hp->bh[lchildIdx]->f < hp->bh[rchildIdx]->f) ? lchildIdx : rchildIdx;
        
    }
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


// // get cells total cost. (weight + manhattan dist.)
// int getCellCost(struct Cell *cell, struct Cell *end_cell) {
//     return cell->weight + getManhattanDistance(cell, end_cell);
// }

// we calculate function value for cell. we add it to min prio queue where lowest value chosen next.