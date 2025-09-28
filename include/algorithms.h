#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "output.h"
#include "heap.h"

/* Welcome Info */

typedef struct {
    char *name;
    char *description;
    char *speed;
} tablerow;

typedef struct {
    int lName;
    int lDesc;
    int lSpeed;

    int tablewidth;
    int algoCount;
    tablerow *rows;
} table;

extern table algos;
extern tablerow algoRows[];

void search();
void astar();
void initSearch();
struct Cell* updateCellF(struct Cell *cell);
Heap* makeClosed(Heap *hp, struct Cell* curr);
bool isValidNeighbour(Heap *hp, struct Cell *cell);

#endif