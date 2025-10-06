#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>

#include "abuf.h"
#include "terminal.h"

#define PATH_VERSION "0.0.1"

/* Grid */



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


#endif