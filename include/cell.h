#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

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

    int weight; // Cell to cell weight.
    int g; // Cumulative weight from start cell to this cell.
    int md; // Manhattan distance of cell to the end cell.
    int f; // Global cost, f = g + h 
};

void drawCell(struct abuf *ab, struct Cell *cell);
char* getCellColor(struct Cell *cell);

#endif