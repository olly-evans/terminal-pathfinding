#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "algorithms.h"
#include "cell.h"
#include "terminal.h"

/* Functions that provide functionality for a priority queue using a binary min-heap */

Heap* initHeap() {

    /* Initialise heap struct for algorithm. */

    Heap *hp = malloc(sizeof(Heap));
    if (!hp) die("initHeap() -> malloc");

    hp->openSet = NULL;
    hp->closed_set = NULL;

    hp->openSetSize = 0;
    hp->closedSetSize = 0;

    hp->openSetCapacity = INIT_OS_CAP;
    hp->cs_cap = INIT_CS_CAP;

    return hp;
}

struct Cell *heapExtract(Heap *hp) {
    if (hp->openSetSize == 0) {
        free(hp->openSet);
        hp->openSet = NULL;
        return NULL;
    }

    struct Cell *extracted = hp->openSet[0];  // Pop the root at index 0.

    // Swap root with last element
    int lastIdx = hp->openSetSize - 1;
    swap(&hp->openSet[0], &hp->openSet[lastIdx]);
    hp->openSetSize--;

    // Bubble down the new root to maintain heap property
    heapBubbleDown(hp, 0);

    extracted->inOpenSet = false;
    return extracted;
}

void heapInsert(Heap *hp, struct Cell *cell) {

    /* Add cell to the binary min-heap. */

    if (cell->inOpenSet) return;
    
    Con.cellsSearched++;
    
    cell->type = OPEN;
    cell->inOpenSet = true;

    if (hp->openSetSize == 0) {
        free(hp->openSet);
        hp->openSet = malloc(hp->openSetCapacity * sizeof(struct Cell *));
    }
    
    if (hp->openSetSize == hp->openSetCapacity) {
        hp->openSetCapacity *= 2;
        struct Cell **tmp = realloc(hp->openSet, (hp->openSetCapacity) * sizeof(struct Cell *));
        if (!tmp) die("heapInsert() -> realloc()"); // Not sure what to do here.
        hp->openSet = tmp;
    }

    hp->openSet[hp->openSetSize++] = cell;

    // If one cell in queue we can just return, no bubbling required.
    if (hp->openSetSize == 1) return;

    heapBubbleUp(hp, hp->openSetSize - 1);
}

void heapBubbleUp(Heap *hp, int childIdx) {

    /* Try and make this account for g score too */
    if (childIdx == 0) return;

    int parentIdx = ((childIdx - 1) / 2);

    while (childIdx > 0 && hp->openSet[parentIdx]->f >= hp->openSet[childIdx]->f) {
        swap(&hp->openSet[parentIdx], &hp->openSet[childIdx]);

        childIdx = parentIdx;
        parentIdx = ((childIdx - 1) / 2);
    }
    return;
}

void heapBubbleDown(Heap *hp, int parentIdx) {
    int openSetSize = hp->openSetSize;

    while (1) {
        int lchildIdx = 2 * parentIdx + 1;
        int rchildIdx = 2 * parentIdx + 2;
        int smallestIdx = parentIdx;

        // Check if left child exists and has lower f
        if (lchildIdx < openSetSize && hp->openSet[lchildIdx]->f < hp->openSet[smallestIdx]->f) {
            smallestIdx = lchildIdx;
        }

        // Check if right child exists and has lower f
        if (rchildIdx < openSetSize && hp->openSet[rchildIdx]->f < hp->openSet[smallestIdx]->f) {
            smallestIdx = rchildIdx;
        }

        if (smallestIdx == parentIdx) break;

        if (parentIdx >= hp->openSetSize || smallestIdx >= hp->openSetSize) return;
        
        swap(&hp->openSet[parentIdx], &hp->openSet[smallestIdx]);
        parentIdx = smallestIdx;
    }
    return;
}

void swap(struct Cell **a, struct Cell **b) {
    if (!a || !b) return;
    struct Cell *tmp = *a;
    *a = *b;
    *b = tmp;
}

void makeClosed(Heap *hp, struct Cell* curr) {

    /* 
    Add a cell to the closed set. 

    Can just flag with a bool actually but this way we know how many we have.
    */

    if (curr->inClosedSet) return;

    if (hp->closedSetSize == 0) {
        hp->closed_set = malloc(hp->cs_cap * sizeof(*hp->closed_set));
    }

    if (hp->closedSetSize == hp->cs_cap) {
        hp->cs_cap *= 2;
        hp->closed_set = realloc(hp->closed_set, hp->cs_cap * sizeof(*hp->closed_set )); 
    }
    hp->closed_set[hp->closedSetSize++] = curr;

    curr->type = CLOSED;
    curr->inClosedSet = true;
    
    return;
}

int getOpenSetIdx(Heap *hp, struct Cell *cell) {
    for (int i = 0; i < hp->openSetSize; i++) {
        if (hp->openSet[i]->x == cell->x && hp->openSet[i]->y == cell->y) {
            return i;
        }
    }
    return -1;
}

void freeHeap(Heap *hp) {

    if (!hp) {
        fprintf(stderr, "freeHeap() called with NULL\n");
        return;
    }

    if (hp->openSet) free(hp->openSet);
    hp->openSet = NULL;

    if (hp->closed_set) free(hp->closed_set);
    hp->closed_set = NULL;

    free(hp);
}