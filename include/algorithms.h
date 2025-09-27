#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "output.h"

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
void initSearch();

#endif