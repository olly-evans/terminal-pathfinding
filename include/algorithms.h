#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "heap.h"
#include "grid.h"

void astar(Grid *g);
void DFS(Grid *g);
void BFS(Grid *g);
void reconstructPath();
void showSearchStats();

#endif