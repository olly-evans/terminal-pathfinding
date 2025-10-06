#ifndef INIT_H
#define INIT_H

#include "welcome.h"

void init();
struct Grid* initGrid(struct Grid *g, int rows, int cols);
void freeGrid(struct Grid *g);
void getTableColWidths();

#endif