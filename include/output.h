#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>

#include "abuf.h"
#include "terminal.h"

#define PATH_VERSION "0.0.1"

/* Grid */

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

struct Grid {
    int rows, cols; // The rows and columns in the grid.

    struct Cell **cells; /* Pointer to array of cell pointers.
                            Each cell pointer points to an array of cells for each row.
                         */ 

    struct Cell *start_cell; // Cell pointer to start cell in grid.
    struct Cell *end_cell; // Cell pointer to end cell in grid.
};

extern struct Grid *g;

void drawPathfindingVisualizer();
void drawWelcomeScreen();
void drawGrid(struct abuf *ab);
void drawWelcomeRows(struct abuf *ab);
bool isHeaderRow(int row);
bool isDataRow(int row); 
bool isCursorRow(int row);
void checkScroll();


void formatAppendRows(struct abuf *ab, int row);

int getfRowLen(int row);
void formatRow(char * buf, size_t bufsize, int row);
void appendVisibleRow(struct abuf *ab, char *buf);
void drawCell(struct abuf *ab, struct Cell *cell);
char* getCellColor(struct Cell *cell);

#endif