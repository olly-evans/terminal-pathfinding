#ifndef INIT_H
#define INIT_H


void init();
struct Grid* initGrid(struct Grid *g, int rows, int cols);
void freeGrid(struct Grid *g);

#endif