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

    hp->os = NULL;
    hp->cs = NULL;

    hp->os_size = 0;
    hp->cs_size = 0;

    hp->os_cap = INIT_OS_CAP;
    hp->cs_cap = INIT_CS_CAP;

    return hp;
}

struct Cell *heapExtract(Heap *hp) {
    if (hp->os_size == 0) {
        free(hp->os);
        hp->os = NULL;
        return NULL;
    }

    struct Cell *extracted = hp->os[0];  // Pop the root at index 0.

    // Swap root with last element
    int lastIdx = hp->os_size - 1;
    swap(&hp->os[0], &hp->os[lastIdx]);
    hp->os_size--;

    // Bubble down the new root to maintain heap property
    heapBubbleDown(hp, 0);

    extracted->inOpenSet = false;
    return extracted;
}

void heapInsert(Heap *hp, struct Cell *cell) {

    /* Add cell to the binary min-heap. */

    if (cell->inOpenSet) return;
    
    cell->type = OPEN;
    cell->inOpenSet = true;

    if (hp->os_size == 0) {
        free(hp->os);
        hp->os = malloc(hp->os_cap * sizeof(struct Cell *));
    }
    
    if (hp->os_size == hp->os_cap) {
        hp->os_cap *= 2;
        struct Cell **tmp = realloc(hp->os, (hp->os_cap) * sizeof(struct Cell *));
        if (!tmp) die("heapInsert() -> realloc()"); // Not sure what to do here.
        hp->os = tmp;
    }

    hp->os[hp->os_size++] = cell;

    // If one cell in queue we can just return, no bubbling required.
    if (hp->os_size == 1) return;

    heapBubbleUp(hp, hp->os_size - 1);
}

void heapBubbleUp(Heap *hp, int childIdx) {

    /* Try and make this account for g score too */
    if (childIdx == 0) return;

    int parentIdx = ((childIdx - 1) / 2);

    while (childIdx > 0 && hp->os[parentIdx]->f >= hp->os[childIdx]->f) {
        swap(&hp->os[parentIdx], &hp->os[childIdx]);

        childIdx = parentIdx;
        parentIdx = ((childIdx - 1) / 2);
    }
    return;
}

void heapBubbleDown(Heap *hp, int parentIdx) {
    int os_size = hp->os_size;

    while (1) {
        int lchildIdx = 2 * parentIdx + 1;
        int rchildIdx = 2 * parentIdx + 2;
        int smallestIdx = parentIdx;

        // Check if left child exists and has lower f
        if (lchildIdx < os_size && hp->os[lchildIdx]->f < hp->os[smallestIdx]->f) {
            smallestIdx = lchildIdx;
        }

        // Check if right child exists and has lower f
        if (rchildIdx < os_size && hp->os[rchildIdx]->f < hp->os[smallestIdx]->f) {
            smallestIdx = rchildIdx;
        }

        if (smallestIdx == parentIdx) break;

        if (parentIdx >= hp->os_size || smallestIdx >= hp->os_size) return;
        
        swap(&hp->os[parentIdx], &hp->os[smallestIdx]);
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

    if (hp->cs_size == 0) {
        hp->cs = malloc(hp->cs_cap * sizeof(*hp->cs));
    }

    if (hp->cs_size == hp->cs_cap) {
        hp->cs_cap *= 2;
        hp->cs = realloc(hp->cs, hp->cs_cap * sizeof(*hp->cs )); 
    }
    hp->cs[hp->cs_size++] = curr;

    curr->type = CLOSED;
    curr->inClosedSet = true;
    
    return;
}

int getOpenSetIdx(Heap *hp, struct Cell *cell) {
    for (int i = 0; i < hp->os_size; i++) {
        if (hp->os[i]->x == cell->x && hp->os[i]->y == cell->y) {
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

    if (hp->os) free(hp->os);
    hp->os = NULL;

    if (hp->cs) free(hp->cs);
    hp->cs = NULL;

    free(hp);
}