#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include "abuf.h"


/* Anything between 3000-8000 I've found to look best. Does depend on this algorithm though.
*
*  3000: Fast and smooth, harder to see changes.
*  8000: Not as smooth, easier to see changes.
*
*/

#define DRAW_DELAY_MICRO_SEC 5000

enum CellTypes {
    START,
    END,
    BARRIER,
    PERMANENT_BARRIER,
    EMPTY,
    CLOSED,
    OPEN,
    PATH
};  

struct Cell {
    enum CellTypes type; // What is the cells type, see enum.
    int x, y; // Cell's y (row) and x (col) in g->cells.
    char ch; // Cell's outward character.

    struct Cell *prev; // Pointer to cell this cell came from to retrace best path.
    
    bool inOpenSet;
    bool inClosedSet;

    bool explored;

    int weight; // Cell to cell weight.
    int g; // Cumulative weight from start cell to this cell.
    int md; // Manhattan distance of cell to the end cell.
    int f; // Global cost, f = g + h 
};

void drawCell(struct Cell *cell);
char* getCellColor(struct Cell *cell);
bool isStartCell(struct Cell *c);
bool isEndCell(struct Cell *c);
bool isWalkableCell(struct Cell *c);
bool isPermBarrier(struct Cell *c);
int getManhattanDist(struct Cell *c1, struct Cell *end);

#endif