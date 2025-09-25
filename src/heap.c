#include <stdlib.h>
#include <stdio.h>

#include "output.h"
#include "heap.h"

Heap hp;

// priority queue data structure.
// list of cells sorted by the smallest cost.


/* PRIORITY QUEUE */



void poll() {
    /* remove highest priority element from Priority queue. */
}

void insert(Heap hp, struct Cell *cell) {

    /* Add element to the priority queue. */

    int idx = hp.size; // hp.size incremented so saving this.

    hp.bh = realloc(hp.bh, (hp.size + 1) * sizeof(*hp.bh ));
    hp.bh[hp.size++] = cell;

    // If one cell in queue we can just return no bubbling required.
    if (hp.size == 1) return;

    bubbleUp(&hp, idx);

}

void bubbleUp(Heap *hp, int childIdx) {
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

void bubbleDown() {
    return;
}

void initHeap() {
	hp.bh = NULL;
    hp.size = 1;
}


/* MIGHT NEED TO BE IN ANOTHER FILE. */
int getManhattanDistance(struct Cell *c1, struct Cell *c2) {
    int x1 = c1->x;
    int y1 = c1->y;

    int x2 = c2->x;
    int y2 = c2->y;
}

// get neighbours


// get cells total cost. (weight + manhattan dist.)
int getCellCost(struct Cell *cell, struct Cell *end_cell) {
    return cell->weight + getManhattanDistance(cell, end_cell);
}

// we calculate function value for cell. we add it to min prio queue where lowest value chosen next.