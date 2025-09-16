#ifndef INIT_H
#define INIT_H
#include "output.h"

void init();
void initGrid(struct Grid *g, int rows, int cols);
void freeGrid(struct Grid *g);

#endif