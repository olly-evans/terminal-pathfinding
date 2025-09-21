#ifndef OUTPUT_H
#define OUTPUT_H

#include "abuf.h"
#include "terminal.h"

/* Algorithm Welcome Screen Display Info */

typedef struct {
    char *name;
    char *description;
    char *speed;

    int len; // length of all char* to be printed on row.
    int padding; // horizontal padding given Con.screencols.
} algoInfo;

/* Grid */

enum CellTypes {
    START,
    END,
    BARRIER,
    PERMANENT_BARRIER,
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

void drawPathfindingVisualizer();
void drawWelcomeScreen();
void drawGrid(struct abuf *ab);
void drawWelcomeRows(struct abuf *ab);

#endif