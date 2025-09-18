#ifndef OUTPUT_H
#define OUTPUT_H

#include "abuf.h"
#include "terminal.h"

enum CellTypes {
    START,
    END,
    BORDER,
    EMPTY
};  

struct Cell {
    enum CellTypes type;
    int x, y;
    char ch;
};

struct Grid {
    int rows, cols;
    struct Cell **cells;

    struct Cell *start_cell;
    struct Cell *end_cell;
};

extern struct Grid *g;

void dashRefreshScreen();
void dashDrawRows();
void drawGrid(struct abuf *ab);

#endif