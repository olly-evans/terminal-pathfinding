#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "welcome.h"
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

void astarCell(struct abuf *s_ab);
void astarGrid(Heap *hp, struct abuf *s_ab);

#endif